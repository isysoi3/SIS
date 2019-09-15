includelib includes/user32.lib
includelib includes/kernel32.lib

extrn GetConsoleWindow: PROC
extrn ShowWindow: PROC	
extrn ShowScrollBar: PROC
extrn GetStdHandle : PROC
extrn WriteConsoleW : PROC  
extrn GetModuleFileNameW : PROC

.data
bytesWritten DWORD ?
fileName dw ?

.code
main proc 
	sub    rsp, 5 * 10  
	call   GetConsoleWindow
	mov    rcx, rax 
	mov    rdx, 3
	call   ShowWindow
	mov    rcx, rax 
	mov    rdx, 3
	mov    r8, 0
	call   ShowScrollBar
	mov    rcx, 0
    lea    rdx, fileName
    mov    r8, 256
	call   GetModuleFileNameW
	mov    r8, rax
	mov    rcx, -11
	call   GetStdHandle
	mov    rcx, rax 
	mov    rdx, offset fileName
	lea    r9, bytesWritten
	call   WriteConsoleW
	mov    rcx, 10
	
	start:
		cmp   rcx, -1
		jle   exit 
		mov   rcx, 0    
		jmp   start 
	exit:
		ret
main endp
end
