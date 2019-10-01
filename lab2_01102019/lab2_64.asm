includelib includes/user32.lib
includelib includes/kernel32.lib

extrn MessageBoxA: PROC

.data 
caption db '64-bit lab2', 0 
output db 'Ã¿Ã¿ Ã€À¿ –¿Ã”', 0 

.code 
Start proc   
       sub    rsp, 28h 
       mov    rcx, 0
       lea    rdx, output
       lea    r8,  caption
       mov    r9d, 0   
       call   MessageBoxA
       mov	  output+10, 'œ'
	   mov	  output+12, 'œ'
       mov    rcx, 0      
       lea    rdx, output 
       lea    r8,  caption
       mov    r9d, 0
       call   MessageBoxA
Start endp
end



