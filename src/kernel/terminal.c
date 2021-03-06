#include <kernel/terminal.h>
#include <kernel/draw.h>

#define ASCII_DELETE 0x7f

uint32_t colours[16] = {
        0x000000, //black
        0x0000aa, //blue
        0x00aa00, //green
        0x00aaaa, //cyan
        0xaa0000, //red
        0xaa00aa, //magenta
        0xaa5500, //brown
        0xaaaaaa, //light grey
        0x555555, //dark grey
        0x5555ff, //light blue
        0x55ff55, //light green
        0x55ffff, //light cyan
        0xff5555, //light red
        0xff55ff, //light magenta
        0xffff55, //yellow
        0xffffff //white
};

char *colour_names[] = {
        "black",
        "blue", 
        "green",
        "cyan",
        "red",
        "magenta",
        "brown",
        "light grey",
        "grey",
        "light blue",
        "light green",
        "light cyan",
        "light red",
        "light magenta",
        "yellow",
        "white"
};

void terminal_colour(uint8_t colour) 
{
        if(colour > 15)
                return; // invalid colour. Do nothing

        draw_set_forecolour(colours[colour]); //set 4bit colour to 16bit equivalent
}


void terminal_display(void)
{
        int x, y;
        int ROWS = (SCREEN_HEIGHT / 16);
        int COLS = (SCREEN_WIDTH / 8);

        for(y = 0; y < COLS; y++) {
                for(x = 0; x < ROWS; x++) {
                }
        }
}

