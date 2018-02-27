extrn _main:near                      ;ʹ��extrn����cģ���е�main����
extrn _cal_pos:near                   ;ʹ��extrn����cģ���е�cal_pos����
extrn _pos:near                       ;ʹ��extrn����cģ���е�pos����
extrn _ch:near                        ;ʹ��extrn����cģ���е�ch����
extrn _x:near                         ;ʹ��extrn����cģ���е�x����
extrn _y:near                         ;ʹ��extrn����cģ���е�y����
extrn _offset_prog:near               ;ʹ��extrn����cģ���е�offset_prog����
extrn _data:near                      ;ʹ��extrn����cģ���е�data����

_TEXT segment byte public 'CODE'      ;�ζ���α����
assume cs:_TEXT                       ;��ȷ�μĴ�����εĹ�ϵ(cs�Ĵ������_TEXT��)
org 100h                              ;��ʼƫ�Ƶ�ַΪ100h

start:                                ;
    mov ax,cs                         ;��cs�Ĵ�����ֵ(����ε�ַ)�浽ax�Ĵ�����
	add ax,800h                       ;�˴�Ϊcs+800h���Ƚ�800h��������λ�ټ���ƫ�Ƶ�ַ�õ������ַ
	mov ds,ax                         ;��ax�Ĵ�����ֵ�浽ds�Ĵ�����
	mov es,ax                         ;��ax�Ĵ�����ֵ�浽es�Ĵ�����
	mov ss,ax                         ;��ax�Ĵ�����ֵ�浽ss�Ĵ�����(ջ�Ķε�ַ)
	mov sp,100h                       ;����sp�Ĵ�����ֵΪ100h(ջ�ĳ���)
	call near ptr _main               ;����cģ���е�������
	jmp $                             ;����ѭ��

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
cond1:                                ;��һ����������ַ��ǿ��ַ����з�
    mov al,byte ptr [si]              ;��si������ַ����ϵ�һλ�ַ��浽al�Ĵ�����
	inc si                            ;si�Լ�1����ʾ������һ���ַ�
	test al,al                        ;���������������߼������㣬����al�д�ŵ��Ƿ�Ϊ���ַ�����������浽zf��
    jz cond3                          ;���zf�Ĵ�����������1������ת��cond3
	cmp al,0ah                        ;�Ƚ�al�Ĵ����д�������Ƿ�Ϊ���з�����������浽zf��
	jz cond2                          ;���zf�Ĵ�����������1������ת��cond2
	mov ah,0fh                        ;��0fh���ah�Ĵ����У���ʾҪ������ַ�����ʽΪ���ֺڵ�
	mov word ptr es:[di],ax           ;����Ļ�ϴ�ӡ���ַ�
	inc byte ptr [_y]                 ;y������1(���������1)
	call near ptr _cal_pos            ;����cal_pos���������ڼ����µ�����
	mov di,word ptr [_pos]            ;���µ�����(pos)���di�Ĵ�����
	jmp cond1                         ;��ת��cond1
cond2:                                ;�ڶ����������ȡ�����ǻ��з�
    inc word ptr [_x]				  ;x������1(���������1)
	mov word ptr [_y],0               ;y������Ϊ0(���ڻ��У���������Ϊ0)
	call near ptr _cal_pos            ;����cal_pos���������ڼ����µ�����
	mov di,word ptr [_pos]            ;���µ�����(pos)���di�Ĵ�����
	jmp cond1                         ;��ת��cond1
cond3:                                ;�������������ȡ�����ǿ��ַ�(�������)
    call _setcursor                   ;����cģ���е�setcursor���������ù��
	pop ax                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ax��es��bp��ԭʼֵ
	pop bp                            ;�ֱ�Ż�ԭ��
	ret                               ;����
_printstring endp                     ;�Ӻ����Ķ������
 
public _inputchar                     ;���������ַ��ĺ���
_inputchar proc                       ;�ӳ�����αָ��
    push ax                           ;��axѹջ(����ax�������)
	call _setcursor                   ;����cģ���е�setcursor���������ù��
	mov ax,0                          ;��ax�Ĵ������ֵ��0(���ܺţ�ah=0h�����  ������ַ����ص�al�Ĵ���)
	int 16h                           ;�����жϺ�Ϊ16h�������ж�
	mov byte ptr [_ch],al             ;��al�Ĵ�����ֵ(������ַ�)�浽ch������
	pop ax                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	ret                               ;����
_inputchar endp                       ;�Ӻ����Ķ������

public _clear                         ;���������ַ��ĺ���
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
	ret                               ;����
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
	call word ptr [_offset_prog]      ;����Ҫ���еĳ���ĵ�ַ�����г���
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
	mov word ptr es:[_data],ax        ;��ax�Ĵ�����ֵ�浽data������
	pop ds                            ;�жϵ�����ɺ�ָ������Ĵ����е�ԭʼֵ
	pop es                            ;��˰�˳�򵯳�ds��es��dx��cx��bx��ax��ԭʼֵ
	pop dx                            ;�ֱ�Ż�ԭ��
	pop cx                            ;
	pop bx                            ;
	pop ax                            ;
	ret                               ;����                     
_readdata endp                        ;�Ӻ����Ķ������

_TEXT ends                            ;����ν���
 
end start                             ;start����