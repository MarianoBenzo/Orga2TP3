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

extern screen_modo_estado

extern screen_modo_mapa


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

global _isr32
global _isr33
global _isr50
global _isr66


%macro ISR 1
global _isr%1

_isr%1:
.loopear:
	push %1
	call atender_int

    ; To Infinity And Beyond!!
    mov eax, 0xFFF2
    mov ebx, 0xFFF2
    mov ecx, 0xFFF2
    mov edx, 0xFFF2
    jmp $
%endmacro


;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
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
    call fin_intr_pic1
    call screen_proximo_reloj

    iret

_isr50:
    iret

_isr66:
    iret

screen_proximo_reloj:
    call proximo_reloj
    ret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushad
    call  fin_intr_pic1
    
    in al, 0x60
    cmp al, 0x32
    jne .estado
    call screen_modo_mapa
    .estado:
        cmp al, 0x12
        jne .numero
        call screen_modo_estado
    .numero:
        mov ebx, eax
        dec eax
        imprimir_texto_mp eax, 1, 0x0f, 0, 79 ;Terminar
    .fin:
        popad
        iret 
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

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
