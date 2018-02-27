﻿;**************************************************
;* 内核库过程版本信息                             *
;**************************************************

;
extrn _input
extrn _disp_pos
extrn _hour
extrn _minute
extrn _second
extrn _century
extrn _year
extrn _month
extrn _day
extrn _which
extrn _Pro
extrn _dir
extrn _c_paint


extrn _Current_Process
extrn _Save_Process
extrn _Schedule
extrn _Have_Program
extrn _special
extrn _Program_Num
extrn _CurrentPCBno
extrn _Segment

;************ *****************************
; *SCOPY@                               *
;****************** ***********************


; 实参为局部字符串带初始化异常问题的补钉程序

public SCOPY@
SCOPY@ proc 
		arg_0 = dword ptr 6
		arg_4 = dword ptr 0ah
		push bp
		mov bp,sp
		push si
		push di
		push ds
			lds si,[bp+arg_0]
			les di,[bp+arg_4]
			cld
			shr cx,1
			rep movsw
			adc cx,cx
			rep movsb
		pop ds
		pop di
		pop si
		pop bp
		retf 8
SCOPY@ endp

;*************** ********************
;*  void _cls()                       *
;**************** *******************
; 清屏
public _cls
_cls proc 
; 清屏
    mov ax,0003h
	int 10h
	ret
_cls endp

;**** ***********************************
;* void _PrintChar()                       *
;******* ********************************
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

public _put_color_char                ;输出一个指定位置的指定颜色的字符
_put_color_char proc                  ;子程序定义伪指令
	mov bp,sp                         ;把栈的原地址存到bp中
	push es                           ;把以下寄存器压栈
	push ax                           ;
	push bx                           ;
	
	mov ax,0b800h                     ;显存初始位置存进ax
	mov es,ax						  ;把ax存进es
	mov ax,word ptr [bp+4]            ;把传入的第二个变量(x坐标)存到ax中
	mov bx,80                         ;计算横坐标
	mul bx                            ;
	add ax,word ptr [bp+6]            ;把传入的第三个变量(y坐标)存到ax中
	mov bx,2                          ;计算纵坐标
	mul bx                            ;
	mov bx,ax                         ;得到相对位置
	mov ax,word ptr [bp+2]            ;把传入的第一个变量(字符)存到ax中
	mov byte ptr es:[bx],al           ;把字符存进该位置
	mov ax,word ptr [bp+8]            ;把传入的第四个变量(颜色)存到ax中
	mov byte ptr es:[bx+1],al         ;设置颜色
	
	pop bx                            ;把以下寄存器弹出栈
	pop ax                            ;
	pop es                            ;
	ret                               ;
_put_color_char endp                  ;子程序定义结束

;*********** ****************************
;*  void _GetChar()                       *
;****************** *********************
; 读入一个字符
public _getChar
_getChar proc
	push bx
	push es
    push ax
	mov ax,0
	int 16h
	mov byte ptr[_input],al
	pop ax                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es
	pop bx
	ret
_getChar endp

; ****************************************
;      void _port_out(u16 port, u8 value);
; ; ****************************************
; 端口输出
Public	_port_out
_port_out proc
    push bp
            mov bp,sp
        	mov	dx, word ptr [bp + 2]		; port
			mov	al, byte ptr [bp + 2 + 2]	; value
			out	dx, al
			nop	; 一点延迟
			nop
			mov sp,bp
	pop bp
	ret
_port_out endp
; ****************************************
;* u8 _Port_In(u16 port)                     *;
; ****************************************
; 端口输出
public	_Port_In
_Port_In proc
    push bp
    mov bp,sp
    mov	dx, word ptr [bp + 2]		; port
	  xor	ax, ax
	  in	al, dx
		nop	; 一点延迟
		nop
	  mov sp,bp
	  pop bp
	  ret
_Port_In endp
;****************************************
;* Show Time                            *
;****************************************
public _show_Time                                  ;获取时间的函数
_show_Time proc

    push ax                                        ;保护寄存器原来的值
    push bx
    push cx
    push dx	
	
	mov ah,2h                                      ;功能号：2
    int 1ah                                        ;中断号：1a
    mov  byte ptr[_hour],ch                        ;时
    mov  byte ptr[_minute],cl                      ;分
    mov  byte ptr[_second],dh                      ;秒
	
	
	pop dx                                         ;还原寄存器
    pop cx
	pop bx
	pop ax
	ret                                            ;调用返回
 _show_Time endp                                 
;****************************************
;* Show Date                            *
;****************************************
public _show_Date                                 ;获取日期的函数
_show_Date proc
    push ax                                       ;保护寄存器原来的值   
    push bx
    push cx
    push dx
	
	mov ah,4h                                     ;功能号：4
    int 1ah                                       ;中断号：1a
	
	mov byte ptr[_century],ch                     ;
	mov byte ptr[_year],cl                        ;年
	mov byte ptr[_month],dh                       ;月
	mov byte ptr[_day],dl                         ;日
	
	pop dx                                        ;还原寄存器
    pop cx
	pop bx
	pop ax
	ret                                           ;调用返回
 _show_Date endp
 
;****************************************
;* Run program                          *
;****************************************
public _Run
_Run proc
    push ax
    push bx
    push cx
    push dx
	push es
	push ds
      ;装载模块
	mov ax,1000h     		;段地址 ; 存放数据的内存基地址
	mov es,ax         		;设置段地址（不能直接mov es,段地址）
	mov bx,7e00h      		;偏移地址; 存放数据的内存偏移地址
	mov ah,2         		;功能号
	mov al,1         		;扇区数
	mov dl,0         		;驱动器号 ; 软盘为0，硬盘和U盘为80H
	mov dh,1         		;磁头号 ; 起始编号为0
	mov ch,0          		;柱面号 ; 起始编号为0
	mov cl,byte ptr[_Pro] 	;起始扇区号 ; 起始编号为1
	int 13H           		; 调用中断
	
	xor ax,ax
	mov es,ax
	push word ptr es:[9*4]
	pop word ptr ds:[0]
	push word ptr es:[9*4+2]
	pop word ptr ds:[2]
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[24h],offset Orch
	mov ax,cs
	mov word ptr es:[26h],cs
	
	mov bx,7e00h
	call bx
	
	pop ax
	mov ds,ax
	
	xor ax,ax
	mov es,ax
	push word ptr ds:[0]
	pop word ptr es:[9*4]
	push word ptr ds:[2]
	pop word ptr es:[9*4+2]
	int 9h

	
	pop ax
	mov es,ax
	pop dx
    pop cx
	pop bx
	pop ax
	ret	
_Run endp

    row dw 0
	col dw 0
Orch:
    push ax
	push bx
	push dx
	push cx
	push bp
	
	mov ax,0b800h
	mov es,ax
	mov ah,0ah
	mov al,'O'
	mov es:[((80*1+35)*2)],ax
	mov al,'R'
	mov es:[((80*1+36)*2)],ax
	mov al,'C'
	mov es:[((80*1+37)*2)],ax
	mov al,'H'
	mov es:[((80*1+38)*2)],ax
	mov al,'!'
	mov es:[((80*1+39)*2)],ax
	
	
	mov ax,0b800h
	mov es,ax
	mov ah,0ah
	mov al,''
	mov es:[((80*1+35)*2)],ax
	mov al,''
	mov es:[((80*1+36)*2)],ax
	mov al,''
	mov es:[((80*1+37)*2)],ax
	mov al,''
	mov es:[((80*1+38)*2)],ax
	mov al,''
	mov es:[((80*1+39)*2)],ax
	
	pop bp
	pop cx 
	pop dx
	pop bx
	pop ax
	iret

initial:
    mov byte ptr es:[row],0
    pop bp
	pop cx 
	pop dx
	pop bx
	pop ax
	iret

public _int33h	
_int33h proc
	cli
	push es
	push ax
	;es置零
	xor ax,ax
	mov es,ax
	;填充中断向量
	mov word ptr es:[0cch],offset _Int33
	mov ax,cs
	mov word ptr es:[0ceh],ax
	pop ax
	pop es
	sti
	ret
_int33h endp

 ; ***************************************
;* Int 33h                               *
; ****************************************
public _Int33
_Int33 proc
    cli
	push es
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs
	mov es,ax
	
Smile:
    mov ax,0003h
	int 10h
	
    mov ah,13h 	    	; 功能号
	mov al,0 			; 光标放到串尾
	mov bl,0ah 	    	; 亮绿
	mov bh,0 			; 第0页
	mov dh,2	   	 	; 第5行
	mov dl,0	    	; 第32列
	mov cx,166 			; 串长为 Length1
	mov bp, offset str4
	int 10h 			; 调用10H号中
	
	mov al,51*4			; AL = EOI
	out 24h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	pop ds
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti
	iret
str4:
    db '*******************'
	db 0ah,0dh
	db '*                 *'
	db 0ah,0dh
	db '*  ****     ****  *'
	db 0ah,0dh
	db '*                 *'
	db 0ah,0dh
	db '*        *        *'
	db 0ah,0dh
	db '*       * *       *'
	db 0ah,0dh
	db '*      *   *      *'
	db 0ah,0dh
	db '*******************'
	
_Int33 endp

public _int34h
_int34h proc
	cli
	push es
	push ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[0d0h],offset _Int34
	mov ax,cs
	mov word ptr es:[0d2h],ax
	
	pop ax
	pop es
	sti
	ret
_int34h endp
 ; ***************************************
;* Int 34h                               *
; ****************************************
public _Int34
_Int34 proc
    cli
	push es
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs
	mov es,ax

OS:
    mov ax,0003h
	int 10h
	
    mov ah,13h 	    ; 功能号
	mov al,0 		; 光标放到串尾
	mov bl,09h 	    ; 亮绿
	mov bh,0 		; 第0页
	mov dh,5	    ; 第5行
	mov dl,40	    ; 第32列
	mov cx,34 		; 串长为 Length1
	mov bp, offset str5
	int 10h 		; 调用10H号中
	

	
	mov al,52*4		; AL = EOI
	out 52*4+2,al	; 发送EOI到主8529A
	out 0A0h,al		; 发送EOI到从8529A
	pop ds
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti
	iret
str5:
   db '****Hello! OS World! I Like It****' 
	
_Int34 endp

public _int35h
_int35h proc
	cli
	push es
	push ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[0D4h],offset _Int35
	mov ax,cs
	mov word ptr es:[0d6h],ax
	
	pop ax
	pop es
	sti
	ret
_int35h endp
 ; ***************************************
;* Int 35h                               *
; ****************************************
public _Int35
_Int35 proc
    cli
	push es
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs
	mov es,ax

HAHA:
    mov ax,0003h
	int 10h
	
    mov ah,13h 	    ; 功能号
	mov al,0 		; 光标放到串尾
	mov bl,07h 	    ; 亮绿
	mov bh,0 		; 第0页
	mov dh,20	    ; 第5行
	mov dl,0	    ; 第32列
	mov cx,30 		; 串长为 Length1
	mov bp, offset str6
	int 10h 		; 调用10H号中
	

	
	mov al,53*4		; AL = EOI
	out 53*4+2,al	; 发送EOI到主8529A
	out 0A0h,al		; 发送EOI到从8529A
	pop ds
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti
	iret
str6:
   db 'Ha!Ha!   I am the Int 35h  !!!' 	
	
_Int35 endp



public _int36h
_int36h proc
	cli
	push es
	push ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[0d8h],offset _Int36
	mov ax,cs
	mov word ptr es:[0dah],ax
	
	pop ax
	pop es
	sti
	ret
_int36h endp
 ; ***************************************
;* Int 36h                               *
; ****************************************
public _Int36
_Int36 proc
    cli
	push es
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs
	mov es,ax
	
final:
    mov ax,0003h
	int 10h
	
    mov ah,13h 	    ; 功能号
	mov al,0 		; 光标放到串尾
	mov bl,05h 	    ; 亮绿
	mov bh,0 		; 第0页
	mov dh,20	    ; 第5行
	mov dl,40	    ; 第32列
	mov cx,33 		; 串长为 Length1
	mov bp, offset str7
	int 10h 		; 调用10H号中
	

	
	mov al,54*4		; AL = EOI
	out 54*4+2,al	; 发送EOI到主8529A
	out 0A0h,al		; 发送EOI到从8529A
	pop ds
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti
	iret
str7:
   db '###I am the final one !!! Bye!###' 	

_Int36 endp


Delay1:
Loop1:
    inc word ptr es:[count1] 		;递增外层计数变量
	mov word ptr es:[count2],0  	;每递增一次外层计数变量，内层计数变量置为0
Loop2:	
	inc word ptr es:[count2]  		;递增内层计数变量
	cmp word ptr es:[count2],delay  ;比较内层计数变量与延迟数是否相等
	jnz Loop2                		;若不相等，则继续计数
	cmp word ptr es:[count1],delay  ;比较外层计数变量与延迟数是否相等
	jnz Loop1
	mov word ptr es:[count1],0
	ret

	count1 dw 0 					;用于外层循环的计数
    count2 dw 0     				;用于内层循环的计数
    delay equ 5000


public _another_load
_another_load proc
    push ax
	push bp
	
	mov bp,sp
	
    mov ax,[bp+6]      	;段地址 ; 存放数据的内存基地址
	mov es,ax          	;设置段地址（不能直接mov es,段地址）
	mov bx,100h        	;偏移地址; 存放数据的内存偏移地址
	mov ah,2           	;功能号
	mov al,16          	;扇区数
	mov dl,0          	;驱动器号 ; 软盘为0，硬盘和U盘为80H
	mov dh,1          	;磁头号 ; 起始编号为0
	mov ch,0          	;柱面号 ; 起始编号为0
	mov cl,[bp+8]       ;起始扇区号 ; 起始编号为1
	int 13H          	; 调用中断
	
	pop bp
	pop ax
	
	ret
_another_load endp



public _Open_Key_Int
_Open_Key_Int proc
    push ax
	push bx
	push cx
	push dx
	push es
	push ds
	
    xor ax,ax
	mov es,ax
	push word ptr es:[9*4]
	pop word ptr ds:[0]
	push word ptr es:[9*4+2]
	pop word ptr ds:[2]
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[24h],offset Orch
	mov ax,cs
	mov word ptr es:[26h],cs
	
	pop ax
	mov ds,ax
	pop ax
	mov es,ax
	pop dx
	pop cx
	pop bx
	pop ax
	ret
_Open_Key_Int endp

public _Close_Key_Int
_Close_Key_Int proc
	push ax
	push bx
	push cx
	push dx
	push es
	push ds
	
	xor ax,ax
	mov es,ax
	push word ptr ds:[0]
	pop word ptr es:[9*4]
	push word ptr ds:[2]
	pop word ptr es:[9*4+2]
	int 9h
	
	pop ax
	mov ds,ax
	pop ax
	mov es,ax
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
_Close_Key_Int endp
Finite dw 0	
Pro_Timer:
;*****************************************
;*                Save                   *
; ****************************************
    cmp word ptr[_Program_Num],0
	jnz Save
	jmp No_Progress
Save:
	inc word ptr[Finite]
	cmp word ptr[Finite],3200
	jnz Lee 
    mov word ptr[_CurrentPCBno],0
	mov word ptr[Finite],0
	mov word ptr[_Program_Num],0
	mov word ptr[_Segment],2000h
	jmp Pre
Lee:
    push ss
	push ax
	push bx
	push cx
	push dx
	push sp
	push bp
	push si
	push di
	push ds
	push es
	.386
	push fs
	push gs
	.8086

	mov ax,cs
	mov ds, ax
	mov es, ax

	call near ptr _Save_Process
	call near ptr _Schedule 
	
Pre:
	mov ax, cs
	mov ds, ax
	mov es, ax
	
	call near ptr _Current_Process
	mov bp, ax

	mov ss,word ptr ds:[bp+0]         
	mov sp,word ptr ds:[bp+16] 

	cmp word ptr ds:[bp+32],0 
	jnz No_First_Time

;*****************************************
;*                Restart                *
; ****************************************
Restart:
    call near ptr _special
	
	push word ptr ds:[bp+30]
	push word ptr ds:[bp+28]
	push word ptr ds:[bp+26]
	
	push word ptr ds:[bp+2]
	push word ptr ds:[bp+4]
	push word ptr ds:[bp+6]
	push word ptr ds:[bp+8]
	push word ptr ds:[bp+10]
	push word ptr ds:[bp+12]
	push word ptr ds:[bp+14]
	push word ptr ds:[bp+18]
	push word ptr ds:[bp+20]
	push word ptr ds:[bp+22]
	push word ptr ds:[bp+24]

	pop ax
	pop cx
	pop dx
	pop bx
	pop bp
	pop si
	pop di
	pop ds
	pop es
	.386
	pop fs
	pop gs
	.8086

	push ax         
	mov al,20h
	out 20h,al
	out 0A0h,al
	pop ax
	iret

No_First_Time:	
	add sp,16 
	jmp Restart
	
No_Progress:
    call another_Timer
	
	push ax         
	mov al,20h
	out 20h,al
	out 0A0h,al
	pop ax
	iret
	
	

SetTimer: 
    push ax
    mov al,34h   ; 设控制字值 
    out 43h,al   ; 写控制字到控制字寄存器 
    mov ax,59659 ; 每秒 20 次中断（50ms 一次） 
    out 40h,al   ; 写计数器 0 的低字节 
    mov al,ah    ; AL=AH 
    out 40h,al   ; 写计数器 0 的高字节 
	pop ax
	ret

public _setClock
_setClock proc
    push ax
	push bx
	push cx
	push dx
	push ds
	push es
	
    call SetTimer
    xor ax,ax
	mov es,ax
	mov word ptr es:[20h],offset Pro_Timer
	mov ax,cs
	mov word ptr es:[22h],cs
	
	pop ax
	mov es,ax
	pop ax
	mov ds,ax
	pop dx
	pop cx
	pop bx
	pop ax
	ret
_setClock endp




another_Timer:
    push ax
	push bx
	push cx
	push dx
	push bp
    push es
	push ds
	call near ptr _c_paint
	mov ax,cs
	mov ds,ax

	cmp byte ptr [ds:count],0
	jz case1
	cmp byte ptr [ds:count],1
	jz case2
	cmp byte ptr [ds:count],2
	jz case3
	cmp byte ptr [ds:count],3
	jz case4
case1:	
    inc byte ptr [ds:count]
	mov al,'/'
	jmp show
case2:	
    inc byte ptr [ds:count]
	mov al,'-'
	jmp show
case3:	
    inc byte ptr [ds:count]
	mov al,'\'
	jmp show
case4:	
    mov byte ptr [ds:count],0
	mov al,'|'
	jmp show
	
show:
    mov bx,0b800h
	mov es,bx
	mov ah,0ah
	mov es:[((80*2+25)*2)],ax
	mov es:[((80*2+47)*2)],ax
	mov ah,0fh
	mov es:[((80*23+78)*2)],ax
	mov al,'O'
	mov es:[((80*23+68)*2)],ax
	mov al,'S'
	mov es:[((80*23+69)*2)],ax
	mov al,'R'
	mov es:[((80*23+71)*2)],ax
	mov al,'u'
	mov es:[((80*23+72)*2)],ax
	mov al,'n'
	mov es:[((80*23+73)*2)],ax
	mov es:[((80*23+74)*2)],ax
	mov es:[((80*23+76)*2)],ax
	mov al,'i'
	mov es:[((80*23+75)*2)],ax
	mov al,'g'
	mov es:[((80*23+77)*2)],ax
    
	pop ax
	mov ds,ax
	pop ax
	mov es,ax
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	ret

	count db 0