;prog1
START:
    mov ax,0910h         ;���������ڴ��ַ����ʼΪ0910h
    mov ds,ax            ;��7c0h������ݶμĴ���ds�У�ָ����ʼλ��
    mov ax,0b800h        ;���Դ����ʼλ��0b800h���ax�Ĵ���
    mov es,ax            ;��0b800h������ӶμĴ���es�У�ָ���Դ���ʼλ��
	cmp byte[run],1      ;�ж�run�����Ƿ���1������ǾͰ�zf������Ϊ1
	jz BEGIN             ;���zf����Ϊ1������ת��BEGIN
    mov word[x],-1       ;Ҫ��ʾ���ַ�����ʼ������
    mov word[y],-1       ;Ҫ��ʾ���ַ�����ʼ������
    mov byte[dir],d_r    ;���������䷽��ı���
    mov byte[cnt],2      ;��������
    mov byte[color],1fh  ;������ɫ�ı���
	mov byte[count],0
    mov byte[run],1      ;��run������ֵΪ1
BEGIN:
	mov ax,0100h         ;��0100h���ax�Ĵ�����(ah=01h:���ܺ�  al=00h:ASCII��Ϊ0��������������Ϊ0)
	int 16h              ;�жϣ��жϺ�Ϊ16h�����ܺ�Ϊ01h���������̻������Ƿ�������
	                     ;��������ݣ������ݴ��al�Ĵ����У���zf����1������Ϊ0
	jnz READKEY          ;���zf�Ƿ�Ϊ0�������0������ת��READKEY�δ��룬���򲻽��в���
	jmp NOTREAD          ;��ת��BEGIN�δ���
READKEY:
    mov ax,0             ;��00h���ax�Ĵ�����(ah=00h:���ܺ�  al=00h:ASCII��Ϊ0��������������Ϊ0)
	int 16h              ;�жϣ��жϺ�Ϊ16h�����ܺ�Ϊ00h����������̵����룬���al�Ĵ�����
	cmp al,'1'           ;�Ƚ�al�Ĵ����е�ֵ�Ƿ���'1'��ȣ������ȾͰ�zf��Ϊ1��������Ϊ0
	jz RETURN            ;���zfΪ1������ת��RETURN�δ���
NOTREAD:
    inc byte[count]      ;count������1
	cmp byte[count],0afh ;��count��0afh���Ƚϣ������ȣ����zf��Ϊ1������Ϊ0(��������ʱ��)
	jz RETURN            ;���zf�Ƿ�Ϊ0�������0������ת��READKEY�δ��룬���򲻽��в���
	jmp SEC              ;��ת��SEC��
RETURN:
    mov ax,0             ;��00h���ax�Ĵ�����
	mov es,ax            ;��ax���es�Ĵ�����(��ʼ��ַΪ0)
	mov word[es:600h],0  ;��0�浽600h�ĵ�ַ��
	mov byte[run],0      ;��0���run����
	ret                  ;����
SEC:
	cmp byte[dir],1      ;�Ƚ�dir��1�������ͬ������ת��DRMOVE
	jz DRMOVE            ;��תָ��
	cmp byte[dir],2      ;�Ƚ�dir��2�������ͬ������ת��DLMOVE
	jz DLMOVE            ;��תָ��
	cmp byte[dir],3      ;�Ƚ�dir��3�������ͬ������ת��URMOVE
	jz URMOVE            ;��תָ��
	cmp byte[dir],4      ;�Ƚ�dir��4�������ͬ������ת��ULMOVE
	jz ULMOVE            ;��תָ��
	jmp START            ;��ת��START
DRMOVE:
    mov byte[dir],d_r    ;��d_r��ֵ����dir
	cmp word[y],39       ;�Ƚ�y��38�������ͬ������ת��DLMOVE���ж��ַ��Ƿ񵽴�����ұ߽磩
	jz DLMOVE            ;��תָ��
	cmp word[x],11       ;�Ƚ�x��11�������ͬ������ת��URMOVE���ж��ַ��Ƿ񵽴������±߽磩
	jz URMOVE            ;��תָ��
	inc word[y]          ;y��1
	inc word[x]          ;x��1
	jmp SHOW             ;��ת��PRINT
DLMOVE:
	mov byte[dir],d_l    ;��d_l��ֵ����dir
	cmp word[y],0        ;�Ƚ�y��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������߽磩
	jz DRMOVE            ;��תָ��
	cmp word[x],11       ;�Ƚ�x��11�������ͬ������ת��ULMOVE���ж��ַ��Ƿ񵽴������±߽磩
	jz ULMOVE            ;��תָ��
	dec word[y]          ;y��1
	inc word[x]          ;x��1
	jmp SHOW             ;��ת��PRINT
URMOVE:
    mov byte[dir],u_r    ;��u_r��ֵ����dir
	cmp word[y],39       ;�Ƚ�y��38�������ͬ������ת��ULMOVE���ж��ַ��Ƿ񵽴�����ұ߽磩
	jz ULMOVE            ;��תָ��
	cmp word[x],0        ;�Ƚ�x��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������ϱ߽磩
	jz DRMOVE            ;��תָ��
	inc word[y]          ;y��1
	dec word[x]          ;x��1
	jmp SHOW             ;��ת��PRINT
ULMOVE:
    mov byte[dir],u_l    ;��u_l��ֵ����dir
	cmp byte[y],0        ;�Ƚ�y��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������߽磩
	jz URMOVE            ;��תָ��
	cmp byte[x],0        ;�Ƚ�x��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������ϱ߽磩
	jz DLMOVE            ;��תָ��
	dec word[y]          ;y��1
	dec word[x]          ;x��1
	jmp SHOW             ;��ת��PRINT
SHOW:
    inc byte[cnt]        ;cnt++
	cmp byte[cnt],0fh    ;cnt��0fh�Ƚϴ�С
	jz CHANGE            ;����ͬ����ת��CHANGE
	jmp PRINT            ;��ת��PRINT
CHANGE:
    mov byte[cnt],2      ;cnt=2
	add byte[color],10h  ;color+=0x10
	cmp byte[color],7fh  ;�Ƚ�color��7fh
	jz CHANGE2           ;��ͬ����ת��CHANGE2
	jmp PRINT            ;��ת��PRINT
CHANGE2:
    mov byte[color],1fh  ;color=0x1f
PRINT:
    mov ax,[x]           ;��x��ֵ����ax�Ĵ�����
	imul ax,ax,80        ;��ax�Ĵ������ֵ��80��ˣ��浽ax�Ĵ����У���x�У�
	add ax,[y]           ;��y��ֵ��ax�Ĵ������ֵ��ӣ��浽ax�Ĵ�����
	imul ax,ax,2         ;��ax�Ĵ������ֵ��2��ˣ��浽ax�Ĵ����У���y�У�
	mov bx,ax            ;��ax��ֵ����bx��
	mov al,'Z'           ;�ѡ�Z���ַ������al�Ĵ���
	mov ah,byte[cnt]     ;���ڴ���cnt��ֵȡ���Ĵ���ah��
	mov [es:bx],ax       ;��ax��ֵд���Դ��ж�Ӧ��λ��
	; mov ax,24            ;ax=24
	; sub ax,word[x]       ;ax-=[x]
	; imul ax,ax,80        ;����Ϊ��һ����ĸ����ʾ���̣�ԭ��ͬ��
	; mov bx,79
	; sub bx,[y]           ;���һ����ĸ��������
	; add ax,bx
	; imul ax,ax,2
	; mov bx,ax
	; mov al,'Z'           ;�͵�һ����ĸ��ͬ�����ڹ۲�
	; mov ah,byte[cnt]
	; mov [es:bx],ax       ;��ax��ֵд���Դ��ж�Ӧ��λ��
	jmp SHOW_NAME        ;������ʾ������ѧ�ŵĳ����
	jmp BEGIN            ;��ת��BEGIN
SHOW_NAME:             
    mov word[xx],0      ;��0����xx�У���ʾ����ѧ�ŵ������꣩
	mov cx,2             ;��2����cx�Ĵ����У���2�У�
STEP1:
    push cx              ;��cxѹջ
	mov word[yy],0      ;��0����yy�У���ʾ����ѧ�ŵĺ����꣩
	mov cx,18            ;��18����cx�Ĵ����У���18�У�
STEP2:
    call CAL             ;����CAL��
	mov byte[es:bx],' '  ;�ÿո������λ��
	mov byte[es:bx+1],7fh;��ɫ��
	inc word[yy]         ;yy��1
	loop STEP2           ;����STEP2ѭ��
	pop cx               ;����ջ��Ԫ�أ��浽cx��
	inc word[xx]         ;xx��1
	loop STEP1           ;����STEP1ѭ��
	mov word[xx],0      ;��0����xx�У���һ�У�
	mov word[yy],0      ;��0����yy��
	mov si,0             ;�ַ�������������ʼ��Ϊ0
	mov cx,18            ;�ַ�������Ϊ18
STEP3: 
    call CAL             ;����CAL��
	mov al,byte[name1+si];���ַ���name1��siλ�浽al�Ĵ�����
	mov byte[es:bx],al   ;������ַ�
	inc word[yy]         ;yy��1
	inc si               ;si��1
	loop STEP3           ;����STEP3ѭ��
	mov word[xx],1      ;��1����xx�У���һ�У�
    mov word[yy],5      ;��5����yy��
	mov si,0             ;�ַ�������������ʼ��Ϊ0
	mov cx,8            ;�ַ�������Ϊ8
STEP4: 
    call CAL             ;����CAL��
	mov al,byte[name2+si];���ַ���name2��siλ�浽al�Ĵ�����
	mov byte[es:bx],al   ;������ַ�
	inc word[yy]         ;yy��1
	inc si               ;si��1
	loop STEP4           ;����STEP4ѭ��
	push es              ;��esѹջ
	mov ax,0             ;��0�浽ax�Ĵ�����
	mov es,ax            ;��ax���es�Ĵ�����(��ʼ��ַΪ0)
	cmp word [es:600h],1 ;�Ƚ�600h��ַ��ֵ�Ƿ�Ϊ1������ǣ����zf��1��������0
	pop es               ;����es
	jz TIME              ;���zf��ֵ��1��������TIME��
	mov cx,0f0h          ;��0fh�浽cx��
	call DELAY           ;����DELAY��
	jmp BEGIN            ;��ת��BEGIN
TIME:
    mov cx,090h          ;��090h���cx�Ĵ�����
	call DELAY           ;����DELAY��
	ret                  ;����
CAL: 
    mov ax,word[xx]      ;��xx��ֵ����ax�Ĵ���
	mov bx,80            ;��80����bx�Ĵ���
	mul bx               ;ax=ax*bx�������xx�е��Դ�λ�ã�
	add ax,word[yy]      ;��yy��ֵ�ӽ�ax�Ĵ���
	mov bx,2             ;��2����bx�Ĵ���
	mul bx               ;ax*bx�������xx�У���yy�е��Դ�λ�ã�
	mov bx,ax            ;��ax�Ĵ�����ֵ����bx�Ĵ���
	ret                  ;����
DELAY:
DELAY1:                   
	push cx              ;��cxѹջ
	mov cx,0ffffh        ;��ջ�����Ĵ����д���0ffffh
DELAY2:
	loop DELAY2          ;���cx��0���ص�DELAY2
	pop cx               ;��ջ��Ԫ�ص������浽cx�Ĵ���
	loop DELAY1          ;���cx��0���ص�DELAY1
	ret                  ;����
end:
    jmp $                  ;����

DEFINE:                    ;�궨��
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
	name1 db 'coded by zongjiaxi'  ;�ڼ�ϣ
	name2 db '15352461' ;15352461
	times 1022-($-$$) db 0
	db 0x55,0xaa