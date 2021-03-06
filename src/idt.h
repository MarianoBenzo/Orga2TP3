/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#ifndef __IDT_H__
#define __IDT_H__


/* Struct de descriptor de IDT */
typedef struct str_idt_descriptor {
    unsigned short  idt_length;
    unsigned int    idt_addr;
} __attribute__((__packed__)) idt_descriptor;

/* Struct de una entrada de la IDT */
typedef struct str_idt_entry_fld {
    unsigned short offset_0_15;
    unsigned short segsel;
    unsigned short attr;
    unsigned short offset_16_31;
} __attribute__((__packed__, aligned (8))) idt_entry;

extern idt_entry idt[];
extern idt_descriptor IDT_DESC;

void idt_inicializar();

void atender_int(int n, int ebx, int ecx, int edx, int esi, int edi, int ebp, int esp, int cr0, int cr2, int cr3, int cr4, int cs, int ds, int es, int fs, int gs, int ss, int eflags, int eip, int eax);
void int_teclado(int n);

void navegar(int fisica_uno, int fisica_dos, int cr3);
void anclar(int fisica, int cr3);

#endif  /* !__IDT_H__ */
