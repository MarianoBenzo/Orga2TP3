/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"

const unsigned char task_idle = (indice_idle << 3);
// Arreglos con los selectores de segmento en la GDT + privilegios
unsigned short tasks[CANT_TAREAS];					
unsigned short flags[CANT_TAREAS];
// Respectivos indices a cada arreglo
int currTask;
int currFlag;
// Contador y booleano para controlar la ejecucion de banderas
unsigned char modoBandera;
unsigned char cicloBandera;

void sched_inicializar() {
	// Al ejecutar la funcion bandera, depende del contexto, entonces cuando se ejecuta otra bandera hay que hacer un salto de tarea?
	// Esto significa que el scheduler corre en el contexto de la tarea, o sea usuario
	// Cómo hace para saltar a Idle si está en usuario, o para correr la int del reloj? Tiene que ser root?
	// La funcion bandera ya está determinada por la tarea bandera, con solo hacer el salto ya deberia empezar a ejecutarse?
	tasks[0] = (tarea_1 << 3) + 0x03;
	tasks[1] = (tarea_2 << 3) + 0x03;
	tasks[2] = (tarea_3 << 3) + 0x03;
	tasks[3] = (tarea_4 << 3) + 0x03;
	tasks[4] = (tarea_5 << 3) + 0x03;
	tasks[5] = (tarea_6 << 3) + 0x03;
	tasks[6] = (tarea_7 << 3) + 0x03;
	tasks[7] = (tarea_8 << 3) + 0x03;

	flags[0] = (tarea_1_bandera << 3) + 0x03;
	flags[1] = (tarea_2_bandera << 3) + 0x03;
	flags[2] = (tarea_3_bandera << 3) + 0x03;
	flags[3] = (tarea_4_bandera << 3) + 0x03;
	flags[4] = (tarea_5_bandera << 3) + 0x03;
	flags[5] = (tarea_6_bandera << 3) + 0x03;
	flags[6] = (tarea_7_bandera << 3) + 0x03;
	flags[7] = (tarea_8_bandera << 3) + 0x03;

	currTask = -1; 		// Para que de correctamente en la primera iteracion de sched_proximo_indice()
	currFlag = -1;

	modoBandera = 0;
	cicloBandera = 0;
}

// Esta funcion unicamente se encarga de devolver el indice de la proxima tarea a ejecutar, no toma en cuenta nada mas
unsigned short sched_proximo_indice() {
	if (currTask == 7)
		currTask = 0;
	else
		currTask++;

	int j = 0;
	while (tasks[currTask] == 0 && j < CANT_TAREAS){
		currTask++;
		if (currTask == CANT_TAREAS)
			currTask = 0;
		j++;
	}

    return tasks[currTask];
}

unsigned short sched_proxima_bandera(){
	currFlag++;

	while (flags[currFlag] == 0 && currFlag < CANT_TAREAS)
		currFlag++;

	int current = currFlag;
	// Si currFlag es 7 u 8, significa que ya terminé de ejecutar todas las banderas
	if (currFlag >= CANT_TAREAS - 1){
		cicloBandera = 0;
		modoBandera = FALSE;
		currFlag = -1;
	}

	if (current == CANT_TAREAS)
		return 0;
	else
		return flags[current];
}

unsigned short proximo_indice(){
	// Como hago para saber si estoy ejecutando una bandera y tengo que matarla?
	if (modoBandera)
		return sched_proxima_bandera();
	else{
		cicloBandera++;
		if (cicloBandera == 3)
			modoBandera = TRUE;			// En el prox tick se ejecuta sched_proxima_bandera()
		return sched_proximo_indice();
	}
}