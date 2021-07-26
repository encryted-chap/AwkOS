section .text
grub_magic:
    align 4
    dd 0x1BADB002
    dd 0
    dd - (0x1BADB002+0)

    %include "Modes.asm"
    %include "Memory.asm"

    extern  ENTRY
    global  start
    global BootDrive
    

start:
    mov     [BootDrive], dl         ; store Boot Disk ID
    
    call    ENTRY
    jmp     onKill

onKill:
    mov     ecx, 0xFF
clearstack:
    pop     eax
    rep     jmp clearstack
    ; handle end

    hlt
section .data
    BootDrive:   db 0