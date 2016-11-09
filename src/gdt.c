/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"
#include "tss.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [kernel_code] = (gdt_entry) {
        (unsigned short)    0xFFFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x06,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ 
        (unsigned char)     0x01,           /* g            */  
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [kernel_data] = (gdt_entry) {
        (unsigned short)    0xFFFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s        	*/
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x06,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ 
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
	
    [user_code] = (gdt_entry) {
        (unsigned short)    0xFFFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s        	*/
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x06,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ 
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
	
    [user_data] = (gdt_entry) {
        (unsigned short)    0xFFFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s        	*/
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x06,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ 
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
	
    [pantalla] = (gdt_entry) {
        (unsigned short)    0x0FFF,         /* limit[0:15]  1000 = 4096, en bytes*/
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0x0B,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s        	*/
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */ 
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [indice_idle] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                             /* base[0:15]   */
        (unsigned char)     0x00,                               /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x00,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [indice_inicial] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                             /* base[0:15]   */
        (unsigned char)     0x00,                               /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x00,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_1] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                             /* base[0:15]   */
        (unsigned char)     0x00,                               /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_2] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                             /* base[0:15]   */
        (unsigned char)     0x00,                               /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_3] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_4] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                             /* base[0:15]   */
        (unsigned char)     0x00,                               /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_5] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_6] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_7] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_8] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_1_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_2_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_3_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_4_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_5_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_6_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_7_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },

    [tarea_8_bandera] = (gdt_entry) {
        (unsigned short)    0x0067,                             /* limit[0:15]  0x67 = 104 bytes*/
        (unsigned short)    0x0000,                   /* base[0:15]   */
        (unsigned char)     0x00,            /* base[23:16]  */
        (unsigned char)     0x09,                               /* type         */
        (unsigned char)     0x00,                               /* s            */
        (unsigned char)     0x00,                               /* dpl          */
        (unsigned char)     0x01,                               /* p            */
        (unsigned char)     0x00,                               /* limit[16:19] */
        (unsigned char)     0x00,                               /* avl          */
        (unsigned char)     0x00,                               /* l            */
        (unsigned char)     0x01,                               /* db           */ 
        (unsigned char)     0x00,                               /* g            */
        (unsigned char)     0x00,                               /* base[31:24]  */
    },
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};
