/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"

void pintar(ca* p, unsigned char a, unsigned char c)
{
	p->a = a;
	p->c = c;
}

void limpiar_pantalla()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int f;
    for (f = 0; f < VIDEO_FILS; f++)
    {
        int c;
        for (c = 0; c < VIDEO_COLS; c++)
            pintar(&(p[f][c]), 0, 0);
    }    
}

void screen_pintar_pantalla()
{
	ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
	int f;
	for (f = 0; f < VIDEO_FILS; f++)
	{
		int c;
		for (c = 0; c < VIDEO_COLS; c++)
		{
			if (f == 0 || f == (VIDEO_FILS - 1))
				pintar(&(p[f][c]), C_FG_WHITE, 65);
			else
				pintar(&(p[f][c]), 0, 0);
		}
	}
}

void screen_modo_mapa()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int f;
    for (f = 0; f < VIDEO_FILS; f++)
    {
        int c;
        for (c = 0; c < VIDEO_COLS; c++)
        {
            if (f < 4 || (f == 4 && c < 17))
                pintar(&(p[f][c]), C_BG_GREEN, 0);
            else if(f == VIDEO_FILS-1)
                pintar(&(p[f][c]), C_BG_BLACK, 0);
            else
                pintar(&(p[f][c]), C_BG_CYAN, 0);
            
        }
    }
}

void screen_modo_estado()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int f = 0;
    int c;
    //imprimo cabecera
    print("Francesco Tamburini/Teatro Colon", 0, 0, C_BG_BLACK + C_FG_WHITE);
    for (c = 32; c < VIDEO_COLS; c++)
        pintar(&(p[f][c]), C_BG_BLACK, 0);

    //imprimo fondo
    for (f = 1; f < VIDEO_FILS; f++)
        for (c = 0; c < VIDEO_COLS; c++)
            pintar(&(p[f][c]), C_BG_LIGHT_GREY, 0);

    //imprimo letras de los navios
    int navio = 0;
    for (f = 2; f < 10; f += 7)
    {
        for (c = 5; c < 51; c += 12)
        {
            print("NAVIO ", c, f, C_BG_LIGHT_GREY + C_FG_BLACK);
            print_int(navio, c + 6, f, C_BG_LIGHT_GREY + C_FG_BLACK);
            navio++;
        }
    }

    //imprimo pantalla de debug
    for (f = 2; f < 15; f++)
        for (c = 50; c < 78; c++)
            pintar(&(p[f][c]), C_BG_BLACK, 0);

    //imprimo pantalla de estados
    navio = 1;
    for (f = 16; f < VIDEO_FILS - 1; f++)
    {
        for (c = 0; c < VIDEO_COLS; c++)
        {
            if (c == 0 || c == VIDEO_COLS - 1)
                pintar(&(p[f][c]), C_BG_BLACK, 0);
            else if (c == 1)
                print_int(navio, c, f, C_BG_LIGHT_GREY + C_FG_BLACK);
            else
                pintar(&(p[f][c]), C_BG_CYAN, 0);
        }
        navio++;
    }

    //imprimo barra del scheduler
    f = VIDEO_FILS - 1;
    for (c = 0; c < VIDEO_COLS; c++)
    {
        if (c == 0)
            print("*", c, f, C_BG_LIGHT_GREY + C_FG_BLACK);
        else if (c == VIDEO_COLS - 1)
            print("*", c, f, C_BG_BLACK + C_FG_WHITE);
        else
            pintar(&(p[f][c]), C_BG_BLACK, 0);
    }

}

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}




