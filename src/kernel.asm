; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start


;; GDT
extern GDT_DESC

;; IDT
extern IDT_DESC
extern idt_inicializar

;; PIC
extern resetear_pic
extern habilitar_pic


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; xchg bx, bx

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; habilitar A20

    ; cargar la GDT
    ; la estructura gdt_descriptor contiene los datos necesarios para cargar en GDTR (en orden)
    LGDT [GDT_DESC]      

    ; setear el bit PE del registro CR0
    ; no estoy operando en 16 bits? puedo hacer mov bx:ax, cr0 (y mov cr0, bx:ax)?
    mov eax, CR0
    or eax, 1
    mov CR0, eax

    ; pasar a modo protegido
    jmp 0x08:modoProtegido     

BITS 32
modoProtegido:
    xor eax, eax
    ; hay que setear la pila del kernel en la direccion 0x27000
    ; como cargo 0x270000 (20 bits) si ss es de 16 bits?
    mov ax, 1000b
    mov ss, 
    mov ax, 10000b         ; index: 3 (segmento kernel_data)
    mov ds, ax


    ; acomodar los segmentos

    ; setear la pila

    ; pintar pantalla, todos los colores, que bonito!

    ; inicializar el manejador de memoria

    ; inicializar el directorio de paginas

    ; inicializar memoria de tareas

    ; habilitar paginacion

    ; inicializar tarea idle

    ; inicializar todas las tsss

    ; inicializar entradas de la gdt de las tsss

    ; inicializar el scheduler

    ; inicializar la IDT

    ; configurar controlador de interrupciones

    ; cargar la tarea inicial

    ; saltar a la primer tarea

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
