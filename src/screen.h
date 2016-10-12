/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__


/* Definicion de la pantalla */
#define VIDEO_FILS 25
#define VIDEO_COLS 80
#define VIDEO_MEM 0xB8000

typedef struct pixel {
	unsigned char caracter;
	unsigned char modo;
} __attribute__((packed)) pixel;


void screen_pintar_pantalla();

#endif  /* !__SCREEN_H__ */
