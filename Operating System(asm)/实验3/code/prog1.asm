;prog1
START:
    mov ax,0910h         ;决定程序内存地址的起始为0910h
    mov ds,ax            ;把7c0h存进数据段寄存器ds中，指向起始位置
    mov ax,0b800h        ;把显存的起始位置0b800h存进ax寄存器
    mov es,ax            ;把0b800h存进附加段寄存器es中，指向显存起始位置
	cmp byte[run],1      ;判断run变量是否是1，如果是就把zf变量变为1
	jz BEGIN             ;如果zf变量为1，就跳转到BEGIN
    mov word[x],-1       ;要显示的字符的起始纵坐标
    mov word[y],-1       ;要显示的字符的起始横坐标
    mov byte[dir],d_r    ;决定方向弹射方向的变量
    mov byte[cnt],2      ;计数变量
    mov byte[color],1fh  ;决定颜色的变量
	mov byte[count],0
    mov byte[run],1      ;把run变量赋值为1
BEGIN:
	mov ax,0100h         ;把0100h存进ax寄存器中(ah=01h:功能号  al=00h:ASCII码为0，键盘无输入则为0)
	int 16h              ;中断，中断号为16h，功能号为01h，即检查键盘缓存区是否有数据
	                     ;如果有数据，把数据存进al寄存器中，且zf等于1，否则为0
	jnz READKEY          ;检查zf是否为0，如果非0，则跳转到READKEY段代码，否则不进行操作
	jmp NOTREAD          ;跳转到BEGIN段代码
READKEY:
    mov ax,0             ;把00h存进ax寄存器中(ah=00h:功能号  al=00h:ASCII码为0，键盘无输入则为0)
	int 16h              ;中断，中断号为16h，功能号为00h，即读入键盘的输入，存进al寄存器中
	cmp al,'1'           ;比较al寄存器中的值是否与'1'相等，如果相等就把zf置为1，否则置为0
	jz RETURN            ;如果zf为1，则跳转至RETURN段代码
NOTREAD:
    inc byte[count]      ;count变量加1
	cmp byte[count],0afh ;把count与0afh作比较，如果相等，则把zf置为1，否则为0(程序运行时间)
	jz RETURN            ;检查zf是否为0，如果非0，则跳转到READKEY段代码，否则不进行操作
	jmp SEC              ;跳转到SEC段
RETURN:
    mov ax,0             ;把00h存进ax寄存器中
	mov es,ax            ;把ax存进es寄存器中(初始地址为0)
	mov word[es:600h],0  ;把0存到600h的地址中
	mov byte[run],0      ;把0存进run变量
	ret                  ;返回
SEC:
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
	cmp word[y],39       ;比较y与38，如果相同，则跳转到DLMOVE（判断字符是否到达横向右边界）
	jz DLMOVE            ;跳转指令
	cmp word[x],11       ;比较x与11，如果相同，则跳转到URMOVE（判断字符是否到达纵向下边界）
	jz URMOVE            ;跳转指令
	inc word[y]          ;y加1
	inc word[x]          ;x加1
	jmp SHOW             ;跳转到PRINT
DLMOVE:
	mov byte[dir],d_l    ;把d_l的值赋给dir
	cmp word[y],0        ;比较y与0，如果相同，则跳转到DRMOVE（判断字符是否到达横向左边界）
	jz DRMOVE            ;跳转指令
	cmp word[x],11       ;比较x与11，如果相同，则跳转到ULMOVE（判断字符是否到达纵向下边界）
	jz ULMOVE            ;跳转指令
	dec word[y]          ;y减1
	inc word[x]          ;x加1
	jmp SHOW             ;跳转到PRINT
URMOVE:
    mov byte[dir],u_r    ;把u_r的值赋给dir
	cmp word[y],39       ;比较y与38，如果相同，则跳转到ULMOVE（判断字符是否到达横向右边界）
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
    inc byte[cnt]        ;cnt++
	cmp byte[cnt],0fh    ;cnt与0fh比较大小
	jz CHANGE            ;若相同则跳转到CHANGE
	jmp PRINT            ;跳转到PRINT
CHANGE:
    mov byte[cnt],2      ;cnt=2
	add byte[color],10h  ;color+=0x10
	cmp byte[color],7fh  ;比较color和7fh
	jz CHANGE2           ;相同则跳转至CHANGE2
	jmp PRINT            ;跳转到PRINT
CHANGE2:
    mov byte[color],1fh  ;color=0x1f
PRINT:
    mov ax,[x]           ;把x的值传到ax寄存器中
	imul ax,ax,80        ;把ax寄存器里的值与80相乘，存到ax寄存器中（第x行）
	add ax,[y]           ;把y的值与ax寄存器里的值相加，存到ax寄存器中
	imul ax,ax,2         ;把ax寄存器里的值与2相乘，存到ax寄存器中（第y列）
	mov bx,ax            ;把ax的值传到bx中
	mov al,'Z'           ;把‘Z’字符储存进al寄存器
	mov ah,byte[cnt]     ;将内存中cnt的值取到寄存器ah中
	mov [es:bx],ax       ;将ax的值写入显存中对应的位置
	; mov ax,24            ;ax=24
	; sub ax,word[x]       ;ax-=[x]
	; imul ax,ax,80        ;以下为另一个字母的显示过程，原理同上
	; mov bx,79
	; sub bx,[y]           ;与第一个字母反向运行
	; add ax,bx
	; imul ax,ax,2
	; mov bx,ax
	; mov al,'Z'           ;和第一个字母不同，便于观察
	; mov ah,byte[cnt]
	; mov [es:bx],ax       ;将ax的值写入显存中对应的位置
	jmp SHOW_NAME        ;跳到显示姓名和学号的程序段
	jmp BEGIN            ;跳转到BEGIN
SHOW_NAME:             
    mov word[xx],0      ;把0传到xx中（显示姓名学号的纵坐标）
	mov cx,2             ;把2传到cx寄存器中（共2行）
STEP1:
    push cx              ;把cx压栈
	mov word[yy],0      ;把0传到yy中（显示姓名学号的横坐标）
	mov cx,18            ;把18传到cx寄存器中（共18列）
STEP2:
    call CAL             ;跳到CAL段
	mov byte[es:bx],' '  ;用空格填补多余位置
	mov byte[es:bx+1],7fh;白色底
	inc word[yy]         ;yy加1
	loop STEP2           ;跳到STEP2循环
	pop cx               ;弹出栈顶元素，存到cx中
	inc word[xx]         ;xx加1
	loop STEP1           ;跳到STEP1循环
	mov word[xx],0      ;把0传到xx中（下一行）
	mov word[yy],0      ;把0传到yy中
	mov si,0             ;字符串计数器，初始化为0
	mov cx,18            ;字符串长度为18
STEP3: 
    call CAL             ;跳到CAL段
	mov al,byte[name1+si];把字符串name1第si位存到al寄存器中
	mov byte[es:bx],al   ;输出该字符
	inc word[yy]         ;yy加1
	inc si               ;si加1
	loop STEP3           ;跳到STEP3循环
	mov word[xx],1      ;把1传到xx中（下一行）
    mov word[yy],5      ;把5传到yy中
	mov si,0             ;字符串计数器，初始化为0
	mov cx,8            ;字符串长度为8
STEP4: 
    call CAL             ;跳到CAL段
	mov al,byte[name2+si];把字符串name2第si位存到al寄存器中
	mov byte[es:bx],al   ;输出该字符
	inc word[yy]         ;yy加1
	inc si               ;si加1
	loop STEP4           ;跳到STEP4循环
	push es              ;把es压栈
	mov ax,0             ;把0存到ax寄存器中
	mov es,ax            ;把ax存进es寄存器中(初始地址为0)
	cmp word [es:600h],1 ;比较600h地址的值是否为1，如果是，则把zf置1，否则置0
	pop es               ;弹出es
	jz TIME              ;如果zf的值是1，则跳到TIME段
	mov cx,0f0h          ;把0fh存到cx中
	call DELAY           ;调用DELAY段
	jmp BEGIN            ;跳转到BEGIN
TIME:
    mov cx,090h          ;把090h存进cx寄存器中
	call DELAY           ;跳至DELAY段
	ret                  ;返回
CAL: 
    mov ax,word[xx]      ;把xx的值传入ax寄存器
	mov bx,80            ;把80传进bx寄存器
	mul bx               ;ax=ax*bx（计算第xx行的显存位置）
	add ax,word[yy]      ;把yy的值加进ax寄存器
	mov bx,2             ;把2传进bx寄存器
	mul bx               ;ax*bx（计算第xx行，第yy列的显存位置）
	mov bx,ax            ;把ax寄存器的值传进bx寄存器
	ret                  ;返回
DELAY:
DELAY1:                   
	push cx              ;把cx压栈
	mov cx,0ffffh        ;向栈计数寄存器中存入0ffffh
DELAY2:
	loop DELAY2          ;如果cx非0，回到DELAY2
	pop cx               ;把栈顶元素弹出，存到cx寄存器
	loop DELAY1          ;如果cx非0，回到DELAY1
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
	count db 0
	run db 0
	dir db d_r	
	name1 db 'coded by zongjiaxi'  ;宗嘉希
	name2 db '15352461' ;15352461
	times 1022-($-$$) db 0
	db 0x55,0xaa