org  7c00h		                 ; BIOS���������������ص�0:7C00h��������ʼִ��
BaseOfKernal equ 8000h
OffSetOfKernal equ 100h         ;���ں˵ĵ�ַ��Ϊ8100h
Start:                           ;�����̻�Ӳ���ϵ����������������ڴ��ES:BX����
      mov ax,BaseOfKernal
	  ;mov ax,cs                  ;�ε�ַ ; ������ݵ��ڴ����ַ
      mov es,ax                  ;���öε�ַ������ֱ��mov es,�ε�ַ��
      mov bx,OffSetOfKernal      ;ƫ�Ƶ�ַ; ������ݵ��ڴ�ƫ�Ƶ�ַ
      mov ah,2                   ;���ܺ�
      mov al,12                  ;������
      mov dl,0                   ;�������� ; ����Ϊ0��Ӳ�̺�U��Ϊ80H
      mov dh,0                   ;��ͷ�� ; ��ʼ���Ϊ0
      mov ch,0                   ;����� ; ��ʼ���Ϊ0
      mov cl,12                  ;��ʼ������ ; ��ʼ���Ϊ12
      int 13H                    ;���ö�����BIOS��13h����
	  jmp BaseOfKernal:OffSetOfKernal      ;��ת���ں˵ĵ�ַ�����г���
AfterRun:                        ;
      jmp $                      ;����ѭ��

	  times 510-($-$$) db 0      ;512�ֽڵ�����
	  db 0x55,0xaa               ;
	  incbin 'prog1.bin'         ;����ļ�������
	  incbin 'prog2.bin'
	  incbin 'prog3.bin'
	  incbin 'prog4.bin'
	  incbin 'int_caller.bin'
	  incbin 'os1.com'
	  