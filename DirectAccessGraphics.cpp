#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char byte;

//Screen memory is placed at A000-BFFF, 320x200 pixels, mapped right to left within each horizontal byte
byte* screen = (byte*)0xA000;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define CHARWIDTH 8
#define CHARHEIGHT 8
#define BYTESPERROW (SCREEN_WIDTH / 8)
#define BYTESPERCHARROW (BYTESPERROW * 8)
#define CHARSPERROW (SCREEN_WIDTH / CHARWIDTH)
#define ROWSPERCOLUMN (SCREEN_HEIGHT / CHARHEIGHT)


void ClearScreen(byte val)
{
    int totalBytes = SCREEN_HEIGHT * BYTESPERROW;
    int i;

    for (i = 0; i < totalBytes; i++)
        screen[i] = val;
}


void SETPIXEL(int x, int y, byte b)
{
    byte* pb = screen;
    pb += x >> 3;
    pb += y * BYTESPERROW;

    if (b)
        *(pb) |= (0b10000000 >> (x & 7));
    else
        *(pb) &= ~(0b10000000 >> (x & 7));
}


void DRAWPIXEL(int x, int y)
{
    byte* pb = screen;
    pb += x >> 3;
    pb += y * BYTESPERROW;
    *(pb) |= (0b10000000 >> (x & 7));
}


void DrawLine(int x0, int y0, int x1, int y1, byte val)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1)
    {
        SETPIXEL(x0, y0, val);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}


int main(void)
{
    ClearScreen(0x00);

    DrawLine(0, 0, 100, 100, 1);

    return 0;
}


