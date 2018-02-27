org 7c00h                                ;BIOS���������������ص�0:7C00h��������ʼִ��
PRO equ 0a100h                           ;������ݵ��ڴ�ƫ�Ƶ�ַ

START:
	mov ax,cs                            ;��ax�Ĵ�����ֵ��cs��ͬ
	mov ds,ax                            ;��ax(cs)��ֵ�浽ds�Ĵ�����(��ַƫ��) 
	mov es,ax                            ;��ax(cs)��ֵ�浽es�Ĵ�����(���ӶμĴ���) 
	mov dx,ax                            ;��ax(cs)��ֵ�浽dx�Ĵ�����
	call CLEAR                           ;����CLEAR�δ���(��������) 
	mov bp,string1                       ;��string1�ַ������bp�Ĵ���
	mov cx,string1_length                ;��string1�ַ����ĳ��ȴ��cx�Ĵ���
	mov ax,1301h                         ;��1301h���ax�Ĵ���(ah=13h:���ܺ�  al=01h:�����÷�ʽ)
	mov bx,000fh                         ;��000fh���bx�Ĵ���(bh=00h:��ʾҳΪ0  bl=0fh:�ڵװ�����)
	mov dx,090dh                         ;��0b10h���dx�Ĵ���(dh=0bh:��λ��  dl=10h:��λ��) 
	int 10h                              ;�жϣ��жϺ�Ϊ10h�����ܺ�Ϊ13h������ʾ�ַ���
	mov bp,string2                       ;��string2�ַ������bp�Ĵ���
	mov cx,string2_length                ;��string2�ַ����ĳ��ȴ��cx�Ĵ���
	mov dx,0a01h                         ;��0a10h���dx�Ĵ���(dh=0ch:��λ��  dl=10h:��λ��)
	int 10h
	mov bp,string3                       ;��string3�ַ������bp�Ĵ���
	mov cx,string3_length                ;��string3�ַ����ĳ��ȴ��cx�Ĵ���
	mov dx,0b00h                         ;��0b10h���dx�Ĵ���(dh=0dh:��λ��  dl=10h:��λ��)
	int 10h
	mov bp,string4                       ;��string4�ַ������bp�Ĵ���
	mov cx,string4_length                ;��string4�ַ����ĳ��ȴ��cx�Ĵ���
	mov dx,0c1ah                         ;��0c10h���dx�Ĵ���(dh=0eh:��λ��  dl=10h:��λ��)
	int 10h
	mov bp,string5                       ;��string5�ַ������bp�Ĵ���
	mov cx,string5_length                ;��string5�ַ����ĳ��ȴ��cx�Ĵ���
	mov dx,0d1ah                         ;��0d10h���dx�Ĵ���(dh=0fh:��λ��  dl=10h:��λ��)
	int 10h                              ;�жϣ��жϺ�Ϊ10h�����ܺ�Ϊ13h������ʾ�ַ���
	mov bp,string6                       ;��string6�ַ������bp�Ĵ���
	mov cx,string6_length                ;��string6�ַ����ĳ��ȴ��cx�Ĵ���
	mov dx,0e1ah                         ;��0e10h���dx�Ĵ���(dh=0fh:��λ��  dl=10h:��λ��)
	int 10h                              ;�жϣ��жϺ�Ϊ10h�����ܺ�Ϊ13h������ʾ�ַ���
BEGIN:
    mov ax,0100h                         ;��0100h���ax�Ĵ�����(ah=01h:���ܺ�  al=00h:ASCII��Ϊ0��������������Ϊ0)
	int 16h                              ;�жϣ��жϺ�Ϊ16h�����ܺ�Ϊ01h���������̻������Ƿ�������
	                                     ;��������ݣ������ݴ��al�Ĵ����У���zf����1������Ϊ0
	jnz RUN                              ;���zf�Ƿ�Ϊ0�������0������ת��RUN�δ��룬���򲻽��в���
	jmp BEGIN                            ;��ת��BEGIN�δ���
RUN:
    mov ax,0                             ;��00h���ax�Ĵ�����(ah=00h:���ܺ�  al=00h:ASCII��Ϊ0��������������Ϊ0)
	int 16h                              ;�жϣ��жϺ�Ϊ16h�����ܺ�Ϊ00h����������̵����룬���al�Ĵ�����
	cmp al,'1'                           ;�Ƚ�al�Ĵ����е�ֵ�Ƿ���'1'��ȣ������ȾͰ�zf��Ϊ1��������Ϊ0
	jz PRO1                              ;���zfΪ1������ת��PRO1�δ���
	cmp al,'2'                           ;�Ƚ�al�Ĵ����е�ֵ�Ƿ���'2'��ȣ������ȾͰ�zf��Ϊ1��������Ϊ0
	jz PRO2                              ;���zfΪ1������ת��PRO2�δ���
	cmp al,'3'                           ;�Ƚ�al�Ĵ����е�ֵ�Ƿ���'3'��ȣ������ȾͰ�zf��Ϊ1��������Ϊ0
	jz PRO3                              ;���zfΪ1������ת��PRO3�δ���
	cmp al,'4'                           ;�Ƚ�al�Ĵ����е�ֵ�Ƿ���'4'��ȣ������ȾͰ�zf��Ϊ1��������Ϊ0
	jz PRO4                              ;���zfΪ1������ת��PRO4�δ���
	jmp START                            ;��ת��START�δ���
PRO1:
    mov byte[choice],1                   ;��choice��ֵ��Ϊ1
	jmp LOAD                             ;��ת��LOAD�δ���
PRO2:
    mov byte[choice],2                   ;��choice��ֵ��Ϊ2
	jmp LOAD                             ;��ת��LOAD�δ���
PRO3:
    mov byte[choice],3                   ;��choice��ֵ��Ϊ3
	jmp LOAD                             ;��ת��LOAD�δ���
PRO4:
    mov byte[choice],4                   ;��choice��ֵ��Ϊ4
	jmp LOAD                             ;��ת��LOAD�δ���
LOAD:
    call CLEAR                           ;����CLEAR�δ���(��������) 
	mov ax,cs                            ;��ax�Ĵ�����ֵ��cs��ͬ
	mov es,ax                            ;��ax(cs)��ֵ�浽es�Ĵ�����(���ӶμĴ���)
	mov bx,PRO                           ;��PRO��ֵ�浽bx�Ĵ�����(������ݵ��ڴ�ƫ�Ƶ�ַ,[es:bx]ָ�����������ʼ��ַ)
	mov ax,0201h                         ;��0201h���ax�Ĵ���(ah=02h:���ܺţ�Ҳ�洢�����ǵĴ������  al=01h:������(1~255))
	mov dx,0                             ;��00h���dx�Ĵ���(dh=00h:��ͷ��  dl=00h:��������)
	mov cx,01h                           ;��02h���cx�Ĵ���(ch=00h:����ŵĵ�8λ  cl=01h:0~5λΪ��ʼ������)  ������
	add cl,byte[choice]                  ;cl�Ĵ�����ֵ����choice��ֵ��������cl�Ĵ�����
	                                     ;�˴������������ڵ�һ������������n���ӳ�����ڵ�1~n������
										 ;��ˣ�cl+n��Ϊ��n���ӳ���������úţ�ͨ���˷�����ȡ��������
	int 13h;                             ;�жϣ��жϺ�Ϊ13h�����ܺ�Ϊ02h����������
	jmp PRO                              ;��ת��PRO�δ���(PRO�ε�ַ�Ĵ���) 
CLEAR:
	push es                              ;��es�Ĵ�����ֵѹջ(Ҫ����es�Ĵ������ȱ���ԭ����ֵ)
	mov ax,0b800h                        ;��b800h���ax�Ĵ�����(�Դ���ʼλ��) 
	mov es,ax                            ;��ax�Ĵ�����ֵ���es�Ĵ�����
	mov word[x],0                        ;��x��ֵ��Ϊ0
	mov cx,25                            ;��25���cx�Ĵ���(��ʾ�������򳤶�)
LOOP1:	
	push cx                              ;��cx�Ĵ�����ֵѹջ(Ҫ����es�Ĵ������ȱ���ԭ����ֵ)
	mov word[y],0                        ;��y��ֵ��Ϊ0
	mov cx,80                            ;��80���cx�Ĵ���(��ʾ���ĺ��򳤶�)
LOOP2:
	mov ax,word[x]                       ;��x��ֵ���ax�Ĵ�����
	mov bx,80                            ;��80���bx�Ĵ�����
	mul bx                               ;����������(80*x)�����ax�Ĵ�����
	add ax,word[y]                       ;��y��ֵ�ӽ�ax�Ĵ�����
	mov bx,2                             ;��2���bx�Ĵ�����
	mul bx                               ;������ʵ����((80*x)+y)*2,���ax�Ĵ�����
	mov bx,ax                            ;��ax�Ĵ������ֵ���bx�Ĵ�����
	mov word[es:bx],00h                  ;�Ѹõ�ַ�����ֵ��Ϊ00h(�ڵ׺���)
	inc word[y]	                         ;y��ֵ��1
	loop LOOP2                           ;����LOOP2ѭ��
	pop cx                               ;��ջ��Ԫ�ص������浽cx�Ĵ�����
	inc word[x]                          ;x��ֵ��1
	loop LOOP1                           ;����LOOP1ѭ��
	pop es                               ;��ջ����Ԫ�ص������浽es�Ĵ�����
	RET                                  ;����CALL����һ�����
DEFINE:                                  ;�궨��
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
	times 510-($-$$) db 0                ;�����������510��0
	db 0x55,0xaa                         ;����55AA(������һ��512�ֽڣ��պ�һ������)
	incbin 'prog1.bin'                   ;�����������
	incbin 'prog2.bin'
	incbin 'prog3.bin'
	incbin 'prog4.bin'