;test for 'A'
START:
    mov ax,7c0h          ;决定程序内存地址的起始为7c0h
	mov ds,ax            ;把7c0h存进数据段寄存器ds中，指向起始位置
	mov ax,0b800h        ;把显存的起始位置0b800h存进ax寄存器
	mov es,ax            ;把0b800h存进附加段寄存器es中，指向显存起始位置
	mov word[x],-1       ;要显示的字符的起始纵坐标
	mov word[y],-1       ;要显示的字符的起始横坐标
	mov byte[dir],d_r    ;决定方向弹射方向的变量
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
	jmp PRINT            ;跳转到PRINT
DLMOVE:
	mov byte[dir],d_l    ;把d_l的值赋给dir
	cmp word[y],0        ;比较y与0，如果相同，则跳转到DRMOVE（判断字符是否到达横向左边界）
	jz DRMOVE            ;跳转指令
	cmp word[x],24       ;比较x与24，如果相同，则跳转到ULMOVE（判断字符是否到达纵向下边界）
	jz ULMOVE            ;跳转指令
	dec word[y]          ;y减1
	inc word[x]          ;x加1
	jmp PRINT            ;跳转到PRINT
URMOVE:
    mov byte[dir],u_r    ;把u_r的值赋给dir
	cmp word[y],79       ;比较y与79，如果相同，则跳转到ULMOVE（判断字符是否到达横向右边界）
	jz ULMOVE            ;跳转指令
	cmp word[x],0        ;比较x与0，如果相同，则跳转到DRMOVE（判断字符是否到达纵向上边界）
	jz DRMOVE            ;跳转指令
	inc word[y]          ;y加1
	dec word[x]          ;x减1
	jmp PRINT            ;跳转到PRINT
ULMOVE:
    mov byte[dir],u_l    ;把u_l的值赋给dir
	cmp byte[y],0        ;比较y与0，如果相同，则跳转到DRMOVE（判断字符是否到达横向左边界）
	jz URMOVE            ;跳转指令
	cmp byte[x],0        ;比较x与0，如果相同，则跳转到DRMOVE（判断字符是否到达纵向上边界）
	jz DLMOVE            ;跳转指令
	dec word[y]          ;y减1
	dec word[x]          ;x减1
	jmp PRINT            ;跳转到PRINT
PRINT:
    mov ax,[x]           ;把x的值传到ax寄存器中
	imul ax,ax,80        ;把ax寄存器里的值与80相乘，存到ax寄存器中（第x行）
	add ax,[y]           ;把y的值与ax寄存器里的值相加，存到ax寄存器中
	imul ax,ax,2         ;把ax寄存器里的值与2相乘，存到ax寄存器中（第y列）
	mov bx,ax            ;把ax的值传到bx中
	mov byte[es:bx],'A'  ;把‘A’字符储存进es+bx的显存位置
	jmp BEGIN            ;跳转到BEGIN
end:
    jmp $                  ;结束
DEFINE:                    ;宏定义
    d_r equ 1
	d_l equ 2
	u_r equ 3
	u_l equ 4
	x dw 0
	y dw 0
	dir db d_l	