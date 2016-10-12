/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"

static pixel (*pantalla)[VIDEO_COLS] = (pixel (*)[VIDEO_COLS]) VIDEO_MEM;


void pintar_pixel(pixel* p, unsigned char modo, unsigned char caracter)
{
	p->modo = modo;
	p->caracter = caracter;
} 

void screen_pintar_pantalla()
{
	int f = 0;
	while (f < VIDEO_FILS)
	{
		int c = 0;
		while (c < VIDEO_COLS)
		{
			if (f == 0 || f == (VIDEO_FILS - 1)){
				pintar_pixel(&(pantalla[f][c]), C_FG_WHITE, 65);
			}else{
				pintar_pixel(&(pantalla[f][c]), 0, 0);
			}
			c++;
		}
		f++;
	}
}
