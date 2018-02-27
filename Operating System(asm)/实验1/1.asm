START:
    mov ax,7c0h          ;决定程序内存地址的起始为7c0h
	mov ds,ax            ;把7c0h存进数据段寄存器ds中，指向起始位置
	mov ax,0b800h        ;把显存的起始位置0b800h存进ax寄存器
	mov es,ax            ;把0b800h存进附加段寄存器es中，指向显存起始位置
	mov word[x],-1       ;要显示的字符的起始纵坐标
	mov word[y],-1       ;要显示的字符的起始横坐标
	mov byte[dir],d_r    ;决定方向弹射方向的变量
	mov byte[cnt],2
	mov byte[color],1fh
BEGIN:
    mov cx,0a0h          ;向栈计数寄存器中存入0a0h
DELAY:
    push cx              ;把cx压栈
	mov cx,0ffffh        ;向栈计数寄存器中存入0ffffh
DELAY2:
    loop DELAY2          ;如果cx非0，回到DELAY2
	pop cx               ;把栈顶元素弹出，存到cx寄存器
	loop DELAY           ;如果cx非0，回到DELAY
	cmp byte[dir],1      ;比较dir与1，如果相同，则跳转到DRMOVE
	jz DRMOVE            ;跳转指令
	cmp byte[dir],2      ;比较dir与2，如果相同，则跳转到DLMOVE
	jz DLMOVE            ;跳转指令
	cmp byte[dir],3      ;比较dir与3，如果相同，则跳转到URMOVE
	jz URMOVE            ;跳转指令
	cmp byte[dir],4      ;比较dir与4，如果相同，则跳转到ULMOVE
	jz ULMOVE            ;跳转指令
	jmp START            ;跳转到START
DRMOVE:
    mov byte[dir],d_r    ;把d_r的值赋给dir
	cmp word[y],79       ;比较y与79，如果相同，则跳转到DLMOVE（判断字符是否到达横向右边界）
	jz DLMOVE            ;跳转指令
	cmp word[x],24       ;比较x与24，如果相同，则跳转到URMOVE（判断字符是否到达纵向下边界）
	jz URMOVE            ;跳转指令
	inc word[y]          ;y加1
	inc word[x]          ;x加1
	jmp SHOW             ;跳转到PRINT
DLMOVE:
	mov byte[dir],d_l    ;把d_l的值赋给dir
	cmp word[y],0        ;比较y与0，如果相同，则跳转到DRMOVE（判断字符是否到达横向左边界）
	jz DRMOVE            ;跳转指令
	cmp word[x],24       ;比较x与24，如果相同，则跳转到ULMOVE（判断字符是否到达纵向下边界）
	jz ULMOVE            ;跳转指令
	dec word[y]          ;y减1
	inc word[x]          ;x加1
	jmp SHOW             ;跳转到PRINT
URMOVE:
    mov byte[dir],u_r    ;把u_r的值赋给dir
	cmp word[y],79       ;比较y与79，如果相同，则跳转到ULMOVE（判断字符是否到达横向右边界）
	jz ULMOVE            ;跳转指令
	cmp word[x],0        ;比较x与0，如果相同，则跳转到DRMOVE（判断字符是否到达纵向上边界）
	jz DRMOVE            ;跳转指令
	inc word[y]          ;y加1
	dec word[x]          ;x减1
	jmp SHOW             ;跳转到PRINT
ULMOVE:
    mov byte[dir],u_l    ;把u_l的值赋给dir
	cmp byte[y],0        ;比较y与0，如果相同，则跳转到DRMOVE（判断字符是否到达横向左边界）
	jz URMOVE            ;跳转指令
	cmp byte[x],0        ;比较x与0，如果相同，则跳转到DRMOVE（判断字符是否到达纵向上边界）
	jz DLMOVE            ;跳转指令
	dec word[y]          ;y减1
	dec word[x]          ;x减1
	jmp SHOW             ;跳转到PRINT
SHOW:
    inc byte[cnt]
	cmp byte[cnt],0fh
	jz CHANGE
	jmp PRINT
CHANGE:
    mov byte[cnt],2
	add byte[color],10h
	cmp byte[color],7fh
	jz CHANGE2
	jmp PRINT
CHANGE2:
    mov byte[color],1fh
PRINT:
    mov ax,[x]           ;把x的值传到ax寄存器中
	imul ax,ax,80        ;把ax寄存器里的值与80相乘，存到ax寄存器中（第x行）
	add ax,[y]           ;把y的值与ax寄存器里的值相加，存到ax寄存器中
	imul ax,ax,2         ;把ax寄存器里的值与2相乘，存到ax寄存器中（第y列）
	mov bx,ax            ;把ax的值传到bx中
	mov al,'A'           ;把‘A’字符储存进al寄存器
	mov ah,byte[cnt]
	mov [es:bx],ax
	mov ax,24
	sub ax,word[x]
	imul ax,ax,80
	mov bx,79
	sub bx,[y]
	add ax,bx
	imul ax,ax,2
	mov bx,ax
	mov al,'Z'
	mov ah,byte[cnt]
	mov [es:bx],ax
	jmp SHOW_NAME        ;跳到显示姓名和学号的程序段
	jmp BEGIN            ;跳转到BEGIN
SHOW_NAME:             
    mov word[xx],23      ;把23传到xx中（显示姓名学号的纵坐标）
	mov cx,2             ;把3传到cx寄存器中（共2行）
STEP1:
    push cx              ;把cx压栈
	mov word[yy],54      ;把54传到yy中（显示姓名学号的横坐标）
	mov cx,26            ;把26传到cx寄存器中（共26列）
STEP2:
    call CAL             ;跳到CAL段
	mov byte[es:bx],' '  ;用空格填补多余位置
	mov byte[es:bx+1],7fh;白色底
	inc word[yy]         ;yy加1
	loop STEP2           ;跳到STEP2循环
	pop cx               ;弹出栈顶元素，存到cx中
	inc word[xx]         ;xx加1
	loop STEP1           ;跳到STEP1循环
	mov word[xx],23      ;把23传到xx中（下一行）
	mov word[yy],67      ;把67传到yy中
	mov si,0             ;字符串计数器，初始化为0
	mov cx,13            ;字符串长度为13
STEP3: 
    call CAL             ;跳到CAL段
	mov al,byte[name1+si];把字符串name1第si位存到al寄存器中
	mov byte[es:bx],al   ;输出该字符
	inc word[yy]         ;yy加1
	inc si               ;si加1
	loop STEP3           ;跳到STEP3循环
	mov word[xx],24      ;把24传到xx中（下一行）
    mov word[yy],54      ;把54传到yy中
	mov si,0             ;字符串计数器，初始化为0
	mov cx,26            ;字符串长度为26
STEP4: 
    call CAL             ;跳到CAL段
	mov al,byte[name2+si];把字符串name2第si位存到al寄存器中
	mov byte[es:bx],al   ;输出该字符
	inc word[yy]         ;yy加1
	inc si               ;si加1
	loop STEP4           ;跳到STEP4循环
	jmp BEGIN
CAL: 
    mov ax,word[xx]      ;把xx的值传入ax寄存器
	mov bx,80            ;把80传进bx寄存器
	mul bx               ;ax=ax*bx（计算第xx行的显存位置）
	add ax,word[yy]      ;把yy的值加进ax寄存器
	mov bx,2             ;把2传进bx寄存器
	mul bx               ;ax*bx（计算第xx行，第yy列的显存位置）
	mov bx,ax            ;把ax寄存器的值传进bx寄存器
	ret                  ;返回
end:
    jmp $                  ;结束

DEFINE:                    ;宏定义
    d_r equ 1
	d_l equ 2
	u_r equ 3
	u_l equ 4
	x dw 0
	y dw 0
	xx dw 0
	yy dw 0
	cnt db 0
	color db 1fh
	dir db d_l	
	name1 db 'zjx zhls zhcc'  ;宗嘉希 钟凌山 周禅城
	name2 db '15352461 15352443 15352448' ;15352461 15352443 15352448