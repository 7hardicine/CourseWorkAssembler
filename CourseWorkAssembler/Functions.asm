.code

AsmVigenereCipher PROC
    push rbx
    push rsi
    push rdi
    
    mov rsi, rcx       
    mov rdi, rdx       
    
    test rsi, rsi
    jz Done
    test rdi, rdi
    jz Done

    xor r10, r10        
    
LoopChar:
    mov al, [rsi]     
    test al, al
    jz Done

    cmp al, 'A'
    jb NextChar
    cmp al, 'Z'
    jbe IsUpper

    cmp al, 'a'
    jb NextChar
    cmp al, 'z'
    jbe IsLower
    
    jmp NextChar

IsUpper:
    mov bl, 'A'
    jmp Process
IsLower:
    mov bl, 'a'

Process:
    mov r11, r10
    mov dl, [rdi + r10]
    test dl, dl
    jnz KeyOK
    xor r10, r10
    mov dl, [rdi]
KeyOK:
    
    sub dl, 'a'        
    sub al, bl         
    
    cmp r8b, 1          
    je DoEncrypt
    
    ; Decrypt
    sub al, dl
    add al, 26
    jmp CalcMod
    
DoEncrypt:
    add al, dl

CalcMod:
    mov ah, 0
    mov dl, 26
    div dl
    mov al, ah
    
    add al, bl         
    mov [rsi], al

    inc r10
    
NextChar:
    inc rsi
    jmp LoopChar

Done:
    pop rdi
    pop rsi
    pop rbx
    ret
AsmVigenereCipher ENDP

AsmBuyTicket PROC
    mov eax, [rcx]
    cmp eax, r8d        ; if left < count
    jl Fail
    
    sub eax, r8d
    mov [rcx], eax      ; left -= count
    
    mov eax, [rdx]
    add eax, r8d
    mov [rdx], eax      ; sold += count
    
    mov eax, 1          ; return true
    ret
Fail:
    xor eax, eax
    ret
AsmBuyTicket ENDP

AsmCheckFilter PROC
    push rsi
    push rdi
    
    mov rsi, rcx
    mov rdi, rdx
CompareLoop:
    mov al, [rsi]
    mov bl, [rdi]
    cmp al, bl
    jne StringsNotEqual
    test al, al
    jz StringsEqual
    inc rsi
    inc rdi
    jmp CompareLoop
    
StringsNotEqual:
    pop rdi
    pop rsi
    xor eax, eax
    ret

StringsEqual:
    pop rdi
    pop rsi

    mov eax, [rsp + 40] ; minH
    mov edx, [rsp + 48] ; maxH
    
    cmp r8d, eax
    jl TimeFail
    cmp r8d, edx
    jg TimeFail
    
    mov eax, 1
    ret

TimeFail:
    xor eax, eax
    ret
AsmCheckFilter ENDP

END