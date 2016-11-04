/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "defines.h"
#include "mmu.h"

#define base23(direccion) direccion >> 16
#define base31(direccion) direccion >> 24

#define GDT_NAVIOS(indice)																		\
  gdt[indice].base_0_15  = (unsigned short) ((unsigned int) &(tss_navios[indice])); 			\
  gdt[indice].base_23_16 = (unsigned char)  ((unsigned int) base23(&(tss_navios[indice])));		\
  gdt[indice].base_31_24 = (unsigned char)  ((unsigned int) base31(&(tss_navios[indice])));	

#define GDT_BANDERAS(indice)																	\
  gdt[indice].base_0_15  = (unsigned short) ((unsigned int) &(tss_banderas[indice])); 			\
  gdt[indice].base_23_16 = (unsigned char)  ((unsigned int) base23(&(tss_banderas[indice])));	\
  gdt[indice].base_31_24 = (unsigned char)  ((unsigned int) base31(&(tss_banderas[indice])));	

tss tarea_inicial;
tss tarea_idle;

tss tss_navios[CANT_TAREAS];
tss tss_banderas[CANT_TAREAS];

void tss_inicializar() {
	gdt[indice_inicial].base_0_15  = (unsigned short) ((unsigned int) &(tarea_inicial));
	gdt[indice_inicial].base_23_16 = (unsigned char)  ((unsigned int) base23(&(tarea_inicial)));
	gdt[indice_inicial].base_31_24 = (unsigned char)  ((unsigned int) base31(&(tarea_inicial))); 

	gdt[indice_idle].base_0_15  = (unsigned short) ((unsigned int) &(tarea_idle));
	gdt[indice_idle].base_23_16 = (unsigned char)  ((unsigned int) base23(&(tarea_idle)));
	gdt[indice_idle].base_31_24 = (unsigned char)  ((unsigned int) base31(&(tarea_idle))); 

	GDT_NAVIOS(tarea_1)
	GDT_NAVIOS(tarea_2)
	GDT_NAVIOS(tarea_3)
	GDT_NAVIOS(tarea_4)
	GDT_NAVIOS(tarea_5)
	GDT_NAVIOS(tarea_6)
	GDT_NAVIOS(tarea_7)
	GDT_NAVIOS(tarea_8)

	GDT_BANDERAS(tarea_1_bandera)
	GDT_BANDERAS(tarea_2_bandera)
	GDT_BANDERAS(tarea_3_bandera)
	GDT_BANDERAS(tarea_4_bandera)
	GDT_BANDERAS(tarea_5_bandera)
	GDT_BANDERAS(tarea_6_bandera)
	GDT_BANDERAS(tarea_7_bandera)
	GDT_BANDERAS(tarea_8_bandera)

	tarea_inicial.eip    = 0x00;
	tarea_inicial.ebp    = 0x00;
	tarea_inicial.esp    = 0x00;
	tarea_inicial.ss     = 0x00;
	tarea_inicial.ds     = 0x00;
	tarea_inicial.fs     = 0x00;
	tarea_inicial.gs     = 0x00;
	tarea_inicial.es     = 0x00;
	tarea_inicial.cs 	 = 0x00;
	tarea_inicial.cr3    = 0x00;
	tarea_inicial.eflags = 0x00;

	tarea_idle.eip    = 0x40000000;
	tarea_idle.ebp    = 0x2A000;
	tarea_idle.esp    = 0x2A000;
	tarea_idle.ss     = 0x98;
	tarea_idle.ds     = 0x98;
	tarea_idle.fs     = 0x98;
	tarea_idle.gs     = 0x98;
	tarea_idle.es     = 0xB0;
	tarea_idle.cs 	  = 0x90;
	tarea_idle.cr3    = 0x27000;
	tarea_idle.eflags = 0x202;

	int mar = 0x100000;
	int i;
	for (i = 0; i < CANT_TAREAS; i++){
		tss_navios[i].cs     = 0xA3;     //1010 00 = 20va entrada GDT
		tss_navios[i].ds     = 0xAB;	 //1010 10 = 21va entrada GDT
		tss_navios[i].ss     = 0xAB;
		tss_navios[i].es     = 0xAB;
		tss_navios[i].fs     = 0xAB;
		tss_navios[i].gs     = 0xAB;
		tss_navios[i].eip    = 0x40000000;
		tss_navios[i].esp    = 0x40001C00;
		tss_navios[i].ebp    = 0x40001C00;
		tss_navios[i].eflags = 0x202;
		tss_navios[i].cr3    = mmu_inicializar_dir_tarea(i, mar);
		tss_navios[i].esp0   = prox_pagina_pila();
		tss_navios[i].ss0    = 0x98;
		mar += 0x2000;
	}

	for (i = 0; i < CANT_TAREAS; i++){
		tss_banderas[i].cs     = 0xA3;    //1010 00 = 20va entrada GDT
		tss_banderas[i].ds     = 0xAB;	  //1010 10 = 21va entrada GDT
		tss_banderas[i].ss     = 0xAB;
		tss_banderas[i].es     = 0xAB;
		tss_banderas[i].fs     = 0xAB;
		tss_banderas[i].gs     = 0xAB;
		tss_banderas[i].eip    = 0x40001FFC;
		tss_banderas[i].esp    = 0x40001FFC;
		tss_banderas[i].ebp    = 0x40001FFC;
		tss_banderas[i].eflags = 0x202;
		tss_banderas[i].cr3    = tss_navios[i].cr3;
		tss_banderas[i].esp0   = prox_pagina_pila();
		tss_banderas[i].ss0    = 0x98;		
		mar += 0x2000;
	}
}

