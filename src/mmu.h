/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

unsigned int p = 0x30000;

typedef struct dir_page_entry {
    unsigned char   present:1;
    unsigned char   rw:1;
    unsigned char   user:1;
    unsigned char   write_through:1;
    unsigned char   cache_disable:1;
    unsigned char   accessed:1;
    unsigned char   ignored:1;
    unsigned char   page_size:1;
    unsigned char   global:1;
    unsigned char  disponible:3;
    unsigned int  dir_base:20;
} __attribute__((__packed__)) dir_page_entry;

typedef struct tab_page_entry {
    unsigned char   present:1;
    unsigned char   rw:1;
    unsigned char   user:1;
    unsigned char   write_through:1;
    unsigned char   cache_disable:1;
    unsigned char   accessed:1;
    unsigned char   dirty:1;
    unsigned char   page_attribute:1;
    unsigned char   global:1;
    unsigned char  disponible:3;
    unsigned int  dir_base:20;
} __attribute__((__packed__)) tab_page_entry;


void mmu_inicializar_dir_kernel();


#endif	/* !__MMU_H__ */
