.code

PUBLIC ExtractKey
PUBLIC VigenereEncrypt
PUBLIC VigenereDecrypt

; =============================================================
; strlen — вычисляет длину строки
; Вход: RCX — указатель на строку
; Выход: RAX — длина
; =============================================================
StrLen proc
    xor rax, rax
LEN_LOOP:
    cmp byte ptr [rcx+rax], 0
    je LEN_DONE
    inc rax
    jmp LEN_LOOP
LEN_DONE:
    ret
StrLen endp



; =============================================================
; ExtractKey
; Вход:
;   RCX — строка "Фамилия Имя Отчество"
;   RDX — буфер под ключ
; Ключ = третьи буквы каждого слова
; =============================================================
ExtractKey proc
    push rbx
    push r12

    mov r12, rcx    ; входная строка
    mov rbx, rdx    ; выходной буфер
    xor rcx, rcx    ; счетчик букв в слове

EK_NEXT:
    mov al, [r12]
    test al, al
    jz EK_FINISH

    cmp al, ' '
    jne EK_INWORD
    mov rcx, 0
    jmp EK_SKIP

EK_INWORD:
    inc rcx
    cmp rcx, 3
    jne EK_SKIP
    mov [rbx], al
    inc rbx

EK_SKIP:
    inc r12
    jmp EK_NEXT

EK_FINISH:
    mov byte ptr [rbx], 0
    pop r12
    pop rbx
    ret
ExtractKey endp



; =============================================================
; VigenereEncrypt
; Вход:
;   RCX — указатель на строку
;   RDX — указатель на ключ
; Результат пишется обратно в RCX
; =============================================================
VigenereEncrypt proc
    push rbx
    push r12
    push r13

    mov r12, rcx    ; текст
    mov r13, rdx    ; ключ
    mov rbx, rdx    ; начало ключа

    mov rcx, r13
    call StrLen
    mov r8, rax     ; длина ключа

ENC_LOOP:
    mov al, [r12]
    test al, al
    jz ENC_DONE

    mov bl, [r13]
    test bl, bl
    jnz ENC_APPLY

    mov r13, rbx
    mov bl, [r13]

ENC_APPLY:
    add al, bl
    mov [r12], al

    inc r12
    inc r13
    jmp ENC_LOOP

ENC_DONE:
    pop r13
    pop r12
    pop rbx
    ret
VigenereEncrypt endp



; =============================================================
; VigenereDecrypt
; Вход:
;   RCX — указатель на строку
;   RDX — указатель на ключ
; Результат пишется обратно в RCX
; =============================================================
VigenereDecrypt proc
    push rbx
    push r12
    push r13

    mov r12, rcx
    mov r13, rdx
    mov rbx, rdx

    mov rcx, r13
    call StrLen
    mov r8, rax

DEC_LOOP:
    mov al, [r12]
    test al, al
    jz DEC_DONE

    mov bl, [r13]
    test bl, bl
    jnz DEC_APPLY

    mov r13, rbx
    mov bl, [r13]

DEC_APPLY:
    sub al, bl
    mov [r12], al

    inc r12
    inc r13
    jmp DEC_LOOP

DEC_DONE:
    pop r13
    pop r12
    pop rbx
    ret
VigenereDecrypt endp

end
