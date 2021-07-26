section .data
    ReturnID16: dw 0
    ReturnID32: dd 0
    GDT:        times 6 db 0
IDT:    
    dw 0x3ff
    dd  0
savcr0:
    dd 0
section .text
    global RealMode
    global ProtMode
RealMode:
    ; switches from protected mode to real mode
    cli
    
    pop     eax                             ; store return code
    mov     [ReturnID32], eax

    mov     eax, 288                        ; datsel16
    mov     ds, eax
    mov     es, eax
    mov     fs, eax
    mov     gs, eax
    mov     ss, eax

    ; disable paging
    mov     eax, cr0
    mov     [savcr0], eax
    btc     eax, 8                          ; clear 8th bit
    mov     cr0, eax
    jmp     0:RM
RM:
    mov     sp, 0x8000		                ; pick a stack pointer.
	mov     ax, 0		                    ; Reset segment registers to 0.
	mov     ds, ax
	mov     es, ax
	mov     fs, ax
	mov     gs, ax
	mov     ss, ax
	lidt    [IDT]

    ; translate 32 bit return addrs into 16-bit
    mov     eax, [ReturnID32]
    mov     si, ax                          ; low bits of address
    shl     eax, 16                         ; shift high bits into ax
    push    ax
    xor     eax, eax
    sti
    ret
ProtMode:
    ; switches from real mode to protected mode
    pop     ax
    mov     [ReturnID16], ax                ; store return address
    xor     ax, ax

    cli                                         ; disable interrupts
    lgdt    [GDT]                               ; load the global descriptor table
    mov     eax, cr0
    or      al, 1                               ; set prot enable bit
    mov     cr0, eax
    jmp     0x08:PM
PM:
    ; load ds, es, fs, gs, ss, esp
    mov     ebp, 4*16                       ; 16 dwords
    mov     esp, ebp                        ; setup stack

    mov     eax, 0
    mov     ds, eax
    mov     es, eax
    mov     fs, eax
    mov     gs, eax
    mov     ss, eax

    ; translate retid16 into retid32
    mov     ax, [ReturnID16]
    shr     eax, 16                     ; shift ax into high bits of eax
    xor     ax, ax                      ; clear ax
    mov     [ReturnID32], eax           ; store 32 bit return address
    push    eax
    ret                                 ; return
    