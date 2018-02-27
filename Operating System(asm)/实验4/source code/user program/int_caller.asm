org 0b100h                 ;程序偏移量为0b100h
Start:                     ;
	mov ax,cs              ;把cs寄存器的值(代码段地址)存到ax寄存器中
	mov ds,ax              ;把ax寄存器的值存到ds寄存器中
	mov es,ax              ;把ax寄存器的值存到es寄存器中
	int 33h                ;调用33号中断
	int 34h                ;调用34号中断
	int 35h                ;调用35号中断
	int 36h                ;调用36号中断
	mov cx,0aaffh          ;以下为延时
delay: 
    push cx
	mov cx,0ffffh
delay2:
	loop delay2
	pop cx
	loop delay
	ret                    ;远转移的返回
	
times 1022-($-$$) db 0
db 0x55,0xaa
	