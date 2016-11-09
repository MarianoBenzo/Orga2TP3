/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

unsigned char corriendoBandera;

void sched_inicializar();
unsigned short proximo_indice();

int current_task();
void desalojar_tarea_actual();

#endif	/* !__SCHED_H__ */
