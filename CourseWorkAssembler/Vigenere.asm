.code
public VigenereEncryptEnglish

; =============================================
; Шифрование Виженера для английского текста
; Вход: RCX - указатель на входную строку (char*)
;       RDX - указатель на ключевую строку (char*)  
;       R8  - указатель на выходной буфер (char*)
; =============================================
VigenereEncryptEnglish proc
    push rbx
    push r12
    push r13
    push r14
    push r15
    
    mov r12, rcx        ; сохраняем входную строку
    mov r13, rdx        ; сохраняем ключевую строку
    mov r14, r8         ; сохраняем выходной буфер
    mov r15, rdx        ; начало ключа для сброса
    
vigenere_loop:
    mov al, [r12]       ; читаем символ из входной строки
    test al, al         ; проверяем конец строки (0)
    jz vigenere_done
    
    ; Проверяем строчные буквы a-z
    cmp al, 'a'
    jb check_uppercase
    cmp al, 'z'
    ja copy_char
    
    ; Обрабатываем строчную букву
process_lower:
    mov rbx, r13        ; текущая позиция в ключе
    mov cl, [rbx]       ; читаем символ ключа
    test cl, cl         ; если ключ закончился - начинаем сначала
    jnz check_key_lower
    mov r13, r15        ; сбрасываем ключ на начало
    mov cl, [r13]
    
check_key_lower:
    ; Пропускаем не-буквенные символы в ключе
    cmp cl, 'a'
    jb check_upper_key_lower
    cmp cl, 'z'
    ja check_upper_key_lower
    jmp encrypt_lower
    
check_upper_key_lower:
    cmp cl, 'A'
    jb skip_key_char_lower
    cmp cl, 'Z'
    ja skip_key_char_lower
    jmp encrypt_lower_upper_key

skip_key_char_lower:
    inc r13             ; пропускаем не-буквенный символ ключа
    jmp process_lower   ; пробуем следующий символ ключа

encrypt_lower:
    ; Строчный ключ для строчной буквы
    sub cl, 'a'         ; cl = смещение ключа (0-25)
    sub al, 'a'         ; al = позиция символа (0-25)
    add al, cl          ; шифруем: (char_pos + key_pos)
    cmp al, 26          ; проверяем выход за пределы алфавита
    jb store_lower
    sub al, 26          ; модуль 26
    
store_lower:
    add al, 'a'         ; обратно в символ
    mov [r14], al
    inc r13             ; переходим к следующему символу ключа
    jmp next_char_v

encrypt_lower_upper_key:
    ; Заглавный ключ для строчной буквы
    sub cl, 'A'         ; cl = смещение ключа (0-25)
    sub al, 'a'         ; al = позиция символа (0-25)
    add al, cl          ; шифруем: (char_pos + key_pos)
    cmp al, 26          ; проверяем выход за пределы алфавита
    jb store_lower
    sub al, 26          ; модуль 26
    jmp store_lower

check_uppercase:
    ; Проверяем заглавные буквы A-Z
    cmp al, 'A'
    jb copy_char
    cmp al, 'Z'
    ja copy_char
    
    ; Обрабатываем заглавную букву
process_upper:
    mov rbx, r13        ; текущая позиция в ключе
    mov cl, [rbx]       ; читаем символ ключа
    test cl, cl         ; если ключ закончился - начинаем сначала
    jnz check_key_upper
    mov r13, r15        ; сбрасываем ключ на начало
    mov cl, [r13]
    
check_key_upper:
    ; Пропускаем не-буквенные символы в ключе
    cmp cl, 'A'
    jb check_lower_key_upper
    cmp cl, 'Z'
    ja check_lower_key_upper
    jmp encrypt_upper
    
check_lower_key_upper:
    cmp cl, 'a'
    jb skip_key_char_upper
    cmp cl, 'z'
    ja skip_key_char_upper
    jmp encrypt_upper_lower_key

skip_key_char_upper:
    inc r13             ; пропускаем не-буквенный символ ключа
    jmp process_upper   ; пробуем следующий символ ключа

encrypt_upper:
    ; Заглавный ключ для заглавной буквы
    sub cl, 'A'         ; cl = смещение ключа (0-25)
    sub al, 'A'         ; al = позиция символа (0-25)
    add al, cl          ; шифруем: (char_pos + key_pos)
    cmp al, 26          ; проверяем выход за пределы алфавита
    jb store_upper
    sub al, 26          ; модуль 26
    
store_upper:
    add al, 'A'         ; обратно в символ
    mov [r14], al
    inc r13             ; переходим к следующему символу ключа
    jmp next_char_v

encrypt_upper_lower_key:
    ; Строчный ключ для заглавной буквы
    sub cl, 'a'         ; cl = смещение ключа (0-25)
    sub al, 'A'         ; al = позиция символа (0-25)
    add al, cl          ; шифруем: (char_pos + key_pos)
    cmp al, 26          ; проверяем выход за пределы алфавита
    jb store_upper
    sub al, 26          ; модуль 26
    jmp store_upper

copy_char:
    ; Не буква - копируем как есть (ключ не двигаем)
    mov [r14], al

next_char_v:
    inc r12             ; переходим к следующему символу входной строки
    inc r14             ; переходим к следующей позиции выходного буфера
    jmp vigenere_loop

vigenere_done:
    mov byte ptr [r14], 0   ; добавляем нулевой терминатор
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    ret
VigenereEncryptEnglish endp
end