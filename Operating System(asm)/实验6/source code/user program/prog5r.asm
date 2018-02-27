extrn _prog5:near

extrn _dmain


_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
assume cs:_TEXT

org 100h

start:
call near ptr _dmain
jmp $

public _printChar
_printChar proc 
	push bp
		mov bp,sp
		;***
		mov al,[bp+4]
		mov bl,0
		mov ah,0eh
		int 10h
		;***
		mov sp,bp
	pop bp
	ret
_printChar endp

public _fork
_fork proc
	int 33h
	ret
_fork endp

public _wait
_wait proc
	int 34h
	ret
_wait endp

public _exit
_exit proc
	int 35h
	ret
_exit endp


_TEXT ends
_DATA segment word public 'DATA'
_DATA ends
_BSS segment word public 'BSS'
_BSS ends
end start
