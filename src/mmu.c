/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"


void mmu_inicializar_dir_kernel() {

	struct dir_page_entry *dir_entry = (dir_page_entry*) 0x27000;
	int i;

	dir_entry[0].dir_base = 0x28;
    dir_entry[0].disponible = 0;
    dir_entry[0].global = 0;
    dir_entry[0].page_size = 0;
    dir_entry[0].ignored = 0;
    dir_entry[0].accessed = 0;
    dir_entry[0].cache_disable = 0;
    dir_entry[0].write_through = 0;
    dir_entry[0].user = 0;
    dir_entry[0].rw = 1;
    dir_entry[0].present = 1;
    
    struct tab_page_entry *tab_entry = (tab_page_entry*) 0x28000; 
    //inicializo los 1024 elementos de la tabla apuntada por el primer dir
    for(i=0; i<1024; i++){

		tab_entry[i].dir_base = i;
	    tab_entry[i].disponible = 0;
	    tab_entry[i].global = 0;
	    tab_entry[i].page_attribute = 0;
	    tab_entry[i].dirty = 0;
	    tab_entry[i].accessed = 0;
	    tab_entry[i].cache_disable = 0;
	    tab_entry[i].write_through = 0;
	    tab_entry[i].user = 0;
	    tab_entry[i].rw = 1;
	    tab_entry[i].present = 1;

	}




	dir_entry[1].dir_base = 0x30;
    dir_entry[1].disponible = 0;
    dir_entry[1].global = 0;
    dir_entry[1].page_size = 0;
    dir_entry[1].ignored = 0;
    dir_entry[1].accessed = 0;
    dir_entry[1].cache_disable = 0;
    dir_entry[1].write_through = 0;
    dir_entry[1].user = 0;
    dir_entry[1].rw = 1;
    dir_entry[1].present = 1;
    
    struct tab_page_entry *tab_entry2 = (tab_page_entry*) 0x30000; 
    //inicializo los 896 elementos de la tabla apuntada por el primer dir
    for(i=0; i < 1024; i++){

	    if (i < 896){

			tab_entry2[i].dir_base = i + 1024;
		    tab_entry2[i].disponible = 0;
		    tab_entry2[i].global = 0;
		    tab_entry2[i].page_attribute = 0;
		    tab_entry2[i].dirty = 0;
		    tab_entry2[i].accessed = 0;
		    tab_entry2[i].cache_disable = 0;
		    tab_entry2[i].write_through = 0;
		    tab_entry2[i].user = 0;
		    tab_entry2[i].rw = 1;
		    tab_entry2[i].present = 1;

		} else
		{

			tab_entry2[i].dir_base = i + 1024;
		    tab_entry2[i].disponible = 0;
		    tab_entry2[i].global = 0;
		    tab_entry2[i].page_attribute = 0;
		    tab_entry2[i].dirty = 0;
		    tab_entry2[i].accessed = 0;
		    tab_entry2[i].cache_disable = 0;
		    tab_entry2[i].write_through = 0;
		    tab_entry2[i].user = 0;
		    tab_entry2[i].rw = 1;
		    tab_entry2[i].present = 1;		
		    
		}
	}



	for(i=2; i<1024; i++){

		dir_entry[i].dir_base = 0;
	    dir_entry[i].disponible = 0;
	    dir_entry[i].global = 0;
	    dir_entry[i].page_size = 0;
	    dir_entry[i].ignored = 0;
	    dir_entry[i].accessed = 0;
	    dir_entry[i].cache_disable = 0;
	    dir_entry[i].write_through = 0;
	    dir_entry[i].user = 0;
	    dir_entry[i].rw = 0;
	    dir_entry[i].present = 0;

	}
}


void mmu_inicializar() {
}

