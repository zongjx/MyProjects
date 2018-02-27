extrn _main:near                      ;使用extrn调用c模块中的main函数
extrn _cal_pos:near                   ;使用extrn调用c模块中的cal_pos函数
extrn _pos:near                       ;使用extrn调用c模块中的pos变量
extrn _ch:near                        ;使用extrn调用c模块中的ch变量
extrn _x:near                         ;使用extrn调用c模块中的x变量
extrn _y:near                         ;使用extrn调用c模块中的y变量
extrn _offset_prog:near               ;使用extrn调用c模块中的offset_prog变量
extrn _data:near                      ;使用extrn调用c模块中的data变量

_TEXT segment byte public 'CODE'      ;段定义伪操作
assume cs:_TEXT                       ;明确段寄存器与段的关系(cs寄存器存放_TEXT段)
org 100h                              ;起始偏移地址为100h

start:                                ;
    mov ax,cs                         ;把cs寄存器的值(代码段地址)存到ax寄存器中
	add ax,800h                       ;此处为cs+800h，先将800h左移了四位再加上偏移地址得到物理地址
	mov ds,ax                         ;把ax寄存器的值存到ds寄存器中
	mov es,ax                         ;把ax寄存器的值存到es寄存器中
	mov ss,ax                         ;把ax寄存器的值存到ss寄存器中(栈的段地址)
	mov sp,100h                       ;设置sp寄存器的值为100h(栈的长度)
	call near ptr _main               ;调用c模块中的主函数
	jmp $                             ;无限循环

public _setcursor                     ;定义设置光标的函数
_setcursor proc                       ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，dx按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这三个寄存器
	push dx                           ;因此先将这几个寄存器里的原始数据压栈保护
	mov ah,02h                        ;功能号设置为02h，光标定位
	mov dh,byte ptr [_x]              ;设置dh为x变量的值，表示起始的行数
	mov dl,byte ptr [_y]              ;设置dl为y变量的值，表示起始的列数
	mov bh,0                          ;bh设置为0，表示第0页
	int 10h                           ;设置中断号为10h，进行中断
	pop dx                            ;中断调用完成后恢复各个寄存器中的原始值
	pop bx                            ;因此按顺序弹出dx，bx，ax的原始值
	pop ax                            ;分别放回原处
	ret                               ;返回
_setcursor endp                       ;子函数的定义结束

public _printchar                     ;定义打印一个字符的函数
_printchar proc                       ;子程序定义伪指令
    push ax                           ;此处分别将ax，es，bp，bx按顺序压栈，用于保护数据
	push es                           ;由于函数中的中断操作将会用到这四个寄存器
	push bp                           ;因此先将这几个寄存器里的原始数据压栈保护
	push bx                           ;
	call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	mov bp,sp                         ;把栈顶位置寄存器赋值给bp寄存器
	mov ax,0b800h                     ;把显存起始位置存到ax寄存器中
	mov es,ax                         ;把ax寄存器的值寄存到段地址
	mov al,byte ptr [bp+10]           ;把传入函数的数据存到al寄存器中,表示要输出的字符
	mov ah,0fh                        ;把0fh存进ah寄存器中，表示要输出的字符的样式为白字黑底
	mov bx,word ptr [_pos]            ;把pos变量存进bx寄存器中，代表输出字符的坐标
	mov word ptr es:[bx],ax           ;在屏幕上打印该字符
    inc word ptr [_y]                 ;y变量加1(横向坐标加1)
    call near ptr _cal_pos            ;调用cal_pos函数，用于计算新的坐标
    pop bx                            ;中断调用完成后恢复各个寄存器中的原始值
    pop bp                            ;因此按顺序弹出bx，bp，es，ax的原始值
    pop es                            ;分别放回原处
    pop ax                            ;
    ret                               ;返回
_printchar endp                       ;子函数的定义结束

public _printstring                   ;定义打印一个字符串的函数
_printstring proc                     ;子程序定义伪指令
    push bp                           ;此处分别将bp，es，ax按顺序压栈，用于保护数据
	push es                           ;由于函数中的中断操作将会用到这三个寄存器
	push ax                           ;因此先将这几个寄存器里的原始数据压栈保护
	mov bp,sp                         ;把栈顶位置寄存器赋值给bp寄存器
	mov ax,0b800h                     ;把显存起始位置存到ax寄存器中
	mov es,ax                         ;把ax寄存器的值存到段地址
	mov si,word ptr [bp+8]            ;把传入函数的数据存到si寄存器中,表示要输出的字符c串
	mov di,word ptr [_pos]            ;把pos变量存进di寄存器中，代表输出字符串的起始坐标
cond1:                                ;第一种情况：该字符非空字符或换行符
    mov al,byte ptr [si]              ;将si代表的字符串上的一位字符存到al寄存器中
	inc si                            ;si自加1，表示读入下一个字符
	test al,al                        ;将两个操作数作逻辑与运算，检验al中存放的是否为空字符，并将结果存到zf中
    jz cond3                          ;如果zf寄存器的内容是1，则跳转到cond3
	cmp al,0ah                        ;比较al寄存器中存的内容是否为换行符，并将结果存到zf中
	jz cond2                          ;如果zf寄存器的内容是1，则跳转到cond2
	mov ah,0fh                        ;把0fh存进ah寄存器中，表示要输出的字符的样式为白字黑底
	mov word ptr es:[di],ax           ;在屏幕上打印该字符
	inc byte ptr [_y]                 ;y变量加1(横向坐标加1)
	call near ptr _cal_pos            ;调用cal_pos函数，用于计算新的坐标
	mov di,word ptr [_pos]            ;把新的坐标(pos)存进di寄存器中
	jmp cond1                         ;跳转到cond1
cond2:                                ;第二种情况：读取到的是换行符
    inc word ptr [_x]				  ;x变量加1(纵向坐标加1)
	mov word ptr [_y],0               ;y变量变为0(由于换行，横向坐标为0)
	call near ptr _cal_pos            ;调用cal_pos函数，用于计算新的坐标
	mov di,word ptr [_pos]            ;把新的坐标(pos)存进di寄存器中
	jmp cond1                         ;跳转到cond1
cond3:                                ;第三种情况：读取到的是空字符(结束输出)
    call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	pop ax                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ax，es，bp的原始值
	pop bp                            ;分别放回原处
	ret                               ;返回
_printstring endp                     ;子函数的定义结束
 
public _inputchar                     ;定义输入字符的函数
_inputchar proc                       ;子程序定义伪指令
    push ax                           ;把ax压栈(保护ax里的数据)
	call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	mov ax,0                          ;把ax寄存器里的值置0(功能号，ah=0h：入口  输入的字符返回到al寄存器)
	int 16h                           ;设置中断号为16h，进行中断
	mov byte ptr [_ch],al             ;把al寄存器的值(输入的字符)存到ch变量里
	pop ax                            ;中断调用完成后恢复各个寄存器中的原始值
	ret                               ;返回
_inputchar endp                       ;子函数的定义结束

public _clear                         ;定义输入字符的函数
_clear proc                           ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，cx，dx按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这四个寄存器
    push cx                           ;因此先将这几个寄存器里的原始数据压栈保护
    push dx                           ;
    mov ax,0600h                      ;把0600h存进ax寄存器(ah=06h：表示窗口上卷功能，al=00h：卷动整个窗口)
    mov bx,0700h                      ;把0700h存进bx寄存器(bh=07h：白字  bl=00h：黑底)
    mov cx,0                          ;把0存进cx寄存器(ch=0h：起始纵坐标为0  cl=0h：起始横坐标为0)
    mov dx,184fh                      ;把184fh存进寄存器(dh=18h：终止纵坐标为24  dl=4fh：终止横坐标为79)
    int 10h                           ;设置中断号为10h，进行中断
    mov word ptr [_x],0               ;把x的值初始化为0
    mov word ptr [_y],0               ;把y的值初始化为0
    mov word ptr [_pos],0             ;把pos的值初始化为0
    call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	pop dx                            ;中断调用完成后恢复各个寄存器中的原始值
	pop cx                            ;因此按顺序弹出dx，cx，bx，ax的原始值
	pop bx                            ;分别放回原处
	pop ax                            ;
	ret                               ;返回
_clear endp                           ;子函数的定义结束
    
public _load_prog                     ;定义加载程序的函数
_load_prog proc                       ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，cx，dx，es，bp按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这六个寄存器
	push cx                           ;因此先将这几个寄存器里的原始数据压栈保护
	push dx                           ;
	push es                           ;
	push bp                           ;
	mov bp,sp                         ;把栈顶位置寄存器赋值给bp寄存器
	mov ax,cs                         ;把cs的值(代码段的段地址)放进ax寄存器中
	mov es,ax                         ;把ax寄存器的值存到段地址(设置段地址)
	mov bx,word ptr [bp+12+2]         ;把传入函数的第三个数据存到bx寄存器中，表示偏移地址
	mov ah,2                          ;功能号为2，表示读磁盘
	mov al,byte ptr [bp+12+4]         ;把传入函数的第二个数据存到al寄存器中，表示扇区数
	mov dl,0                          ;驱动器号
	mov dh,0                          ;磁头后
	mov ch,0                          ;柱面号
	mov cl,byte ptr [bp+12+6]         ;把传入函数的第一个数据存到cl寄存器中，表示起始扇区号
	int 13h                           ;设置中断号为13h，进行中断
	pop bp                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出bp，es，dx，cx，bx，ax的原始值
	pop dx                            ;分别放回原处
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;返回
_load_prog endp                       ;子函数的定义结束

public _run_prog                      ;定义运行程序的函数
_run_prog proc                        ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，cx，dx，es，ds按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这六个寄存器
	push cx                           ;因此先将这几个寄存器里的原始数据压栈保护
	push dx                           ;
	push es                           ;
    push ds                           ;
	call word ptr [_offset_prog]      ;跳至要运行的程序的地址并运行程序
	pop ds                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ds，es，dx，cx，bx，ax的原始值
	pop dx                            ;分别放回原处
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;返回
_run_prog endp                        ;子函数的定义结束

public _filldata                      ;定义填充数据的函数
_filldata proc                        ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，cx，dx，es，ds按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这六个寄存器
	push cx                           ;因此先将这几个寄存器里的原始数据压栈保护
	push dx                           ;
	push es                           ;
    push ds                           ;
	mov bp,sp                         ;把栈顶位置寄存器赋值给bp寄存器
	mov ax,0                          ;把ax置为0
	mov es,ax                         ;设置段地址
	mov bx,word ptr [bp+12+2]         ;把传入函数的第二个数据存到bx寄存器中，表示偏移地址
	mov ax,word ptr [bp+12+4]         ;把传入函数的第一个数据存到ax寄存器中，表示数据
	mov word ptr es:[bx],ax           ;把ax的值存到该地址中
	pop ds                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ds，es，dx，cx，bx，ax的原始值
	pop dx                            ;分别放回原处
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;返回
_filldata endp                        ;子函数的定义结束

public _readdata                      ;定义填充数据的函数
_readdata proc                        ;子程序定义伪指令
    push ax                           ;此处分别将ax，bx，cx，dx，es，ds按顺序压栈，用于保护数据
	push bx                           ;由于函数中的中断操作将会用到这六个寄存器
	push cx                           ;因此先将这几个寄存器里的原始数据压栈保护
	push dx                           ;
	push es                           ;
    push ds                           ;
	mov bp,sp                         ;把栈顶位置寄存器赋值给bp寄存器
	mov ax,0                          ;把ax置为0
	mov es,ax                         ;设置段地址
	mov bx,word ptr [bp+12+2]         ;把传入函数的第一个数据存到bx寄存器中，表示偏移地址
	mov ax,word ptr es:[bx]           ;把该地址中的数据存到ax寄存器中
	mov word ptr es:[_data],ax        ;把ax寄存器的值存到data变量中
	pop ds                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ds，es，dx，cx，bx，ax的原始值
	pop dx                            ;分别放回原处
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;返回                     
_readdata endp                        ;子函数的定义结束

_TEXT ends                            ;代码段结束
 
end start                             ;start结束