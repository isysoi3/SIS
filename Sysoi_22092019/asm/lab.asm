
extern printf: proc 

.data
text      db '*.*',0
format    db '%s',0

.code
main proc 
    sub rsp,5*8;резервируем стек
    lea rcx, text
    call printf
main endp
end