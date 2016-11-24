/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/


#include "idt.h"
#include "isr.h"
#include "colors.h"
#include "screen.h"
#include "sched.h"
#include "mmu.h"
#include "i386.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

void atender_int(int n, int ebx, int ecx, int edx, int esi, int edi, int ebp, int esp, int cr0, int cr2, int cr3, int cr4, int cs, int ds, int es, int fs, int gs, int ss, int eflags, int eip, int eax) {
    int tarea = current_task();
    desalojar_tarea_actual();

    int c;
    for (c = 50; c < VIDEO_COLS - 3; c++){
        print(" ", c, 1, C_BG_CYAN, VIDEO_ESTADO);
    }

    switch(n){
        case 0:
            print("Divide Error", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 1:
            print("Reserved", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 2:
            print("NMI Interrupt", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 3:
            print("BreakPoint", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 4:
            print("Overflow", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 5:
            print("BOUND Range Exceeded", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 6:
            print("Invalid Opcode", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 7:
            print("Device Not Available", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 8:
            print("Double Fault", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 9:
            print("Coprocessor Segment Overrun", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 10:
            print("Invalid TSS", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 11:
            print("Segment Not Present", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 12:
            print("Stack-Segment Fault", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 13:
            print("General protection fault", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 14:
            print("Page fault", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 15:
            print("Intel Reserved", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 16:
            print("x86 FPU Floating-Point Error", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 17:
            print("Alignment Check", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 18:
            print("Machine Check", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;
        case 19:
            print("SIMD Floating-Point Exception", 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            break;

        default:
            print_int(n, 50, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
    }
    print("NAVIO ", 71, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
    print_int(tarea + 1, 77, 1, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);

    print("EAX ", 51, 2, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(eax, 8, 55, 2, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("EBX ", 51, 3, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(ebx, 8, 55, 3, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("ECX ", 51, 4, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(ecx, 8, 55, 4, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("EDX ", 51, 5, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(edx, 8, 55, 5, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("ESI ", 51, 6, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(esi, 8, 55, 6, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);    

    print("EDI ", 51, 7, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(edi, 8, 55, 7, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);     

    print("EBP ", 51, 8, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(ebp, 8, 55, 8, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);       

    print("ESP ", 51, 9, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(esp, 8, 55, 9, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);    

    print("EIP ", 51, 10, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(eip, 8, 55, 10, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);    

    print("CR0 ", 51, 11, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(cr0, 8, 55, 11, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);    

    print("CR2 ", 51, 12, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(cr2, 8, 55, 12, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);  

    print("CR3 ", 51, 13, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(cr3, 8, 55, 13, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);      

    print("CR4 ", 51, 14, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(cr4, 8, 55, 14, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);    

    print("CS ", 66, 2, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(cs, 8, 69, 2, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);   

    print("DS ", 66, 3, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(ds, 8, 69, 3, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("ES ", 66, 4, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(es, 8, 69, 4, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("FS ", 66, 5, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(fs, 8, 69, 5, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("GS ", 66, 6, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(gs, 8, 69, 6, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("SS ", 66, 7, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(ss, 8, 69, 7, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    print("EFLAGS", 66, 9, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO);
    print_hex(eflags, 8, 69, 10, C_FG_WHITE + C_BG_BLACK, VIDEO_ESTADO, 0);

    screen_modo_estado();
}

void int_teclado(int n){
    int makeCode = n - 0x80;
    if(makeCode < 0x0C && makeCode > 0x01)          // es un numero
    {   
        int numero = makeCode;
        if (numero == 0x0B)
            numero = 0;
        else
            numero--;
        print_int(numero, VIDEO_COLS - 1, 0, C_FG_WHITE + (numero%8 << 4), 0xB8000);
    }
    if(makeCode == 0x12)        // E
        screen_modo_estado();

    if(makeCode == 0x32)        // M
        screen_modo_mapa();
}

void anclar(int fisica, int cr3){
    int tarea = current_task();

    mmu_mapear_pagina(0x40002000, cr3, fisica, 0, 0);
    asignar_dir(tarea, fisica, 3);
    tlbflush();
}

void navegar(int fisica_uno, int fisica_dos, int cr3){
    int tarea = current_task();

    mmu_mapear_pagina(0x40000000, cr3, fisica_uno, 1, 1);       // pag codigo 1
    mmu_mapear_pagina(0x40001000, cr3, fisica_dos, 1, 1);       // pag codigo 2
    asignar_dir(tarea, fisica_uno, 1);
    asignar_dir(tarea, fisica_dos, 2);

    unsigned int dir_tarea = dir_codigo_tarea(tarea);
    unsigned char *src = (unsigned char*) dir_tarea;
    unsigned char *dst = (unsigned char*) fisica_uno;
    int i;
    for(i = 0; i < 4096; i++){
        *(dst) = *(src);
        dst++;
        src++;
    }

    dst = (unsigned char*) fisica_dos;
    for(i = 0; i < 4096; i++){
        *(dst) = *(src);
        dst++;
        src++;
    }

    tlbflush();
}

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/


#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x90;                                                                  \
    idt[numero].attr = (unsigned short) 0x8E00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);

void idt_inicializar() {
    IDT_ENTRY(0);
    IDT_ENTRY(1);
    IDT_ENTRY(2);
    IDT_ENTRY(3);
    IDT_ENTRY(4);
    IDT_ENTRY(5);
    IDT_ENTRY(6);
    IDT_ENTRY(7);
    IDT_ENTRY(8);
    IDT_ENTRY(9);
    IDT_ENTRY(10);
    IDT_ENTRY(11);
    IDT_ENTRY(12);
    IDT_ENTRY(13);
    IDT_ENTRY(14);
    IDT_ENTRY(15);
    IDT_ENTRY(16);
    IDT_ENTRY(17);
    IDT_ENTRY(18);
    IDT_ENTRY(19);

    IDT_ENTRY(32);      // Reloj
    IDT_ENTRY(33);      // Teclado

    idt[0x50].offset_0_15 = (unsigned short) ((unsigned int)(&_isrx50) & (unsigned int) 0xFFFF);        
    idt[0x50].segsel = (unsigned short) 0x90;                                                          
    idt[0x50].attr = (unsigned short) 0xEE00;                                                           // 0xEE00 = 1110 1110 0000 0000
    idt[0x50].offset_16_31 = (unsigned short) ((unsigned int)(&_isrx50) >> 16 & (unsigned int) 0xFFFF);

    idt[0x66].offset_0_15 = (unsigned short) ((unsigned int)(&_isrx66) & (unsigned int) 0xFFFF);        
    idt[0x66].segsel = (unsigned short) 0x90;                                                          
    idt[0x66].attr = (unsigned short) 0xEE00;                                                           // 0xEE00 = 1110 1110 0000 0000
    idt[0x66].offset_16_31 = (unsigned short) ((unsigned int)(&_isrx66) >> 16 & (unsigned int) 0xFFFF);
}
