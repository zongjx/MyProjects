;test for 'A'
START:
    mov ax,7c0h          ;���������ڴ��ַ����ʼΪ7c0h
	mov ds,ax            ;��7c0h������ݶμĴ���ds�У�ָ����ʼλ��
	mov ax,0b800h        ;���Դ����ʼλ��0b800h���ax�Ĵ���
	mov es,ax            ;��0b800h������ӶμĴ���es�У�ָ���Դ���ʼλ��
	mov word[x],-1       ;Ҫ��ʾ���ַ�����ʼ������
	mov word[y],-1       ;Ҫ��ʾ���ַ�����ʼ������
	mov byte[dir],d_r    ;���������䷽��ı���
BEGIN:
    mov cx,0a0h          ;��ջ�����Ĵ����д���0a0h
DELAY:
    push cx              ;��cxѹջ
	mov cx,0ffffh        ;��ջ�����Ĵ����д���0ffffh
DELAY2:
    loop DELAY2          ;���cx��0���ص�DELAY2
	pop cx               ;��ջ��Ԫ�ص������浽cx�Ĵ���
	loop DELAY           ;���cx��0���ص�DELAY
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
	cmp word[y],79       ;�Ƚ�y��79�������ͬ������ת��DLMOVE���ж��ַ��Ƿ񵽴�����ұ߽磩
	jz DLMOVE            ;��תָ��
	cmp word[x],24       ;�Ƚ�x��24�������ͬ������ת��URMOVE���ж��ַ��Ƿ񵽴������±߽磩
	jz URMOVE            ;��תָ��
	inc word[y]          ;y��1
	inc word[x]          ;x��1
	jmp PRINT            ;��ת��PRINT
DLMOVE:
	mov byte[dir],d_l    ;��d_l��ֵ����dir
	cmp word[y],0        ;�Ƚ�y��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������߽磩
	jz DRMOVE            ;��תָ��
	cmp word[x],24       ;�Ƚ�x��24�������ͬ������ת��ULMOVE���ж��ַ��Ƿ񵽴������±߽磩
	jz ULMOVE            ;��תָ��
	dec word[y]          ;y��1
	inc word[x]          ;x��1
	jmp PRINT            ;��ת��PRINT
URMOVE:
    mov byte[dir],u_r    ;��u_r��ֵ����dir
	cmp word[y],79       ;�Ƚ�y��79�������ͬ������ת��ULMOVE���ж��ַ��Ƿ񵽴�����ұ߽磩
	jz ULMOVE            ;��תָ��
	cmp word[x],0        ;�Ƚ�x��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������ϱ߽磩
	jz DRMOVE            ;��תָ��
	inc word[y]          ;y��1
	dec word[x]          ;x��1
	jmp PRINT            ;��ת��PRINT
ULMOVE:
    mov byte[dir],u_l    ;��u_l��ֵ����dir
	cmp byte[y],0        ;�Ƚ�y��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������߽磩
	jz URMOVE            ;��תָ��
	cmp byte[x],0        ;�Ƚ�x��0�������ͬ������ת��DRMOVE���ж��ַ��Ƿ񵽴������ϱ߽磩
	jz DLMOVE            ;��תָ��
	dec word[y]          ;y��1
	dec word[x]          ;x��1
	jmp PRINT            ;��ת��PRINT
PRINT:
    mov ax,[x]           ;��x��ֵ����ax�Ĵ�����
	imul ax,ax,80        ;��ax�Ĵ������ֵ��80��ˣ��浽ax�Ĵ����У���x�У�
	add ax,[y]           ;��y��ֵ��ax�Ĵ������ֵ��ӣ��浽ax�Ĵ�����
	imul ax,ax,2         ;��ax�Ĵ������ֵ��2��ˣ��浽ax�Ĵ����У���y�У�
	mov bx,ax            ;��ax��ֵ����bx��
	mov byte[es:bx],'A'  ;�ѡ�A���ַ������es+bx���Դ�λ��
	jmp BEGIN            ;��ת��BEGIN
end:
    jmp $                  ;����
DEFINE:                    ;�궨��
    d_r equ 1
	d_l equ 2
	u_r equ 3
	u_l equ 4
	x dw 0
	y dw 0
	dir db d_l	