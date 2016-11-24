/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"
#include "screen.h"

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
	tasks[0] = (tarea_1 << 3) + 0x00;
	tasks[1] = (tarea_2 << 3) + 0x00;
	tasks[2] = (tarea_3 << 3) + 0x00;
	tasks[3] = (tarea_4 << 3) + 0x00;
	tasks[4] = (tarea_5 << 3) + 0x00;
	tasks[5] = (tarea_6 << 3) + 0x00;
	tasks[6] = (tarea_7 << 3) + 0x00;
	tasks[7] = (tarea_8 << 3) + 0x00;

	flags[0] = (tarea_1_bandera << 3) + 0x00;
	flags[1] = (tarea_2_bandera << 3) + 0x00;
	flags[2] = (tarea_3_bandera << 3) + 0x00;
	flags[3] = (tarea_4_bandera << 3) + 0x00;
	flags[4] = (tarea_5_bandera << 3) + 0x00;
	flags[5] = (tarea_6_bandera << 3) + 0x00;
	flags[6] = (tarea_7_bandera << 3) + 0x00;
	flags[7] = (tarea_8_bandera << 3) + 0x00;

	currTask = -1; 		// Para que de correctamente en la primera iteracion de sched_proximo_indice()
	currFlag = -1;

	modoBandera = FALSE;
	cicloBandera = 0;
	corriendoBandera = FALSE;
}

// Esta funcion unicamente se encarga de devolver el indice de la proxima tarea a ejecutar, no toma en cuenta nada mas
unsigned short sched_proximo_indice() {
	currTask = (currTask + 1) % 8;

	int j = 0;
	while (tasks[currTask] == 0 && j < CANT_TAREAS){
		currTask = (currTask + 1) % 8;
		j++;
	}
	pintar_reloj_tarea(currTask);

    return tasks[currTask];
}

unsigned short sched_proxima_bandera(){
	currFlag++;

	while (flags[currFlag] == 0 && currFlag < CANT_TAREAS)
		currFlag++;

	// Si currFlag es 7 u 8, significa que ya terminé de ejecutar todas las banderas
	if (currFlag >= CANT_TAREAS - 1){
		cicloBandera = 0;
		modoBandera = FALSE;
		if (currFlag == CANT_TAREAS)	// si currFlag es 8, no se va a ejecutar una bandera y no se pone en false
			corriendoBandera = FALSE;
	}
	pintar_reloj_bandera(currFlag);

	if (currFlag == CANT_TAREAS)
		return 0;
	else
		return flags[currFlag];
}

unsigned short proximo_indice(){
	if (corriendoBandera){
		tasks[currFlag] = 0x00;
		flags[currFlag] = 0x00;
		borrar(currFlag);
	}
	if (modoBandera){
		corriendoBandera = TRUE;
		return sched_proxima_bandera();
	}else{
		cicloBandera++;
		// currFlag lo actualizo aca porque si lo hago en sched_proxima_bandera()
		// al generar un problema la bandera 7, se intentaria desalojar la bandera -1 
		currFlag = -1;					
		if (cicloBandera == 3)
			modoBandera = TRUE;			// En el prox tick se ejecuta sched_proxima_bandera()
		return sched_proximo_indice();
	}
}

void desalojar_tarea_actual(){
	if (corriendoBandera){
		flags[currFlag] = 0x00;
		tasks[currFlag] = 0x00;
		borrar(currFlag);
	} else{
		flags[currTask] = 0x00;
		tasks[currTask] = 0x00;
		borrar(currTask);
	}
}

int current_task(){
	return currTask;
}

int current_flag(){
	return currFlag;
}