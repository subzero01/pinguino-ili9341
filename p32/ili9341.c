/*******************************************************************************
 * File:        lcd.c
 * Project:     ILI9341
 * Author:      Nicolas Meyertöns
 * Version:     siehe main.h
 * Web:         http://pic-projekte.de
 ******************************************************************************/

#include <stdlib.h>
#include "ili9341.h"
#include <spi.h>
#include "font.h"
#include <math.h>

#include <digitalw.c>
#include <delay.c>

/*******************************************************************************
 * Globale Variablen
 */

uint16_t global_bg_color = BLACK;

uint16_t global_spi = 1;
uint16_t global_dc = 0;
uint16_t global_cs = 0;
/*******************************************************************************
 * Initialisierung des Displays mit einer frei waehlbaren Hintergrundfarbe
 */

void ili9341_init (uint16_t spi, uint16_t cs, uint16_t dc)
{    
    global_spi = spi;
    global_dc = dc;
    global_cs =cs;
    
    ili9341_send(LCD_REG,  0xCB);
    ili9341_send(LCD_DATA, 0x39);
    ili9341_send(LCD_DATA, 0x2C);
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0x34);
    ili9341_send(LCD_DATA, 0x02);

    ili9341_send(LCD_REG,  0xCF);
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0XC1);
    ili9341_send(LCD_DATA, 0X30);

    ili9341_send(LCD_REG,  0xE8);
    ili9341_send(LCD_DATA, 0x85);
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0x78);

    ili9341_send(LCD_REG,  0xEA);
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0x00);

    ili9341_send(LCD_REG,  0xED);
    ili9341_send(LCD_DATA, 0x64);
    ili9341_send(LCD_DATA, 0x03);
    ili9341_send(LCD_DATA, 0X12);
    ili9341_send(LCD_DATA, 0X81);

    ili9341_send(LCD_REG,  0xF7);
    ili9341_send(LCD_DATA, 0x20);

    ili9341_send(LCD_REG,  0xC0); // Power control
    ili9341_send(LCD_DATA, 0x23); // VRH[5:0]

    ili9341_send(LCD_REG,  0xC1); // Power control
    ili9341_send(LCD_DATA, 0x10); // SAP[2:0];BT[3:0]

    ili9341_send(LCD_REG,  0xC5); // VCM control
    ili9341_send(LCD_DATA, 0x3e);
    ili9341_send(LCD_DATA, 0x28);

    ili9341_send(LCD_REG,  0xC7); // VCM control2
    ili9341_send(LCD_DATA, 0x86);

    ili9341_send(LCD_REG,  0x36); // Memory Access Control
    ili9341_send(LCD_DATA, 0x88); // C8

    ili9341_send(LCD_REG,  0x3A);
    ili9341_send(LCD_DATA, 0x55);

    ili9341_send(LCD_REG,  0xB1);
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0x18);

    ili9341_send(LCD_REG,  0xB6); // Display Function Control
    ili9341_send(LCD_DATA, 0x08);
    ili9341_send(LCD_DATA, 0x82);
    ili9341_send(LCD_DATA, 0x27);

    ili9341_send(LCD_REG,  0xF2); // 3Gamma Function Disable
    ili9341_send(LCD_DATA, 0x00);

    ili9341_send(LCD_REG,  0x26); // Gamma curve selected
    ili9341_send(LCD_DATA, 0x01);

    ili9341_send(LCD_REG,  0xE0); // Set Gamma
    ili9341_send(LCD_DATA, 0x0F);
    ili9341_send(LCD_DATA, 0x31);
    ili9341_send(LCD_DATA, 0x2B);
    ili9341_send(LCD_DATA, 0x0C);
    ili9341_send(LCD_DATA, 0x0E);
    ili9341_send(LCD_DATA, 0x08);
    ili9341_send(LCD_DATA, 0x4E);
    ili9341_send(LCD_DATA, 0xF1);
    ili9341_send(LCD_DATA, 0x37);
    ili9341_send(LCD_DATA, 0x07);
    ili9341_send(LCD_DATA, 0x10);
    ili9341_send(LCD_DATA, 0x03);
    ili9341_send(LCD_DATA, 0x0E);
    ili9341_send(LCD_DATA, 0x09);
    ili9341_send(LCD_DATA, 0x00);

    ili9341_send(LCD_REG,  0xE1); // Set Gamma
    ili9341_send(LCD_DATA, 0x00);
    ili9341_send(LCD_DATA, 0x0E);
    ili9341_send(LCD_DATA, 0x14);
    ili9341_send(LCD_DATA, 0x03);
    ili9341_send(LCD_DATA, 0x11);
    ili9341_send(LCD_DATA, 0x07);
    ili9341_send(LCD_DATA, 0x31);
    ili9341_send(LCD_DATA, 0xC1);
    ili9341_send(LCD_DATA, 0x48);
    ili9341_send(LCD_DATA, 0x08);
    ili9341_send(LCD_DATA, 0x0F);
    ili9341_send(LCD_DATA, 0x0C);
    ili9341_send(LCD_DATA, 0x31);
    ili9341_send(LCD_DATA, 0x36);
    ili9341_send(LCD_DATA, 0x0F);

    ili9341_send(LCD_REG,  0x11); // Sleep out
    Delayms(120);
    ili9341_send(LCD_REG, 0x2c);  
    ili9341_fill(global_bg_color);
    
    ili9341_send(LCD_REG, 0x29); // Display on 
    ili9341_send(LCD_REG, 0x2c);
}

/*******************************************************************************
 * Daten werden via SPI-Bus an den Display-Controller gesendet
 */

void ili9341_send(bool dc, uint8_t value)
{   
    /* register or data */
    digitalwrite(global_dc, dc?1:0);

    /* transmit via SPI */
    digitalwrite(global_cs,0);
    SPI_write(global_spi, value);
    digitalwrite(global_cs,1);
}

/*******************************************************************************
 * Platzieren des Cursors an Punkt (x,y)
 */

uint8_t ili9341_set_cursor(uint16_t x, uint16_t y)
{
    if( ili9341_set_cursor_x(x) || ili9341_set_cursor_y(y) )
    {
        return EXIT_FAILURE;
    }
	
    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Teilplatzierung des Cursors an (x,_)
 */

uint8_t ili9341_set_cursor_x(uint16_t x)
{
    if( x >= LCD_WIDTH )
    {
        return EXIT_FAILURE;
    }
    
    ili9341_send(LCD_REG,  0x2B);
    ili9341_send(LCD_DATA, x >> 8);
    ili9341_send(LCD_DATA, x & 0xFF);
    ili9341_send(LCD_REG, 0x2c);
    
    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Teilplatzierung des Cursors an (_,y)
 */

uint8_t ili9341_set_cursor_y(uint16_t y)
{
    if( y >= LCD_HEIGHT ) 
    {
        return EXIT_FAILURE;
    }
    
    ili9341_send(LCD_REG,  0x2A);
    ili9341_send(LCD_DATA, y >> 8);
    ili9341_send(LCD_DATA, y & 0xFF);
    ili9341_send(LCD_REG, 0x2c);
    
    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Zeichnen eines Pixels an die aktuelle Cursorposition
 */

uint8_t ili9341_draw_pixel(uint16_t color)
{
    ili9341_send(LCD_DATA, color >> 8);
    ili9341_send(LCD_DATA, color & 0xFF);
    
    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Fuellen des gesamten Displays mit einer frei waehlbaren Farbe
 */

void ili9341_fill(uint16_t bg_color)
{   
    uint16_t width = LCD_WIDTH, height = LCD_HEIGHT;
    
    if( ili9341_set_cursor(0,0) )
    {
        return;
    }
    
    while(width--)
    {
        while(height--)
        {
            ili9341_draw_pixel(bg_color);
        }
        height = LCD_HEIGHT;
    }
}

/*******************************************************************************
 * Zeichnen einer Linie beliebiger Orientierung von (x0,y0) zu (x1,y1).
 * Zum Zeichnen horizontaler oder vertikaler Linien die jeweils separate 
 * Funktion mit Geschwindigkeitsvorteil verwenden!
 */

void ili9341_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t dx = x1 - x0, sx = x0 < x1 ? 1 : -1;
    int16_t dy = y1 - y0, sy = y0 < y1 ? 1 : -1; 
    int16_t err, e2;
    
    if(x0 > x1)
    {
        dx = -dx;
    }
    
    if(y1 > y0)
    {
        dy = -dy;
    }
    
    err = dx + dy;
    
    while(true)
    {
        ili9341_draw_pixel_at( x0, y0, color);

        if ( (x0 == x1) && (y0 == y1) )
        {
            break;
        }

        e2 = (err << 1);

        if(e2 >= dy)
        {
            err += dy; 
            x0 += sx;
        }

        if(e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

/*******************************************************************************
 * Zeichnen einer vertikalen Linie von (y0) zu (y1) auf (x). Diese Funktion
 * bietet einen Geschwindigkeitsvorteil im Vergleich zu ili9341_draw_line.
 */

void ili9341_draw_ver_line(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color)
{
    ili9341_set_cursor(x,y0);
    
    while(y0 != y1)
    {
        ili9341_draw_pixel(color);
        y1--;
    }
}

/*******************************************************************************
 * Zeichnen einer horizontalen Linie von (y0) zu (y1) auf (x). Diese Funktion
 * bietet einen Geschwindigkeitsvorteil im Vergleich zu ili9341_draw_line.
 */

void ili9341_draw_hor_line(uint16_t y, uint16_t x0, uint16_t x1, uint16_t color)
{
    while(x0 != x1)
    {
        ili9341_draw_pixel_at(x0,y,color);
        x0++;
    }
}

/*******************************************************************************
 * Zeichnen eines Pixels an den Punkt (x,y) mit Farbe <color>
 */

void ili9341_draw_pixel_at(uint16_t x, uint16_t y, uint16_t color)
{
    if( !ili9341_set_cursor(x,y) )
    {
        ili9341_draw_pixel(color);
    }
}

/*******************************************************************************
 * Zeichnen eines ausgefuellten Rechteckes mit den Punkten (x0,y0) und (x1,y1)
 */

void ili9341_fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint16_t y_start = y0;

    if( (y0 >= LCD_HEIGHT) || (x0 >= LCD_WIDTH) ) 
    {
        return;
    }
    
    if( x1 >= LCD_WIDTH )
    {
        x1 = LCD_WIDTH;
    }
    
    if( y1 >= LCD_HEIGHT )
    {
        y1 = LCD_HEIGHT;
    }
	
    while( x0 <= x1 )
    {
        ili9341_set_cursor(x0++, y0);

        while( y0++ <= y1 )
        {
            ili9341_draw_pixel(color);
        }
        y0 = y_start;
    }
} 

/*******************************************************************************
 * Zeichnen eines Rechteckes mit den Punkten (x0,y0) und (x1,y1)
 */

void ili9341_draw_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    ili9341_draw_ver_line(x0,y0,y1,color);
    ili9341_draw_ver_line(x1,y0,y1,color);
    ili9341_draw_hor_line(y0,x0,x1,color);
    ili9341_draw_hor_line(y1,x0,x1,color);
}

/*******************************************************************************
 * Zeichnen eines Kreises mit dem Zentrum (xm,ym) und dem Radius (r)
 */

void ili9341_draw_circle(int16_t xm, int16_t ym, int16_t r, uint16_t color)
{
    int16_t x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
   
    do 
    {
        ili9341_draw_pixel_at(xm-x, ym+y, color); /*   I. Quadrant */
        ili9341_draw_pixel_at(xm-y, ym-x, color); /*  II. Quadrant */
        ili9341_draw_pixel_at(xm+x, ym-y, color); /* III. Quadrant */
        ili9341_draw_pixel_at(xm+y, ym+x, color); /*  IV. Quadrant */
        
        r = err;
        
        if (r <= y)
        {
            y++;
            err += y*2+1;           /* e_xy+e_y < 0 */
        }
        if (r > x || err > y)
        {
            x++;
            err += x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
        }
    } while (x < 0);
}

/*******************************************************************************
 * Zeichnen eines gefuellten Kreises mit dem Zentrum (xm,ym) und dem Radius (r)
 */

void ili9341_draw_filled_circle (uint16_t xm, uint16_t ym, uint8_t r, uint16_t color)
{
    int16_t f = 1 - r, ddF_x = 1, ddF_y = 0 - (2*r), x = 0, y = r;

    ili9341_draw_ver_line(xm, ym-r, ym+r, color);
    
    while(x < y)
    {
        if(f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        ili9341_draw_ver_line(xm+x, ym-y, ym+y, color);
        ili9341_draw_ver_line(xm-x, ym-y, ym+y, color);
        ili9341_draw_ver_line(xm+y, ym-x, ym+x, color);
        ili9341_draw_ver_line(xm-y, ym-x, ym+x, color);
    }
}

/*******************************************************************************
 * Zeichnen eines Zeichens an Position (x,y) - Diese Funktion kann nur indirekt
 * mit Hilfe der Funktion ili9341_draw_string aufgerufen werden, da diese den 
 * entsprechenden Index fuer den font-Vector berechnet!
 */

void ili9341_draw_char (uint16_t x, uint16_t y, uint16_t fIndex, uint16_t fg_color, uint16_t bg_color)
{
    uint8_t j, k, i;
    uint16_t iOffset = fIndex + (FONT_WIDTH)*FONT_HEIGHT;
    
    for(j=0; j < font[fIndex]; j++) // variable character width
    {
        ili9341_set_cursor(x + font[fIndex] - j, y); // print from right to left
        
        for(k=0; k<FONT_HEIGHT; k++) // _ bytes per character (height)
        {
            for(i=0; i<8; i++)
            {
                if( font[ iOffset - (j*FONT_HEIGHT) - k ] & (0x80 >> i) )
                {
                    ili9341_draw_pixel(fg_color);
                }
                else
                {
                    ili9341_draw_pixel(bg_color);
                }
            }
        }
    }
}

/*******************************************************************************
 * Zeichnen einer Zeichenkette ab Position (x,y)
 */

void ili9341_draw_string (uint16_t x, uint16_t y, const char *pS, uint16_t fg_color, uint16_t bg_color)
{    
    uint16_t lIndex, k;
    
    while(*pS)
    {
        /* index the width information of character <c> */
        lIndex = 0;
        for(k=0; k<(*pS - ' '); k++)
        {
            lIndex += ((font[lIndex]) << 1) + 1;
        }
        
        /* draw character */
        ili9341_draw_char(x, y, lIndex, fg_color, bg_color);
        
        /* move the cursor forward for the next character */
        x += font[lIndex];
        
        /* next charachter */
        pS++;
    }
}

/*******************************************************************************
 * Darstellen großer Ziffern
 */

void ili9341_draw_number (uint16_t x, uint16_t y, char nr, uint16_t fg_color, uint16_t bg_color, uint8_t size)
{
    uint8_t j, k, i, width = NUMBER_WIDTH, height = NUMBER_HEIGHT;
    uint16_t iOffset = 0;
    bool hit = false;
    
    switch(size)
    {
        case NORMAL:
            iOffset = (nr - '0')*(width*height) + (width*height) - 1;
            break;
        case BIG:
            width = BIG_NUMBER_WIDTH;
            height = BIG_NUMBER_HEIGHT;
            iOffset = (nr - '0')*(width*height) + (width*height) - 1;
            break;
    }
    
    for(j=0; j < width; j++)
    {
        ili9341_set_cursor(x + width - j, y);
        
        for(k=0; k<height; k++)
        {
            for(i=0; i<8; i++)
            {
                hit = false;
                
                switch(size)
                {
                    case NORMAL:
                        if( numbers[ iOffset - (j*(height)) - k ] & (0x80 >> i) )
                        {
                            hit = true;
                        }                        
                        break;
                    case BIG:
                        if( bigNumbers[ iOffset - (j*(height)) - k ] & (0x80 >> i) )
                        {
                            hit = true;
                        }                     
                        break;         
                }
                
                if( hit )
                {
                    ili9341_draw_pixel(fg_color);
                }
                else
                {
                    ili9341_draw_pixel(bg_color);
                } 
            }
        }
    }
}
