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
#define VIDEO_SCREEN 0xB8000
#define VIDEO_ESTADO 0x2D000
#define VIDEO_MAPA   0x2E000

typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

typedef struct coordenada_s {
    unsigned char col;
    unsigned char fila;
} coordenada;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void screen_pintar_pantalla();

void limpiar_pantalla();

void screen_modo_mapa();

void screen_modo_estado();

#endif  /* !__SCREEN_H__ */
