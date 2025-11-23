.code

; ---------------------------------------------------------
; void AsmVigenereCipher(char* text (RCX), const char* key (RDX), bool encrypt (R8))
; ---------------------------------------------------------
AsmVigenereCipher PROC
    push rbx
    push rsi
    push rdi
    
    mov rsi, rcx        ; text
    mov rdi, rdx        ; key
    
    test rsi, rsi
    jz Done
    test rdi, rdi
    jz Done

    xor r10, r10        ; Индекс ключа
    
LoopChar:
    mov al, [rsi]       ; Загружаем символ
    test al, al
    jz Done

    ; Проверка на 'A'...'Z'
    cmp al, 'A'
    jb NextChar
    cmp al, 'Z'
    jbe IsUpper

    ; Проверка на 'a'...'z'
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
    ; Получаем символ ключа (циклически)
    mov r11, r10
    ; Упрощенно берем символ по индексу, если 0 - сброс
    mov dl, [rdi + r10]
    test dl, dl
    jnz KeyOK
    xor r10, r10
    mov dl, [rdi]
KeyOK:
    
    sub dl, 'a'         ; смещение ключа (считаем ключ в lowercase)
    sub al, bl          ; al = text - base
    
    cmp r8b, 1          ; Encrypt?
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
    
    add al, bl          ; Восстанавливаем ASCII
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

; ---------------------------------------------------------
; int AsmBuyTicket(int* ticketsLeft (RCX), int* ticketsSold (RDX), int count (R8))
; ---------------------------------------------------------
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

; ---------------------------------------------------------
; int AsmCheckFilter(const char* city (RCX), const char* target (RDX), 
;                    int arrH (R8), int arrM (R9), 
;                    int minH (Stack), int maxH (Stack))
; ---------------------------------------------------------
AsmCheckFilter PROC
    ; Сравнение строк
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
    
    ; Проверка времени (аргументы 5 и 6 в стеке)
    ; Shadow space (32) + ret (8) = 40
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