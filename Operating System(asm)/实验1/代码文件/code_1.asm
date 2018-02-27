mov ax,0xB800          ;把文本窗口显存起始地址放到寄存器ax
mov es,ax              ;将寄存器ax里的内容传送到寄存器es里
mov byte[es:00],'Z'    ;把'Z'字符放到es寄存器的0x01位置，表示要显示的字符
mov byte[es:01],21     ;把21放到es寄存器的0x02位置，表示'Z'字符的显示的格式
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


jmp $                  ;结束
