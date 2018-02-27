;���ģ��
extrn _main:near                      ;ʹ��extrn����cģ���е�main����
extrn _cal_pos:near                   ;ʹ��extrn����cģ���е�cal_pos����
extrn _c_paint:near                   ;ʹ��extrn����cģ���е�c_paint����
extrn _pos:near                       ;ʹ��extrn����cģ���е�pos����
extrn _ch:near                        ;ʹ��extrn����cģ���е�ch����
extrn _x:near                         ;ʹ��extrn����cģ���е�x����
extrn _y:near                         ;ʹ��extrn����cģ���е�y����
extrn _offset_prog:near               ;ʹ��extrn����cģ���е�offset_prog����
extrn _data1:near                     ;ʹ��extrn����cģ���е�data����
extrn _is_ouch:near                   ;ʹ��extrn����cģ���е�is_ouch����
extrn _c_ouch:near                    ;ʹ��extrn����cģ���е�c_ouch����
extrn _c_rotate:near                  ;ʹ��extrn����cģ���е�c_rotate����


_TEXT segment byte public 'CODE'      ;�ζ���α����
DGROUP group _TEXT,_DATA,_BSS         ;�����������
    assume cs:_TEXT                   ;��ȷ�μĴ�����εĹ�ϵ(cs�Ĵ������_TEXT��)
    org 100h                          ;��ʼƫ�Ƶ�ַΪ100h

start:                                ;
    mov ax,cs                         ;��cs�Ĵ�����ֵ(����ε�ַ)�浽ax�Ĵ�����
	mov ds,ax                         ;��ax�Ĵ�����ֵ�浽ds�Ĵ�����
	mov es,ax                         ;��ax�Ĵ�����ֵ�浽es�Ĵ�����
	mov ss,ax                         ;��ax�Ĵ�����ֵ�浽ss�Ĵ�����(ջ�Ķε�ַ)
	mov sp,100h                       ;����sp�Ĵ�����ֵΪ100h(ջ�ĳ���)
	call int33h                       ;����33h�ж�
	call int34h                       ;����34h�ж�
	call int35h                       ;����35h�ж�
	call int36h                       ;����36h�ж�
	call set_clock_interrupt          ;����ʱ���ж�
	call near ptr _main               ;����cģ���е�������
	jmp $                             ;����ѭ��
	
clock_vector dw 0,0                   ;ʱ������
keyboard_vector dw 0,0                ;��������

public _setcursor                     ;�������ù��ĺ���
_setcursor proc                       ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��dx��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ��������Ĵ���
	push dx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	mov ah,02h                        ;���ܺ�����Ϊ02h����궨λ
	mov dh,byte ptr [_x]              ;����dhΪx������ֵ����ʾ��ʼ������
	mov dl,byte ptr [_y]              ;����dlΪy������ֵ����ʾ��ʼ������
	mov bh,0                          ;bh����Ϊ0����ʾ��0ҳ
	int 10h                           ;�����жϺ�Ϊ10h�������ж�
	pop dx                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop bx                            ;��˰�˳�򵯳�dx��bx��ax��ԭʼֵ
	pop ax                            ;�ֱ�Ż�ԭ��
	ret                               ;����
_setcursor endp                       ;�Ӻ����Ķ������

public _printchar                     ;�����ӡһ���ַ��ĺ���
_printchar proc                       ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��es��bp��bx��˳��ѹջ�����ڱ�������
	push es                           ;���ں����е��жϲ��������õ����ĸ��Ĵ���
	push bp                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	push bx                           ;
	call _setcursor                   ;����cģ���е�setcursor���������ù��
	mov bp,sp                         ;��ջ��λ�üĴ�����ֵ��bp�Ĵ���
	mov ax,0b800h                     ;���Դ���ʼλ�ô浽ax�Ĵ�����
	mov es,ax                         ;��ax�Ĵ�����ֵ�Ĵ浽�ε�ַ
	mov al,byte ptr [bp+10]           ;�Ѵ��뺯�������ݴ浽al�Ĵ�����,��ʾҪ������ַ�
	mov ah,0fh                        ;��0fh���ah�Ĵ����У���ʾҪ������ַ�����ʽΪ���ֺڵ�
	mov bx,word ptr [_pos]            ;��pos�������bx�Ĵ����У���������ַ�������
	mov word ptr es:[bx],ax           ;����Ļ�ϴ�ӡ���ַ�
    inc word ptr [_y]                 ;y������1(���������1)
    call near ptr _cal_pos            ;����cal_pos���������ڼ����µ�����
    pop bx                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
    pop bp                            ;��˰�˳�򵯳�bx��bp��es��ax��ԭʼֵ
    pop es                            ;�ֱ�Ż�ԭ��
    pop ax                            ;
    ret                               ;����
_printchar endp                       ;�Ӻ����Ķ������

public _printstring                   ;�����ӡһ���ַ����ĺ���
_printstring proc                     ;�ӳ�����αָ��
    push bp                           ;�˴��ֱ�bp��es��ax��˳��ѹջ�����ڱ�������
	push es                           ;���ں����е��жϲ��������õ��������Ĵ���
	push ax                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	mov bp,sp                         ;��ջ��λ�üĴ�����ֵ��bp�Ĵ���
	mov ax,0b800h                     ;���Դ���ʼλ�ô浽ax�Ĵ�����
	mov es,ax                         ;��ax�Ĵ�����ֵ�浽�ε�ַ
	mov si,word ptr [bp+8]            ;�Ѵ��뺯�������ݴ浽si�Ĵ�����,��ʾҪ������ַ�c��
	mov di,word ptr [_pos]            ;��pos�������di�Ĵ����У���������ַ�������ʼ����
.1:                                   ;��һ����������ַ��ǿ��ַ����з�
    mov al,byte ptr [si]              ;��si������ַ����ϵ�һλ�ַ��浽al�Ĵ�����
	inc si                            ;si�Լ�1����ʾ������һ���ַ�
	test al,al                        ;���������������߼������㣬����al�д�ŵ��Ƿ�Ϊ���ַ�����������浽zf��
    jz .3                             ;���zf�Ĵ�����������1������ת��cond3
	cmp al,0ah                        ;�Ƚ�al�Ĵ����д�������Ƿ�Ϊ���з�����������浽zf��
	jz .2                             ;���zf�Ĵ�����������1������ת��cond2
	mov ah,0fh                        ;��0fh���ah�Ĵ����У���ʾҪ������ַ�����ʽΪ���ֺڵ�
	mov word ptr es:[di],ax           ;����Ļ�ϴ�ӡ���ַ�
	inc byte ptr [_y]                 ;y������1(���������1)
	call near ptr _cal_pos            ;����cal_pos���������ڼ����µ�����
	mov di,word ptr [_pos]            ;���µ�����(pos)���di�Ĵ�����
	jmp .1                            ;��ת��cond1
.2:                                   ;�ڶ����������ȡ�����ǻ��з�
    inc word ptr [_x]				  ;x������1(���������1)
	mov word ptr [_y],0               ;y������Ϊ0(���ڻ��У���������Ϊ0)
	call near ptr _cal_pos            ;����cal_pos���������ڼ����µ�����
	mov di,word ptr [_pos]            ;���µ�����(pos)���di�Ĵ�����
	jmp .1                            ;��ת��cond1
.3:                                   ;�������������ȡ�����ǿ��ַ�(�������)
    call _setcursor                   ;����cģ���е�setcursor���������ù��
	pop ax                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ax��es��bp��ԭʼֵ
	pop bp                            ;�ֱ�Ż�ԭ��
ret                                   ;����
_printstring endp                     ;�Ӻ����Ķ������
 
public _inputchar                     ;���������ַ��ĺ���
_inputchar proc                       ;�ӳ�����αָ��
    push bx
	push es
    push ax                           ;��axѹջ(����ax�������)
	call _setcursor                   ;����cģ���е�setcursor���������ù��
	mov ax,0                          ;��ax�Ĵ������ֵ��0(���ܺţ�ah=0h�����  ������ַ����ص�al�Ĵ���)
	int 16h                           ;�����жϺ�Ϊ16h�������ж�
	mov byte ptr [_ch],al             ;��al�Ĵ�����ֵ(������ַ�)�浽ch������
	pop ax                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es
	pop bx
	ret                               ;����
_inputchar endp                       ;�Ӻ����Ķ������

public _clear                         ;���������ĺ���
_clear proc                           ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��cx��dx��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ����ĸ��Ĵ���
    push cx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
    push dx                           ;
    mov ax,0600h                      ;��0600h���ax�Ĵ���(ah=06h����ʾ�����Ͼ��ܣ�al=00h������������)
    mov bx,0700h                      ;��0700h���bx�Ĵ���(bh=07h������  bl=00h���ڵ�)
    mov cx,0                          ;��0���cx�Ĵ���(ch=0h����ʼ������Ϊ0  cl=0h����ʼ������Ϊ0)
    mov dx,184fh                      ;��184fh����Ĵ���(dh=18h����ֹ������Ϊ24  dl=4fh����ֹ������Ϊ79)
    int 10h                           ;�����жϺ�Ϊ10h�������ж�
    mov word ptr [_x],0               ;��x��ֵ��ʼ��Ϊ0
    mov word ptr [_y],0               ;��y��ֵ��ʼ��Ϊ0
    mov word ptr [_pos],0             ;��pos��ֵ��ʼ��Ϊ0
    call _setcursor                   ;����cģ���е�setcursor���������ù��
	pop dx                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop cx                            ;��˰�˳�򵯳�dx��cx��bx��ax��ԭʼֵ
	pop bx                            ;�ֱ�Ż�ԭ��
	pop ax                            ;
ret                                   ;����
_clear endp                           ;�Ӻ����Ķ������
    
public _load_prog                     ;������س���ĺ���
_load_prog proc                       ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��cx��dx��es��bp��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ��������Ĵ���
	push cx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	push dx                           ;
	push es                           ;
	push bp                           ;
	mov bp,sp                         ;��ջ��λ�üĴ�����ֵ��bp�Ĵ���
	mov ax,cs                         ;��cs��ֵ(����εĶε�ַ)�Ž�ax�Ĵ�����
	mov es,ax                         ;��ax�Ĵ�����ֵ�浽�ε�ַ(���öε�ַ)
	mov bx,word ptr [bp+12+2]         ;�Ѵ��뺯���ĵ��������ݴ浽bx�Ĵ����У���ʾƫ�Ƶ�ַ
	mov ah,2                          ;���ܺ�Ϊ2����ʾ������
	mov al,byte ptr [bp+12+4]         ;�Ѵ��뺯���ĵڶ������ݴ浽al�Ĵ����У���ʾ������
	mov dl,0                          ;��������
	mov dh,0                          ;��ͷ��
	mov ch,0                          ;�����
	mov cl,byte ptr [bp+12+6]         ;�Ѵ��뺯���ĵ�һ�����ݴ浽cl�Ĵ����У���ʾ��ʼ������
	int 13h                           ;�����жϺ�Ϊ13h�������ж�
	pop bp                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�bp��es��dx��cx��bx��ax��ԭʼֵ
	pop dx                            ;�ֱ�Ż�ԭ��
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;����
_load_prog endp                       ;�Ӻ����Ķ������

public _run_prog                      ;�������г���ĺ���
_run_prog proc                        ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��cx��dx��es��ds��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ��������Ĵ���
	push cx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	push dx                           ;
	push es                           ;
    push ds                           ;
	call re_clock_interrupt
	call set_keyboard_interrupt
	call word ptr [_offset_prog]      ;����Ҫ���еĳ���ĵ�ַ�����г���
	call re_keyboard_interrupt
	call set_clock_interrupt
	pop ds                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ds��es��dx��cx��bx��ax��ԭʼֵ
	pop dx                            ;�ֱ�Ż�ԭ��
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;����
_run_prog endp                        ;�Ӻ����Ķ������

public _filldata                      ;����������ݵĺ���
_filldata proc                        ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��cx��dx��es��ds��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ��������Ĵ���
	push cx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	push dx                           ;
	push es                           ;
    push ds                           ;
	mov bp,sp                         ;��ջ��λ�üĴ�����ֵ��bp�Ĵ���
	mov ax,0                          ;��ax��Ϊ0
	mov es,ax                         ;���öε�ַ
	mov bx,word ptr [bp+12+2]         ;�Ѵ��뺯���ĵڶ������ݴ浽bx�Ĵ����У���ʾƫ�Ƶ�ַ
	mov ax,word ptr [bp+12+4]         ;�Ѵ��뺯���ĵ�һ�����ݴ浽ax�Ĵ����У���ʾ����
	mov word ptr es:[bx],ax           ;��ax��ֵ�浽�õ�ַ��
	pop ds                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ds��es��dx��cx��bx��ax��ԭʼֵ
	pop dx                            ;�ֱ�Ż�ԭ��
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;����
_filldata endp                        ;�Ӻ����Ķ������

public _readdata                      ;����������ݵĺ���
_readdata proc                        ;�ӳ�����αָ��
    push ax                           ;�˴��ֱ�ax��bx��cx��dx��es��ds��˳��ѹջ�����ڱ�������
	push bx                           ;���ں����е��жϲ��������õ��������Ĵ���
	push cx                           ;����Ƚ��⼸���Ĵ������ԭʼ����ѹջ����
	push dx                           ;
	push es                           ;
    push ds                           ;
	mov bp,sp                         ;��ջ��λ�üĴ�����ֵ��bp�Ĵ���
	mov ax,0                          ;��ax��Ϊ0
	mov es,ax                         ;���öε�ַ
	mov bx,word ptr [bp+12+2]         ;�Ѵ��뺯���ĵ�һ�����ݴ浽bx�Ĵ����У���ʾƫ�Ƶ�ַ
	mov ax,word ptr es:[bx]           ;�Ѹõ�ַ�е����ݴ浽ax�Ĵ�����
	mov word ptr [_data1],ax          ;��ax�Ĵ�����ֵ�浽data������
	pop ds                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ds��es��dx��cx��bx��ax��ԭʼֵ
	pop dx                            ;�ֱ�Ż�ԭ��
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;����                     
_readdata endp                        ;�Ӻ����Ķ������

set_keyboard_interrupt proc           ;���ü����ж� 09h
	cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	;save the vector
	mov ax,word ptr es:[24h]          ;�Ѽ����ж����es:24h�浽ax�� (09h*4=24h)
	mov word ptr [keyboard_vector],ax ;��ax���keyboard_vector�����У�����ԭ����ֵ
	mov ax,word ptr es:[26h]          ;�Ѽ����ж����es:26h�浽ax�� (09h*4+2=26h)
	mov word ptr [keyboard_vector+2],ax;��ax���keyboard_vector+2�����У�����ԭ����ֵ
	;fill the vector
	mov word ptr es:[24h],offset Ouch ;���ü����ж�������ƫ�Ƶ�ַ�����жϴ���ʱ�Զ�����Ouch����
	mov ax,cs                         ;��cs���ax��
	mov word ptr es:[26h],ax          ;���ü����ж������Ķε�ַ
	;�����жϷ���C����ı���
	mov word ptr [_is_ouch],1         ;�ı�is_ouch��������ʼ����־
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
set_keyboard_interrupt endp           ;�����������

re_keyboard_interrupt proc            ;�ָ������ж�
	cli     						  ;���IF��־��ʹоƬ���ο������ж�
	push es						   	  ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov ax,word ptr [keyboard_vector] ;��ԭ�ȱ���ļ����ж�����ԭ����ֵ���ax��
	mov word ptr es:[24h],ax          ;�ָ������ж�
	mov ax,word ptr [keyboard_vector+2];��ԭ�ȱ���ļ����ж�����ԭ����ֵ���ax��
	mov word ptr es:[26h],ax          ;�ָ������ж�
	;�����жϷ���C����ı���
	mov word ptr [_is_ouch],0         ;���ó�ʼ����־
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
re_keyboard_interrupt endp            ;�����������


set_clock_interrupt proc              ;����ʱ���ж� 08h
	cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	;save the vector
	mov ax,word ptr es:[20h]          ;��ʱ���ж����es:20h�浽ax�� (08h*4=20h)
	mov word ptr [clock_vector],ax    ;��ax���clock_vector�����У�����ԭ����ֵ
	mov ax,word ptr es:[22h]          ;�Ѽ����ж����es:22h�浽ax�� (08h*4+2=22h)
	mov word ptr [clock_vector+2],ax  ;��ax���clock_vector+2�����У�����ԭ����ֵ
	;fill the vector
	mov word ptr es:[20h],offset Paint;����ʱ���ж�������ƫ�Ƶ�ַ�����жϴ���ʱ�Զ�����Paint����
	mov ax,cs                         ;��cs���ax��      
	mov word ptr es:[22h],ax          ;����ʱ���ж������Ķε�ַ
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
set_clock_interrupt endp              ;�����������

re_clock_interrupt proc               ;�ָ�ʱ���ж�
	cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov ax,word ptr [clock_vector]    ;��ԭ�ȱ����ʱ���ж�����ԭ����ֵ���ax��
	mov word ptr es:[20h],ax          ;�ָ�ʱ���ж�
	mov ax,word ptr [clock_vector+2]  ;��ԭ�ȱ����ʱ���ж�����ԭ����ֵ���ax��
	mov word ptr es:[22h],ax          ;�ָ�ʱ���ж�
	pop ax							  ;��ax����ջ
	pop es							  ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
re_clock_interrupt endp               ;�����������

Paint proc                            ;����Paint����
	cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	call near ptr _c_rotate           ;����c_rotate��������ӡ���
	
	call near ptr _c_paint            ;����c_paint����������Ļ��Χ��ӡ�ַ�
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
Paint endp                            ;�����������

Ouch proc                             ;����Ouch����
	cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	call near ptr _c_ouch             ;����c_rotate������������������ʱ��ӡOuch!
	
	in al,60h                         ;��������
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
Ouch endp

public _put_color_char                ;���һ��ָ��λ�õ�ָ����ɫ���ַ�
_put_color_char proc                  ;�ӳ�����αָ��
	mov bp,sp                         ;��ջ��ԭ��ַ�浽bp��
	push es                           ;�����¼Ĵ���ѹջ
	push ax                           ;
	push bx                           ;
	
	mov ax,0b800h                     ;�Դ��ʼλ�ô��ax
	mov es,ax						  ;��ax���es
	mov ax,word ptr [bp+4]            ;�Ѵ���ĵڶ�������(x����)�浽ax��
	mov bx,80                         ;���������
	mul bx                            ;
	add ax,word ptr [bp+6]            ;�Ѵ���ĵ���������(y����)�浽ax��
	mov bx,2                          ;����������
	mul bx                            ;
	mov bx,ax                         ;�õ����λ��
	mov ax,word ptr [bp+2]            ;�Ѵ���ĵ�һ������(�ַ�)�浽ax��
	mov byte ptr es:[bx],al           ;���ַ������λ��
	mov ax,word ptr [bp+8]            ;�Ѵ���ĵ��ĸ�����(��ɫ)�浽ax��
	mov byte ptr es:[bx+1],al         ;������ɫ
	
	pop bx                            ;�����¼Ĵ�������ջ
	pop ax                            ;
	pop es                            ;
	ret                               ;
_put_color_char endp                  ;�ӳ��������

int33h proc                           ;�ӳ�����αָ��(33���ж�)
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov word ptr es:[0cch],offset interrupt33h;�����ж�������ƫ�Ƶ�ַ�����жϴ���ʱ�Զ�����interrupt33h����
	mov ax,cs                         ;��cs���ax
	mov word ptr es:[0ceh],ax         ;�����ж������Ķε�ַ
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
int33h endp                           ;�ӳ��������

;������Ҫ�������Ϣ
message1_33h db 'Interrupt 33h success'
message1_33h_l equ $-message1_33h
message2_33h db 'Coded by zongjiaxi'
message2_33h_l equ $-message2_33h
message3_33h db '15352461'
message3_33h_l equ $-message3_33h 
interrupt33h proc                     ;�ӳ�����αָ��
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
	push si
	push di
	push ax
	push bx
	push cx
	push dx
	push bp
	push ds
	
	mov ax,cs                         ;�ε�ַ����
	mov es,ax                         ;�ŵ�es��
	mov ax,1301h                      ;���ܺš����
	mov bx,0001h                      ;��ɫ
	mov dx,0408h                      ;�У���
	mov cx,message1_33h_l             ;����
	mov bp,offset message1_33h        ;�ַ�����ʼλ��
	int 10h                           ;����10���ж� 
	                                  ;���»�����ͬ
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0001h;bl��ɫ
	mov dx,050dh;�У���
	mov cx,message2_33h_l
	mov bp,offset message2_33h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0001h;bl��ɫ
	mov dx,0608h;�У���
	mov cx,message3_33h_l
	mov bp,offset message3_33h
	int 10h
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
interrupt33h endp

int34h proc
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov word ptr es:[0d0h],offset interrupt34h
	mov ax,cs
	mov word ptr es:[0d2h],ax
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
int34h endp

message1_34h db 'Interrupt 34h success'
message1_34h_l equ $-message1_34h
message2_34h db 'Coded by zhonglingshan'
message2_34h_l equ $-message2_34h
message3_34h db '15352443'
message3_34h_l equ $-message3_34h 
interrupt34h proc
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
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
	mov bx,0002h;bl��ɫ
	mov dx,042eh;�У���
	mov cx,message1_34h_l
	mov bp,offset message1_34h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0002h;bl��ɫ
	mov dx,0534h;�У���
	mov cx,message2_34h_l
	mov bp,offset message2_34h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0002h;bl��ɫ
	mov dx,062eh;�У���
	mov cx,message3_34h_l
	mov bp,offset message3_34h
	int 10h
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
interrupt34h endp

int35h proc
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov word ptr es:[0d4h],offset interrupt35h
	mov ax,cs
	mov word ptr es:[0d6h],ax
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
int35h endp

message1_35h db 'Interrupt 35h success'
message1_35h_l equ $-message1_35h
message2_35h db 'Coded by zhouchancheng'
message2_35h_l equ $-message2_35h
message3_35h db '15352448 I Love Girls'
message3_35h_l equ $-message3_35h 
interrupt35h proc
   cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
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
	mov bx,0003h;bl��ɫ
	mov dx,1008h;�У���
	mov cx,message1_35h_l
	mov bp,offset message1_35h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0003h;bl��ɫ
	mov dx,110dh;�У���
	mov cx,message2_35h_l
	mov bp,offset message2_35h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0003h;bl��ɫ
	mov dx,1208h;�У���
	mov cx,message3_35h_l
	mov bp,offset message3_35h
	int 10h
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
interrupt35h endp

int36h proc
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es                           ;��esѹջ
	push ax                           ;��axѹջ
	xor ax,ax                         ;��ax��0
	mov es,ax                         ;��ax��ֵ���es�Ĵ�����
	mov word ptr es:[0d8h],offset interrupt36h
	mov ax,cs
	mov word ptr es:[0dah],ax
	pop ax                            ;��ax����ջ
	pop es                            ;��es����ջ
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	ret                               ;����
int36h endp

message1_36h db 'Interrupt 36h success'
message1_36h_l equ $-message1_36h
message2_36h db 'Final show'
message2_36h_l equ $-message2_36h
message3_36h db 'All success'
message3_36h_l equ $-message3_36h 
interrupt36h proc
    cli                               ;���IF��־��ʹоƬ���ο������ж�
	push es							  ;���ν����мĴ���ѹջ����ΪҪʹ�õ���Щ�Ĵ���������ԭֵ
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
	mov bx,0004h;bl��ɫ
	mov dx,102eh;�У���
	mov cx,message1_36h_l
	mov bp,offset message1_36h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0004h;bl��ɫ
	mov dx,1134h;�У���
	mov cx,message2_36h_l
	mov bp,offset message2_36h
	int 10h
	
	mov ax,cs
	mov es,ax
	mov ax,1301h
	mov bx,0004h;bl��ɫ
	mov dx,122eh;�У���
	mov cx,message3_36h_l
	mov bp,offset message3_36h
	int 10h
	
	mov al,20h                        ;��20h�浽al�Ĵ�����(al=EOI)
	out 20h,al						  ;����EOI����оƬ
	out 0a0h,al                       ;����EOI����оƬ

	pop ds                            ;���ν����мĴ�������ջ���ָ�ԭֵ
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	pop di
	pop si
	pop es
	sti                               ;����IF��־��ʹоƬ�����ο������ж�
	iret                              ;�жϷ���
interrupt36h endp


_TEXT ends                            ;����ν���

_DATA segment word public 'DATA'      ;_DATA�ο�ʼ
_DATA ends                            ;_DATA�ν���
 
_BSS	segment word public 'BSS'     ;_BSS�ο�ʼ
_BSS ends                             ;_BSS����

end start                             ;start����