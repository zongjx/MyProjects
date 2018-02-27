org 7c00h                                ;BIOS将把引导扇区加载到0:7C00h处，并开始执行
PRO equ 0a100h                           ;存放数据的内存偏移地址

START:
	mov ax,cs                            ;置ax寄存器的值与cs相同
	mov ds,ax                            ;将ax(cs)的值存到ds寄存器中(地址偏移) 
	mov es,ax                            ;将ax(cs)的值存到es寄存器中(附加段寄存器) 
	mov dx,ax                            ;将ax(cs)的值存到dx寄存器中
	call CLEAR                           ;调用CLEAR段代码(清屏功能) 
	mov bp,string1                       ;把string1字符串存进bp寄存器
	mov cx,string1_length                ;把string1字符串的长度存进cx寄存器
	mov ax,1301h                         ;把1301h存进ax寄存器(ah=13h:功能号  al=01h:光标放置方式)
	mov bx,000fh                         ;把000fh存进bx寄存器(bh=00h:显示页为0  bl=0fh:黑底白亮字)
	mov dx,090dh                         ;把0b10h存进dx寄存器(dh=0bh:行位置  dl=10h:列位置) 
	int 10h                              ;中断，中断号为10h，功能号为13h，即显示字符串
	mov bp,string2                       ;把string2字符串存进bp寄存器
	mov cx,string2_length                ;把string2字符串的长度存进cx寄存器
	mov dx,0a01h                         ;把0a10h存进dx寄存器(dh=0ch:行位置  dl=10h:列位置)
	int 10h
	mov bp,string3                       ;把string3字符串存进bp寄存器
	mov cx,string3_length                ;把string3字符串的长度存进cx寄存器
	mov dx,0b00h                         ;把0b10h存进dx寄存器(dh=0dh:行位置  dl=10h:列位置)
	int 10h
	mov bp,string4                       ;把string4字符串存进bp寄存器
	mov cx,string4_length                ;把string4字符串的长度存进cx寄存器
	mov dx,0c1ah                         ;把0c10h存进dx寄存器(dh=0eh:行位置  dl=10h:列位置)
	int 10h
	mov bp,string5                       ;把string5字符串存进bp寄存器
	mov cx,string5_length                ;把string5字符串的长度存进cx寄存器
	mov dx,0d1ah                         ;把0d10h存进dx寄存器(dh=0fh:行位置  dl=10h:列位置)
	int 10h                              ;中断，中断号为10h，功能号为13h，即显示字符串
	mov bp,string6                       ;把string6字符串存进bp寄存器
	mov cx,string6_length                ;把string6字符串的长度存进cx寄存器
	mov dx,0e1ah                         ;把0e10h存进dx寄存器(dh=0fh:行位置  dl=10h:列位置)
	int 10h                              ;中断，中断号为10h，功能号为13h，即显示字符串
BEGIN:
    mov ax,0100h                         ;把0100h存进ax寄存器中(ah=01h:功能号  al=00h:ASCII码为0，键盘无输入则为0)
	int 16h                              ;中断，中断号为16h，功能号为01h，即检查键盘缓存区是否有数据
	                                     ;如果有数据，把数据存进al寄存器中，且zf等于1，否则为0
	jnz RUN                              ;检查zf是否为0，如果非0，则跳转到RUN段代码，否则不进行操作
	jmp BEGIN                            ;跳转到BEGIN段代码
RUN:
    mov ax,0                             ;把00h存进ax寄存器中(ah=00h:功能号  al=00h:ASCII码为0，键盘无输入则为0)
	int 16h                              ;中断，中断号为16h，功能号为00h，即读入键盘的输入，存进al寄存器中
	cmp al,'1'                           ;比较al寄存器中的值是否与'1'相等，如果相等就把zf置为1，否则置为0
	jz PRO1                              ;如果zf为1，则跳转至PRO1段代码
	cmp al,'2'                           ;比较al寄存器中的值是否与'2'相等，如果相等就把zf置为1，否则置为0
	jz PRO2                              ;如果zf为1，则跳转至PRO2段代码
	cmp al,'3'                           ;比较al寄存器中的值是否与'3'相等，如果相等就把zf置为1，否则置为0
	jz PRO3                              ;如果zf为1，则跳转至PRO3段代码
	cmp al,'4'                           ;比较al寄存器中的值是否与'4'相等，如果相等就把zf置为1，否则置为0
	jz PRO4                              ;如果zf为1，则跳转至PRO4段代码
	jmp START                            ;跳转至START段代码
PRO1:
    mov byte[choice],1                   ;把choice的值置为1
	jmp LOAD                             ;跳转至LOAD段代码
PRO2:
    mov byte[choice],2                   ;把choice的值置为2
	jmp LOAD                             ;跳转至LOAD段代码
PRO3:
    mov byte[choice],3                   ;把choice的值置为3
	jmp LOAD                             ;跳转至LOAD段代码
PRO4:
    mov byte[choice],4                   ;把choice的值置为4
	jmp LOAD                             ;跳转至LOAD段代码
LOAD:
    call CLEAR                           ;调用CLEAR段代码(清屏功能) 
	mov ax,cs                            ;置ax寄存器的值与cs相同
	mov es,ax                            ;将ax(cs)的值存到es寄存器中(附加段寄存器)
	mov bx,PRO                           ;把PRO的值存到bx寄存器中(存放数据的内存偏移地址,[es:bx]指向数据域的起始地址)
	mov ax,0201h                         ;把0201h存进ax寄存器(ah=02h:功能号，也存储出错是的错误代码  al=01h:扇区数(1~255))
	mov dx,0                             ;把00h存进dx寄存器(dh=00h:磁头号  dl=00h:驱动器号)
	mov cx,01h                           ;把02h存进cx寄存器(ch=00h:柱面号的低8位  cl=01h:0~5位为起始扇区号)  读扇区
	add cl,byte[choice]                  ;cl寄存器的值加上choice的值，储存在cl寄存器中
	                                     ;此处，引导程序在第一个扇区，其余n个子程序各在第1~n个扇区
										 ;因此，cl+n即为第n个子程序的扇区好号，通过此方法读取扇区内容
	int 13h;                             ;中断，中断号为13h，功能号为02h，即读扇区
	jmp PRO                              ;跳转至PRO段代码(PRO段地址的代码) 
CLEAR:
	push es                              ;把es寄存器的值压栈(要利用es寄存器，先保留原来的值)
	mov ax,0b800h                        ;把b800h存进ax寄存器中(显存起始位置) 
	mov es,ax                            ;把ax寄存器的值存进es寄存器中
	mov word[x],0                        ;把x的值置为0
	mov cx,25                            ;把25存进cx寄存器(显示屏的纵向长度)
LOOP1:	
	push cx                              ;把cx寄存器的值压栈(要利用es寄存器，先保留原来的值)
	mov word[y],0                        ;把y的值置为0
	mov cx,80                            ;把80存进cx寄存器(显示屏的横向长度)
LOOP2:
	mov ax,word[x]                       ;把x的值存进ax寄存器中
	mov bx,80                            ;把80存进bx寄存器中
	mul bx                               ;计算纵坐标(80*x)，存进ax寄存器中
	add ax,word[y]                       ;把y的值加进ax寄存器中
	mov bx,2                             ;把2存进bx寄存器中
	mul bx                               ;计算真实坐标((80*x)+y)*2,存进ax寄存器中
	mov bx,ax                            ;把ax寄存器里的值存进bx寄存器中
	mov word[es:bx],00h                  ;把该地址坐标的值置为00h(黑底黑字)
	inc word[y]	                         ;y的值加1
	loop LOOP2                           ;跳到LOOP2循环
	pop cx                               ;把栈顶元素弹出，存到cx寄存器中
	inc word[x]                          ;x的值加1
	loop LOOP1                           ;跳到LOOP1循环
	pop es                               ;把栈顶的元素弹出，存到es寄存器中
	RET                                  ;返回CALL的下一条语句
DEFINE:                                  ;宏定义
    string1 db 'Please input 1 or 2 or 3 or 4 or 5 to run the program '
	string1_length equ ($-string1)
	string2 db '1 shows LU program  2 shows RU program  3 shows LD program  4 shows RD program'
	string2_length equ ($-string2)
	string3 db ' '
	string3_length equ ($-string3)
	string4 db '   zongjiaxi  15352461'
	string4_length equ ($-string4)
	string5 db ' zhonglingshan  15352443'
	string5_length equ ($-string5)
	string6 db ' zhouchancheng  15352461'
	string6_length equ ($-string6)
	choice db 1
	x dw 0
	y dw 0
	times 510-($-$$) db 0                ;在软盘中填充510个0
	db 0x55,0xaa                         ;填上55AA(加起来一共512字节，刚好一个扇区)
	incbin 'prog1.bin'                   ;导入五个程序
	incbin 'prog2.bin'
	incbin 'prog3.bin'
	incbin 'prog4.bin'