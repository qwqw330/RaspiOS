#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define COLORDEPTH 32
#define BYTES_PER_PIXEL COLORDEPTH/8
#define PIXEL_SIZE 2

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

/*raspi1 */
#define PERIPHERAL_BASE 0x20000000
/* raspi2
#define PERIPHERAL_BASE 0x3F000000 */ 

#define PERIPHERAL_LENGTH 0x01000000


#define SYSTEM_TIMER_OFFSET 0x3000
#define INTERRUPTS_OFFSET 0xB000
#define MAILBOX_OFFSET 0xB880
#define UART0_OFFSET 0x201000
#define GPIO_OFFSET 0x200000

#define GPIO_BASE (PERIPHERAL_BASE + GPIO_OFFSET)
#define UART0_BASE (PERIPHERAL_BASE + UART0_OFFSET)

#endif
