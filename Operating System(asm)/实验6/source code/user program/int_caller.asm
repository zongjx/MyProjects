org 100h                 ;程序偏移量为0b100h
Start:                     ;
	mov ax,cs              ;把cs寄存器的值(代码段地址)存到ax寄存器中
	mov ds,ax              ;把ax寄存器的值存到ds寄存器中
	mov es,ax              ;把ax寄存器的值存到es寄存器中
	mov cx,0affh
	push cx
begin:
	int 36h
	mov cx,00fffh          ;以下为延时
	delay7: 
    push cx
	mov cx,0ffffh
    delay8:
	loop delay8
	pop cx
	loop delay7
	pop cx
	loop begin
	
times 1022-($-$$) db 0
db 0x55,0xaa
	