.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib libucrt.lib
includelib "..\Debug\Library.lib
EXTRN comp: PROC
EXTRN concat: PROC
EXTRN copy: PROC
EXTRN ConsNum: PROC
EXTRN ConsStr: PROC
EXTRN ConsBool: PROC
EXTRN consPause: proc
ExitProcess PROTO : DWORD

.STACK 4096
.CONST

	L1 db "Hui" , 0
	L2 dd 0

.DATA

	buffer BYTE 256 dup(0)

.CODE


Program PROC
START:

mov EAX, offset L1
push EAX
call ConsStr

mov eax, L2
push 0
call consPause
call ExitProcess
Program ENDP
end Program