
nginx-1.16.0
====
gdb -- 调试相关操作
----

##### 1.如何查看数组内容<br>
```Bash
(gdb) p *md5@16
$6 = "B\314#u\177\321ZI\267:=+\244<\310", <incomplete sequence \315>
```



##### 2.如何打印16进制
```Bash
#    x  按十六进制格式显示变量。
#    d  按十进制格式显示变量。
#    u  按十六进制格式显示无符号整型。
#    o  按八进制格式显示变量。
#    t  按二进制格式显示变量。 
#    a  按十六进制格式显示变量。
#    c  按字符格式显示变量。
#    f  按浮点数格式显示变量。
  
(gdb) p/x *md5@16
$5 = {0x42, 0xcc, 0x23, 0x75, 0x7f, 0xd1, 0x5a, 0x49, 0xb7, 0x3a, 0x3d, 0x2b, 0xa4, 0x3c, 0xc8, 0xcd}
```
