; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


;; PIC
extern fin_intr_pic1

extern atender_int
extern int_teclado
extern navegar
extern anclar
extern redirigir_misil

extern screen_modo_estado
extern screen_modo_mapa
extern pintar_buffer_bandera

extern mmu_mapear_pagina

extern proximo_indice

;; Variables globales
extern corriendoBandera

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

global _isr32
global _isr33
global _isrx50
global _isrx66


%macro ISR 1
global _isr%1

_isr%1:
    ;push eflags
    push eax
    xor eax, eax
    mov ax, ss
    push eax
    mov ax, gs
    push eax
    mov ax, fs
    push eax
    mov ax, es
    push eax
    mov ax, ds
    push eax
    mov ax, cs
    push eax
    mov eax, cr4
    push eax
    mov eax, cr3
    push eax
    mov eax, cr2
    push eax
    mov eax, cr0
    push eax
    ;push eip
    push esp
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push %1
	call atender_int

    jmp 0xB8:0x00   ; tarea_idle
%endmacro


;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
offset:					dd 0x00
selector:				dw 0x00
reloj_numero:           dd 0x00000000
reloj:                  db '|/-\'


;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
_isr32:
	pushad

    call screen_proximo_reloj

    call proximo_indice
    cmp ax, 0
    je .noJump
    	mov [selector], ax
    	call fin_intr_pic1
        xchg bx, bx
    	jmp far [offset]
    	jmp .fin
    .noJump:
    	call fin_intr_pic1
    .fin:
    	popad
    iret

screen_proximo_reloj:
    call proximo_reloj
    ret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushad
    call fin_intr_pic1
    
    xor eax, eax
    in al, 0x60
    push eax
    call int_teclado
    
    pop eax
    popad
    iret 
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

_isrx50:
    pushad

    cmp eax, 0x923
    je .anclar
    cmp eax, 0x83A
    je .misilazo
    cmp eax, 0xAEF
    je .navegar
    jmp .fin

    .anclar:
        mov eax, CR3
        push eax                ; parametro "cr3"
        push ebx                ; parametro "fisica"
        call anclar
        pop ebx
        pop eax

        jmp .fin
    .misilazo:
        ; EBX = direccion fisica donde se disparara el misil
        ; ECX = direccion relativa al espacio de la tarea donde se encuentra el misil
        xor eax, eax
        mov edx, ecx
        mov ecx, 0x61   ; 0x61 = 97
        .ciclo:
            mov al, [edx]
            mov [ebx], al
            inc edx
            inc eax
            loop .ciclo
        push ebx
        call redirigir_misil
        pop ebx
        jmp .fin
    .navegar:
        ; EBX/ECX = direccion fisica del area de usuario para la primera/segunda pagina de codigo
        mov eax, CR3
        push eax
        push ecx
        push ebx
        call navegar
        pop ebx
       	pop ecx
       	pop eax
    .fin:
        popad
        call screen_modo_mapa
        jmp 0xB8:0x00
        iret

_isrx66:
    push eax
    call pintar_buffer_bandera
    pop eax
    mov byte [corriendoBandera], 0x00
    jmp 0xB8:0x00       ; tarea_idle
    iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
    pushad

    inc DWORD [reloj_numero]
    mov ebx, [reloj_numero]
    cmp ebx, 0x4
    jl .ok
        mov DWORD [reloj_numero], 0x0
        mov ebx, 0
    .ok:
        add ebx, reloj
        imprimir_texto_mp ebx, 1, 0x0f, 24, 79

    popad
    ret
