;汇编模块
extrn _main:near                      ;使用extrn调用c模块中的main函数
extrn _cal_pos:near                   ;使用extrn调用c模块中的cal_pos函数
extrn _c_paint:near                   ;使用extrn调用c模块中的c_paint函数
extrn _pos:near                       ;使用extrn调用c模块中的pos变量
extrn _ch:near                        ;使用extrn调用c模块中的ch变量
extrn _x:near                         ;使用extrn调用c模块中的x变量
extrn _y:near                         ;使用extrn调用c模块中的y变量
extrn _offset_prog:near               ;使用extrn调用c模块中的offset_prog变量
extrn _data1:near                     ;使用extrn调用c模块中的data变量
extrn _is_ouch:near                   ;使用extrn调用c模块中的is_ouch变量
extrn _c_ouch:near                    ;使用extrn调用c模块中的c_ouch函数
extrn _c_rotate:near                  ;使用extrn调用c模块中的c_rotate函数


_TEXT segment byte public 'CODE'      ;段定义伪操作
DGROUP group _TEXT,_DATA,_BSS         ;数据与的设置
    assume cs:_TEXT                   ;明确段寄存器与段的关系(cs寄存器存放_TEXT段)
    org 100h                          ;起始偏移地址为100h

start:                                ;
    mov ax,cs                         ;把cs寄存器的值(代码段地址)存到ax寄存器中
	mov ds,ax                         ;把ax寄存器的值存到ds寄存器中
	mov es,ax                         ;把ax寄存器的值存到es寄存器中
	mov ss,ax                         ;把ax寄存器的值存到ss寄存器中(栈的段地址)
	mov sp,100h                       ;设置sp寄存器的值为100h(栈的长度)
	call int33h                       ;开启33h中断
	call int34h                       ;开启34h中断
	call int35h                       ;开启35h中断
	call int36h                       ;开启36h中断
	call set_clock_interrupt          ;开启时钟中断
	call near ptr _main               ;调用c模块中的主函数
	jmp $                             ;无限循环
	
clock_vector dw 0,0                   ;时钟向量
keyboard_vector dw 0,0                ;键盘向量

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
.1:                                   ;第一种情况：该字符非空字符或换行符
    mov al,byte ptr [si]              ;将si代表的字符串上的一位字符存到al寄存器中
	inc si                            ;si自加1，表示读入下一个字符
	test al,al                        ;将两个操作数作逻辑与运算，检验al中存放的是否为空字符，并将结果存到zf中
    jz .3                             ;如果zf寄存器的内容是1，则跳转到cond3
	cmp al,0ah                        ;比较al寄存器中存的内容是否为换行符，并将结果存到zf中
	jz .2                             ;如果zf寄存器的内容是1，则跳转到cond2
	mov ah,0fh                        ;把0fh存进ah寄存器中，表示要输出的字符的样式为白字黑底
	mov word ptr es:[di],ax           ;在屏幕上打印该字符
	inc byte ptr [_y]                 ;y变量加1(横向坐标加1)
	call near ptr _cal_pos            ;调用cal_pos函数，用于计算新的坐标
	mov di,word ptr [_pos]            ;把新的坐标(pos)存进di寄存器中
	jmp .1                            ;跳转到cond1
.2:                                   ;第二种情况：读取到的是换行符
    inc word ptr [_x]				  ;x变量加1(纵向坐标加1)
	mov word ptr [_y],0               ;y变量变为0(由于换行，横向坐标为0)
	call near ptr _cal_pos            ;调用cal_pos函数，用于计算新的坐标
	mov di,word ptr [_pos]            ;把新的坐标(pos)存进di寄存器中
	jmp .1                            ;跳转到cond1
.3:                                   ;第三种情况：读取到的是空字符(结束输出)
    call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	pop ax                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ax，es，bp的原始值
	pop bp                            ;分别放回原处
ret                                   ;返回
_printstring endp                     ;子函数的定义结束
 
public _inputchar                     ;定义输入字符的函数
_inputchar proc                       ;子程序定义伪指令
    push bx
	push es
    push ax                           ;把ax压栈(保护ax里的数据)
	call _setcursor                   ;调用c模块中的setcursor函数，放置光标
	mov ax,0                          ;把ax寄存器里的值置0(功能号，ah=0h：入口  输入的字符返回到al寄存器)
	int 16h                           ;设置中断号为16h，进行中断
	mov byte ptr [_ch],al             ;把al寄存器的值(输入的字符)存到ch变量里
	pop ax                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es
	pop bx
	ret                               ;返回
_inputchar endp                       ;子函数的定义结束

public _clear                         ;定义清屏的函数
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
ret                                   ;返回
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
	call re_clock_interrupt
	call set_keyboard_interrupt
	call word ptr [_offset_prog]      ;跳至要运行的程序的地址并运行程序
	call re_keyboard_interrupt
	call set_clock_interrupt
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
	mov word ptr [_data1],ax          ;把ax寄存器的值存到data变量中
	pop ds                            ;中断调用完成后恢复各个寄存器中的原始值
	pop es                            ;因此按顺序弹出ds，es，dx，cx，bx，ax的原始值
	pop dx                            ;分别放回原处
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;返回                     
_readdata endp                        ;子函数的定义结束

set_keyboard_interrupt proc           ;设置键盘中断 09h
	cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	;save the vector
	mov ax,word ptr es:[24h]          ;把键盘中断入口es:24h存到ax中 (09h*4=24h)
	mov word ptr [keyboard_vector],ax ;把ax存进keyboard_vector向量中，保存原来的值
	mov ax,word ptr es:[26h]          ;把键盘中断入口es:26h存到ax中 (09h*4+2=26h)
	mov word ptr [keyboard_vector+2],ax;把ax存进keyboard_vector+2向量中，保存原来的值
	;fill the vector
	mov word ptr es:[24h],offset Ouch ;设置键盘中断向量的偏移地址，当中断触发时自动调用Ouch函数
	mov ax,cs                         ;把cs存进ax中
	mov word ptr es:[26h],ax          ;设置键盘中断向量的段地址
	;用于中断服务C程序的变量
	mov word ptr [_is_ouch],1         ;改变is_ouch变量，初始化标志
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
set_keyboard_interrupt endp           ;函数定义结束

re_keyboard_interrupt proc            ;恢复键盘中断
	cli     						  ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es						   	  ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov ax,word ptr [keyboard_vector] ;把原先保存的键盘中断向量原来的值存进ax中
	mov word ptr es:[24h],ax          ;恢复键盘中断
	mov ax,word ptr [keyboard_vector+2];把原先保存的键盘中断向量原来的值存进ax中
	mov word ptr es:[26h],ax          ;恢复键盘中断
	;用于中断服务C程序的变量
	mov word ptr [_is_ouch],0         ;重置初始化标志
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
re_keyboard_interrupt endp            ;函数定义结束


set_clock_interrupt proc              ;设置时钟中断 08h
	cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	;save the vector
	mov ax,word ptr es:[20h]          ;把时钟中断入口es:20h存到ax中 (08h*4=20h)
	mov word ptr [clock_vector],ax    ;把ax存进clock_vector向量中，保存原来的值
	mov ax,word ptr es:[22h]          ;把键盘中断入口es:22h存到ax中 (08h*4+2=22h)
	mov word ptr [clock_vector+2],ax  ;把ax存进clock_vector+2向量中，保存原来的值
	;fill the vector
	mov word ptr es:[20h],offset Paint;设置时钟中断向量的偏移地址，当中断触发时自动调用Paint函数
	mov ax,cs                         ;把cs存进ax中      
	mov word ptr es:[22h],ax          ;设置时钟中断向量的段地址
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
set_clock_interrupt endp              ;函数定义结束

re_clock_interrupt proc               ;恢复时钟中断
	cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov ax,word ptr [clock_vector]    ;把原先保存的时钟中断向量原来的值存进ax中
	mov word ptr es:[20h],ax          ;恢复时钟中断
	mov ax,word ptr [clock_vector+2]  ;把原先保存的时钟中断向量原来的值存进ax中
	mov word ptr es:[22h],ax          ;恢复时钟中断
	pop ax							  ;把ax弹出栈
	pop es							  ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
re_clock_interrupt endp               ;函数定义结束

Paint proc                            ;定义Paint函数
	cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	call near ptr _c_rotate           ;调用c_rotate函数，打印横杠
	
	call near ptr _c_paint            ;调用c_paint函数，在屏幕周围打印字符
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
Paint endp                            ;函数定义结束

Ouch proc                             ;定义Ouch函数
	cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	call near ptr _c_ouch             ;调用c_rotate函数，当键盘有输入时打印Ouch!
	
	in al,60h                         ;读缓冲区
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
Ouch endp

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

int33h proc                           ;子程序定义伪指令(33号中断)
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov word ptr es:[0cch],offset interrupt33h;设置中断向量的偏移地址，当中断触发时自动调用interrupt33h函数
	mov ax,cs                         ;把cs存进ax
	mov word ptr es:[0ceh],ax         ;设置中断向量的段地址
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
int33h endp                           ;子程序定义结束

;以下是要输出的信息
message1_33h db 'Interrupt 33h success'
message1_33h_l equ $-message1_33h
message2_33h db 'Coded by zongjiaxi'
message2_33h_l equ $-message2_33h
message3_33h db '15352461'
message3_33h_l equ $-message3_33h 
interrupt33h proc                     ;子程序定义伪指令
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs                         ;段地址储存
	mov es,ax                         ;放到es中
	mov ax,1301h                      ;功能号、光标
	mov bx,0001h                      ;颜色
	mov dx,0408h                      ;行，列
	mov cx,message1_33h_l             ;长度
	mov bp,offset message1_33h        ;字符串起始位置
	int 10h                           ;调用10号中断 
	                                  ;以下基本相同
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0001h;bl颜色
	mov dx,050dh;行，列
	mov cx,message2_33h_l
	mov bp,offset message2_33h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0001h;bl颜色
	mov dx,0608h;行，列
	mov cx,message3_33h_l
	mov bp,offset message3_33h
	int 10h
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
interrupt33h endp

int34h proc
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov word ptr es:[0d0h],offset interrupt34h
	mov ax,cs
	mov word ptr es:[0d2h],ax
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
int34h endp

message1_34h db 'Interrupt 34h success'
message1_34h_l equ $-message1_34h
message2_34h db 'Coded by zhonglingshan'
message2_34h_l equ $-message2_34h
message3_34h db '15352443'
message3_34h_l equ $-message3_34h 
interrupt34h proc
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
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
	mov ax,1301h
	mov bx,0002h;bl颜色
	mov dx,042eh;行，列
	mov cx,message1_34h_l
	mov bp,offset message1_34h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0002h;bl颜色
	mov dx,0534h;行，列
	mov cx,message2_34h_l
	mov bp,offset message2_34h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0002h;bl颜色
	mov dx,062eh;行，列
	mov cx,message3_34h_l
	mov bp,offset message3_34h
	int 10h
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
interrupt34h endp

int35h proc
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov word ptr es:[0d4h],offset interrupt35h
	mov ax,cs
	mov word ptr es:[0d6h],ax
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
int35h endp

message1_35h db 'Interrupt 35h success'
message1_35h_l equ $-message1_35h
message2_35h db 'Coded by zhouchancheng'
message2_35h_l equ $-message2_35h
message3_35h db '15352448 I Love Girls'
message3_35h_l equ $-message3_35h 
interrupt35h proc
   cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
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
	mov ax,1301h
	mov bx,0003h;bl颜色
	mov dx,1008h;行，列
	mov cx,message1_35h_l
	mov bp,offset message1_35h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0003h;bl颜色
	mov dx,110dh;行，列
	mov cx,message2_35h_l
	mov bp,offset message2_35h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0003h;bl颜色
	mov dx,1208h;行，列
	mov cx,message3_35h_l
	mov bp,offset message3_35h
	int 10h
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
interrupt35h endp

int36h proc
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es                           ;把es压栈
	push ax                           ;把ax压栈
	xor ax,ax                         ;把ax置0
	mov es,ax                         ;把ax的值存进es寄存器中
	mov word ptr es:[0d8h],offset interrupt36h
	mov ax,cs
	mov word ptr es:[0dah],ax
	pop ax                            ;把ax弹出栈
	pop es                            ;把es弹出栈
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	ret                               ;返回
int36h endp

message1_36h db 'Interrupt 36h success'
message1_36h_l equ $-message1_36h
message2_36h db 'Final show'
message2_36h_l equ $-message2_36h
message3_36h db 'All success'
message3_36h_l equ $-message3_36h 
interrupt36h proc
    cli                               ;清除IF标志，使芯片屏蔽可屏蔽中断
	push es							  ;依次将下列寄存器压栈，因为要使用到这些寄存器，保护原值
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
	mov ax,1301h
	mov bx,0004h;bl颜色
	mov dx,102eh;行，列
	mov cx,message1_36h_l
	mov bp,offset message1_36h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0004h;bl颜色
	mov dx,1134h;行，列
	mov cx,message2_36h_l
	mov bp,offset message2_36h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0004h;bl颜色
	mov dx,122eh;行，列
	mov cx,message3_36h_l
	mov bp,offset message3_36h
	int 10h
	
	mov al,20h                        ;把20h存到al寄存器中(al=EOI)
	out 20h,al						  ;发送EOI到主芯片
	out 0a0h,al                       ;发送EOI到从芯片

	pop ds                            ;依次将下列寄存器弹出栈，恢复原值
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;设置IF标志，使芯片不屏蔽可屏蔽中断
	iret                              ;中断返回
interrupt36h endp


_TEXT ends                            ;代码段结束

_DATA segment word public 'DATA'      ;_DATA段开始
_DATA ends                            ;_DATA段结束
 
_BSS	segment word public 'BSS'     ;_BSS段开始
_BSS ends                             ;_BSS结束

end start                             ;start结束