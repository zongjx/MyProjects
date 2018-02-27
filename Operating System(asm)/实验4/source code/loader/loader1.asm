org  7c00h		                 ; BIOS将把引导扇区加载到0:7C00h处，并开始执行
BaseOfKernal equ 8000h
OffSetOfKernal equ 100h         ;把内核的地址设为8100h
Start:                           ;读软盘或硬盘上的若干物理扇区到内存的ES:BX处：
      mov ax,BaseOfKernal
	  ;mov ax,cs                  ;段地址 ; 存放数据的内存基地址
      mov es,ax                  ;设置段地址（不能直接mov es,段地址）
      mov bx,OffSetOfKernal      ;偏移地址; 存放数据的内存偏移地址
      mov ah,2                   ;功能号
      mov al,12                  ;扇区数
      mov dl,0                   ;驱动器号 ; 软盘为0，硬盘和U盘为80H
      mov dh,0                   ;磁头号 ; 起始编号为0
      mov ch,0                   ;柱面号 ; 起始编号为0
      mov cl,12                  ;起始扇区号 ; 起始编号为12
      int 13H                    ;调用读磁盘BIOS的13h功能
	  jmp BaseOfKernal:OffSetOfKernal      ;跳转至内核的地址，运行程序
AfterRun:                        ;
      jmp $                      ;无限循环

	  times 510-($-$$) db 0      ;512字节的设置
	  db 0x55,0xaa               ;
	  incbin 'prog1.bin'         ;导入的几个程序
	  incbin 'prog2.bin'
	  incbin 'prog3.bin'
	  incbin 'prog4.bin'
	  incbin 'int_caller.bin'
	  incbin 'os1.com'
	  