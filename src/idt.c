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

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

void atender_int(int n) {
    unsigned short attr = C_FG_RED;
    limpiar_pantalla();
    print("Se genero la interrupcion ", 0, 0, attr);
    print_int(n, 26, 0, C_FG_WHITE);
    if (n == 0)
        print("(Division por cero)", 0, 1, C_FG_GREEN);
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
        print_int(numero, VIDEO_COLS - 1, 0, C_FG_WHITE + (numero%8 << 4));
    }
    if(makeCode == 0x12)        // E
        screen_modo_estado();

    if(makeCode == 0x32)        // M
        screen_modo_mapa();
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

    IDT_ENTRY(50);
    IDT_ENTRY(66);
}
