mov ax,0xB800          ;���ı������Դ���ʼ��ַ�ŵ��Ĵ���ax
mov es,ax              ;���Ĵ���ax������ݴ��͵��Ĵ���es��
mov byte[es:00],'Z'    ;��'Z'�ַ��ŵ�es�Ĵ�����0x01λ�ã���ʾҪ��ʾ���ַ�
mov byte[es:01],21     ;��21�ŵ�es�Ĵ�����0x02λ�ã���ʾ'Z'�ַ�����ʾ�ĸ�ʽ
mov byte[es:06],'1'
mov byte[es:08],'5'
mov byte[es:10],'3'
mov byte[es:12],'5'
mov byte[es:14],'2'
mov byte[es:16],'4'
mov byte[es:18],'6'
mov byte[es:20],'1'
mov byte[es:166],'z'
mov byte[es:168],'o'
mov byte[es:170],'n'
mov byte[es:172],'g'
mov byte[es:174],'j'
mov byte[es:176],'i'
mov byte[es:178],'a'
mov byte[es:180],'x'
mov byte[es:182],'i'


jmp $                  ;����
