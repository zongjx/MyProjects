;wangshuocheng 14350047
START:
	mov ax,0950h
	mov ds,ax
	mov ax,0b800h
	mov es,ax
	cmp byte[run],1
	jz BEGIN
	mov word[x],-1
	mov word[y],39
	mov byte[dir],D_R
	mov byte[cnt],2
	mov byte[color],1fh
	mov byte[count],0
	mov byte[run],1
BEGIN:
	mov ax,0100h
	int 16h
	jnz READKEY
	jmp NOTREAD
READKEY:
	mov ax,0
	int 16h
	cmp al,'2'
	jz RETURN
NOTREAD:	
	inc byte[count]
	cmp byte[count],05fh
	jz RETURN
	jmp SEC
RETURN:
	mov ax,0
	mov es,ax
	mov word[es:602h],0
	mov byte[run],0
	ret
	
SEC:
	;select one direction	
	cmp byte[dir],1
	jz DDRR
	cmp byte[dir],2
	jz DDLL
	cmp byte[dir],3
	jz UURR
	cmp byte[dir],4
	jz UULL
	jmp START
;down and right	
DDRR:
	mov byte[dir],D_R
	cmp word[y],79
	jz DDLL
	cmp word[x],11
	jz UURR
	inc word[x]
	inc word[y]
	jmp SHOW
;down and left
DDLL:
	mov byte[dir],D_L
	cmp word[y],40
	jz DDRR
	cmp word[x],11
	jz UULL
	inc word[x]
	dec word[y]
	jmp SHOW
;up and left
UULL:
	mov byte[dir],U_L
	cmp word[y],40
	jz UURR
	cmp word[x],0
	jz DDLL
	dec word[x]
	dec word[y]
	jmp SHOW
;up and right
UURR:
	mov byte[dir],U_R
	cmp word[y],79
	jz UULL
	cmp word[x],0
	jz DDRR
	dec word[x]
	inc word[y]
	jmp SHOW
;show the char
SHOW:
	;calculate the color of char
	inc byte[cnt]
	cmp byte[cnt],0fh
	jz CHANGE
	jmp NEXT
CHANGE:
	mov byte[cnt],2
	;calculate the color of the rectangle which shows the name and ID
	add byte[color],10h
	cmp byte[color],7fh
	jz CHANGE2
	jmp NEXT
CHANGE2:
	mov byte[color],1fh
NEXT:
	;show the char 'A'
	mov ax,[x]
	mov cx,80
	mul cx
	add ax,[y]
	mov cx,2
	mul cx
	mov bx,ax
	mov al,'A'
	mov ah,byte[cnt]
	mov [es:bx],ax
	;show the char 'B',which opposite to the char 'A'
	mov ax,11
	sub ax,word[x]
	mov cx,80
	mul cx
	mov bx,119
	sub bx,[y]
	add ax,bx
	mov cx,2
	mul cx
	mov bx,ax
	mov al,'B'
	mov ah,byte[cnt]
	mov [es:bx],ax
	
	jmp SHOW_NAME
	jmp BEGIN
;show the name and id
SHOW_NAME: 
	;show the rectangle in the center, full of '*'
	mov word[xx],4
	mov cx,4
LOOP1:	
	push cx
	mov word[yy],50
	mov cx,17
LOOP2:
	call CAL
	mov byte[es:bx],'*'
	mov al,[color]
	mov byte[es:bx+1],al
	inc word[yy]	
	loop LOOP2
	pop cx
	inc word[xx]
	loop LOOP1
	;show the name
	mov word[xx],5
	mov word[yy],52
	mov si,0
	mov cx,13
LOOP3:
	call CAL
	mov al,byte[myname+si]
	mov byte[es:bx],al
	inc word[yy]
	inc si
	loop LOOP3
	;show the ID
	mov word[xx],6
	mov word[yy],54
	mov si,0
	mov cx,8
LOOP4:
	call CAL
	mov al,byte[myid+si]
	mov byte[es:bx],al
	inc word[yy]
	inc si
	loop LOOP4
	
	push es
	mov ax,0
	mov es,ax
	cmp word [es:602h],1
	pop es
	jz FENSHI
	mov cx,0f0h
	call DELAY
	jmp BEGIN
FENSHI:
	mov cx,090h
	call DELAY
	ret
;calculate the position, using (x*80+y)*2
CAL:mov ax,word[xx]
	mov bx,80
	mul bx
	add ax,word[yy]
	mov bx,2
	mul bx
	mov bx,ax
	ret
DELAY:
DELAY1:
	push cx
	mov cx,0ffffh
DELAY2:
	loop DELAY2
	pop cx
	loop DELAY1
	ret	
end:
    jmp $ 

DEFINE:
	D_R equ 1
	D_L equ 2
	U_R equ 3
	U_L equ 4
	xx dw 0
	yy dw 0
	x dw 0
	y dw 0
	dir db D_R
	myname db 'wangshuocheng'
	myid db '14350047'
	cnt db 0
	color db 1fh
	count db 0
	run db 0
	times 1022-($-$$) db 0
    db 0x55,0xaa