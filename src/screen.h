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

coordenada coordenadas(unsigned int dir);

void asignar_dir(unsigned int tarea, unsigned int dir, unsigned char nro_pag);
void redirigir_misil(unsigned int dir);
void pintar_tarea(int tarea_vieja, int tarea_actual);
void pintar_bandera(int bandera_vieja, int bandera_actual);

void pintar(ca* p, unsigned char a, unsigned char c);
void print(const char * text, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir);
void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir, unsigned char ox);
void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir);

void limpiar_pantalla();

void screen_pintar_pantalla();
void screen_modo_mapa();
void screen_modo_estado();

void pintar_scheduler();
void pintar_buffer_mapa();
void pintar_buffer_estado();

#endif  /* !__SCREEN_H__ */
