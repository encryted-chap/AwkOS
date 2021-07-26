section .text
    global memcpy               ; copies bytes worth of data
    global memcpy_w             ; copies words worth of data
memcpy:
    pop     ecx                 ; times to rep
    pop     esi                 ; from
    pop     edi                 ; to
    rep     movsb
    ret
memcpy_w:
    pop     ecx                 ; times to rep
    pop     esi                 ; from
    pop     edi                 ; to
    rep     movsw
    ret