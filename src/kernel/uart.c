#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <common/stdlib.h>

/*memory mapped I/O output */
void mmio_write(uint32_t reg, uint32_t data)
{
        *(volatile uint32_t *)reg = data;
}

/* memory-mapped I/O input */
uint32_t mmio_read(uint32_t reg)
{
        return *(volatile uint32_t *)reg;
}


/* delaya the compiler wont optimize */
void delay(int32_t count)
{
        asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                        : "=r"(count): [count]"0"(count): "cc");
}

void uart_init()
{
        uart_control_t control;
        /* disable UART0 */
        bzero(&control, 4);
        mmio_write(UART0_CR, control.as_int);

        /* setup GPIO pin 14 && 15 */
        mmio_write(GPPUD, 0x00000000);
        delay(150);

        mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
        delay(150);
        
        /* write 0 to GPPUDCLK0 to make it take effect */
        mmio_write(GPPUDCLK0, 0x00000000);

        /* clear pending interrupts */
        mmio_write(UART0_ICR, 0x7FF);


        /* Set integer & fractional part of baud rate.
        Divider = UART_CLOCK/(16 * Baud)
        Fraction part register = (Fractional part * 64) + 0.5
        UART_CLOCK = 48000000 (48 MHz); Baud = 115200.

        Divider = 48000000 / (16 * 115200) = 26.041 = ~26. */
        mmio_write(UART0_IBRD, 26);
        /* Fractional part register = (.041 * 64) + 0.5 = 3.124 = ~3. */
        mmio_write(UART0_FBRD, 3);

        /* Enable FIFO & 8 bit data transmissio (1 stop bit, no parity). */
        mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

        /* Mask all interrupts. */
        mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

        /* Enable UART0, receive & transfer part of UART. */
        control.uart_enabled = 1;
        control.transmit_enabled = 1;
        control.receive_enabled = 1;
        mmio_write(UART0_CR, control.as_int);
}


uart_flags_t read_flags(void) {
        uart_flags_t flags;
        flags.as_int = mmio_read(UART0_FR);
        return flags;
}

void uart_putc(unsigned char c)
{
        uart_flags_t flags;
        /* Wait for UART to become ready to transmit. */

        do {
                flags = read_flags();
        }
        while ( flags.transmit_queue_full );
        mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
        /* Wait for UART to have received something. */
        uart_flags_t flags;
        do {
                flags = read_flags();
        }
        while ( flags.receive_queue_empty );
        return mmio_read(UART0_DR);
}

