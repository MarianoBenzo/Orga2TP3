/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"


unsigned int prox_pagina(){
	p += 0x1000;
	return p;
}

void mmu_inicializar_dir_kernel() {
	dir_page_entry *dir_entry = (dir_page_entry*) 0x27000;
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
    
    tab_page_entry *tab_entry = (tab_page_entry*) 0x28000; 
    //inicializo los 1024 elementos de la tabla apuntada por el primer dir
    for(i = 0; i < 1024; i++){
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
    
    tab_page_entry *tab_entry2 = (tab_page_entry*) 0x30000; 
    //inicializo los 896 elementos de la tabla apuntada por el primer dir
    for(i = 0; i < 1024; i++){
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
			//Consultar que hacer con el resto de las entradas
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

	for(i = 2; i < 1024; i++){
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

#define PDE_INDEX(virtual)  virtual >> 22
#define PTE_INDEX(virtual)  (virtual << 10) >> 22
#define ALIGN(dir) 			(dir << 12)

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){
	unsigned int pd_index = PDE_INDEX(virtual);
	unsigned int pt_index = PTE_INDEX(virtual);
	dir_page_entry *dir_entry = (dir_page_entry*) cr3;

	dir_page_entry pd = dir_entry[pd_index];
	tab_page_entry *pt;
	//Ver bit de presente en pd
	//Si esta en 0, crear una tabla (e inicializar todas sus entradas)
	//Inicializar la entrada correspondiente
	if (pd.present == 0)
	{
		unsigned int dir = prox_pagina();
		pt = (tab_page_entry*) dir;
    	for(i = 0; i < 1024; i++){
			pt[i].dir_base = 0;
		    pt[i].disponible = 0;
		    pt[i].global = 0;
		    pt[i].page_attribute = 0;
		    pt[i].dirty = 0;
		    pt[i].accessed = 0;
		    pt[i].cache_disable = 0;
		    pt[i].write_through = 0;
		    pt[i].user = 0;
		    pt[i].rw = 1;
		    pt[i].present = 1;
		}
		pd.dir_base = (dir >> 12);
		pd.user = 1;				// Marcar de usuario?
		pd.rw = 1;
		pd.present = 1;
	}else{
		pt = (tab_page_entry*) ALIGN(pd.dir_base);
	}

	tab_page_entry pte = pt[pt_index];
	pte.dir_base = (fisica >> 12);
	pte.disponible = 0;
	pte.global = 0;
	pte.page_attribute = 0;
	pte.dirty = 0;
	pte.accessed = 0;
	pte.cache_disable = 0;
	pte.write_through = 0;
	pte.user = 1;
	pte.rw = 1;
	pte.present = 1;	
}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
	unsigned int pd_index = PDE_INDEX(virtual);
	unsigned int pt_index = PTE_INDEX(virtual);
	dir_page_entry *dir_entry = (dir_page_entry*) cr3;

	dir_page_entry pd = dir_entry[pd_index];
	tab_page_entry *pt = (tab_page_entry*) ALIGN(pd.dir_base);
	tab_page_entry pte = pt[pt_index];

	pte.dir_base = 0;
	pte.disponible = 0;
	pte.global = 0;
	pte.page_attribute = 0;
	pte.dirty = 0;
	pte.accessed = 0;
	pte.cache_disable = 0;
	pte.write_through = 0;
	pte.user = 1;
	pte.rw = 1;
	pte.present = 1;			//Hay que mantener el bit de presente? Qué implica?

	pd.dir_base = 0;			
	pd.user = 0;				//Hay que limpiar los flags de usuario y r/w?
	pd.rw = 0;
	pd.present = 0;
}

void mmu_inicializar() {
}

