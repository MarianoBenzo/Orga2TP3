; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start

extern screen_pintar_pantalla
extern screen_modo_mapa
extern screen_modo_estado

extern mmu_inicializar_dir_kernel 
extern mmu_inicializar_dir_tarea
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
    call habilitar_A20

    ; cargar la GDT
    ; la estructura gdt_descriptor contiene los datos necesarios para cargar en GDTR (en orden)
    LGDT [GDT_DESC]      

    ; setear el bit PE del registro CR0
    mov eax, CR0
    or eax, 1
    mov CR0, eax

    ; pasar a modo protegido
    ; 0x90 = 10010 000 accedo a la entrada 18 de GDT (kernel_code)
    jmp 0x90:modoProtegido     

BITS 32
modoProtegido:
    xor eax, eax
    ; ss describe el segmento donde esta la pila (kernel_data)
    ; acomodar los segmentos
    mov ax, 0x98
    mov ss, ax
    mov ds, ax
    mov gs, ax
    mov fs, ax
    mov ax, 0xB0
    mov es, ax
    ; setear la pila
    mov esp, 0x27000

    ; pintar pantalla, todos los colores, que bonito!
    call screen_pintar_pantalla
    ;call screen_modo_mapa
    call screen_modo_estado

    ; inicializar el manejador de memoria

    ; inicializar el directorio de paginas
    mov eax, 0x27000
    mov CR3, eax
    call mmu_inicializar_dir_kernel

    ; inicializar memoria de tareas

    ; habilitar paginacion
    mov eax, CR0
    or eax, 0x80000000
    mov CR0, eax

    ; inicializar tarea idle

    ; inicializar todas las tsss

    ; inicializar entradas de la gdt de las tsss

    ; inicializar el scheduler
    
    ; inicializar la IDT
    call idt_inicializar
    LIDT [IDT_DESC]
    call resetear_pic
    call habilitar_pic
    sti

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
