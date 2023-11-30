# Regular

## 1. 基本规则

特别注意⚠️：和通配符的含义不相同。这是正则表达式。

| RE 字符   | 意义和范例                                                   |
| --------- | ------------------------------------------------------------ |
| `^word`   | 意义：待查找的字符串word在行首；<br>举例：查找行首为`#`开始的那一行，并列出行号；<br>`grep -n '^#' regular_express.txt` |
| `word$`   | 意义：待查找的字符串word在行尾；<br>举例：将行尾为`!`的那一行打印出来，并列出行号；<br>`grep -n '!$' regular_express.txt` |
| `.`       | 意义：代表【一定有一个任意字符】的字符；<br>举例：e与e的中间【一定】仅有一个字符，空格符也是字符；<br>`grep -n 'e.e' regular_express.txt` |
| `\`       | 意义：转义符，将特殊符号的特殊意义去除；<br>举例：查找含有单引号`'`的那一行；<br>`grep -n \' regular_express.txt` |
| `*`       | 意义：重复0个或无穷多个的前一个RE字符；<br>举例：查找`es ess esss`等的字符串；<br>`grep -n 'ess*' regular_express.txt` |
| `.*`      | `.`和`*`组合起来的。非常重要！！<br>`.`代表任意字符。`*`代表重复前一个字符，0次或多次。因此`.*`就是重复任意字符，0次或多次<br>举例：g开头和g结尾，中间任意个字符的字符串；<br>`grep -n 'g.*g' regular_express.txt` |
| `[list]`  | 意义：字符集合的RE字符，里面列出想要选取的【字符】；<br>举例：`grep -n 'g[ld]' regular_express.txt` |
| `[n1-n2]` | 意义：字符集合的RE字符，里面列出想要选取的【字符范围】；<br>举例：`grep -n '[A-Z]' regular_express.txt` |
| `[^list]` | 意义：字符集合的RE字符，里面列出不要的【字符串或范围】；<br>举例：`grep -n 'oo[^t]' regular_express.txt` |
| `\{n,m\}` | 意义：连续n到m个的【前一个RE字符】；<br>意义：若为`\{n\}`，则是连续n个的【前一个RE字符】；<br>意义：若为`\{n,\}`，则是连续n个以上的【前一个RE字符】；<br>举例：`grep -n 'go\{2,3\}g' regular_express.txt` |

## 2. 使用grep

```bash
ubuntu@niu0217:~/Dev/Test$ cat -n regular_express.txt
     1	"Open Source" is a good mechanism to develop programs.
     2	apple is my favorite food.
     3	Football game is not use feet only.
     4	this dress doesn't fit me.
     5	However, this dress is about $ 3183 dollars.^M
     6	GNU is free air not free beer.^M
     7	Her hair is very beauty.^M
     8	I can't finish the test.^M
     9	Oh! The soup taste good.^M
    10	motorcycle is cheap than car.
    11	This window is clear.
    12	the symbol '*' is represented as start.
    13	Oh!     My god!
    14	The gd software is a library for drafting programs.^M
    15	You are the best is mean you are the no. 1.
    16	The world <Happy> is the same with "glad".
    17	I like dog.
    18	google is the best tools for search keyword.
    19	goooooogle yes!
    20	go! go! Let's go.
    21	# I am VBird
    22
ubuntu@niu0217:~/Dev/Test$
```

```bash
# the开头的行
ubuntu@niu0217:~/Dev/Test$ grep -n '^the' regular_express.txt
12:the symbol '*' is represented as start.
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 开头是小写字母
ubuntu@niu0217:~/Dev/Test$ grep -n '^[a-z]' regular_express.txt
2:apple is my favorite food.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
12:the symbol '*' is represented as start.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
ubuntu@niu0217:~/Dev/Test$
ubuntu@niu0217:~/Dev/Test$ grep -n '^[[:lower:]]' regular_express.txt
2:apple is my favorite food.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
12:the symbol '*' is represented as start.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 不是字母开头 注意^在外面和在[]内的含义是不同的,外面是开头，里面是取反操作
ubuntu@niu0217:~/Dev/Test$ grep -n '^[^a-zA-Z]' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
21:# I am VBird
ubuntu@niu0217:~/Dev/Test$
ubuntu@niu0217:~/Dev/Test$ grep -n '^[^[:alpha:]]' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
21:# I am VBird
ubuntu@niu0217:~/Dev/Test$
```

```bash
# .结尾
ubuntu@niu0217:~/Dev/Test$ grep -n '\.$' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
11:This window is clear.
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
17:I like dog.
18:google is the best tools for search keyword.
20:go! go! Let's go.
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 取5～10行
ubuntu@niu0217:~/Dev/Test$ cat -An regular_express.txt | head -n 10 | tail -n 6
     5	However, this dress is about $ 3183 dollars.^M$
     6	GNU is free air not free beer.^M$
     7	Her hair is very beauty.^M$
     8	I can't finish the test.^M$
     9	Oh! The soup taste good.^M$
    10	motorcycle is cheap than car.$
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 找出空白行
ubuntu@niu0217:~/Dev/Test$ grep -n '^$' regular_express.txt
22:
ubuntu@niu0217:~/Dev/Test$
```

```bash
ubuntu@niu0217:~/Dev/Test$ cat -n /etc/rsyslog.conf
     1	# /etc/rsyslog.conf configuration file for rsyslog
     2	#
     3	# For more information install rsyslog-doc and see
     4	# /usr/share/doc/rsyslog-doc/html/configuration/index.html
     5	#
     6	# Default logging rules can be found in /etc/rsyslog.d/50-default.conf
     7
     8
     9	#################
    10	#### MODULES ####
    11	#################
    12
    13	module(load="imuxsock") # provides support for local system logging
    14	#module(load="immark")  # provides --MARK-- message capability
    15
    16	# provides UDP syslog reception
    17	#module(load="imudp")
    18	#input(type="imudp" port="514")
    19
    20	# provides TCP syslog reception
    21	#module(load="imtcp")
    22	#input(type="imtcp" port="514")
    23
    24	# provides kernel logging support and enable non-kernel klog messages
    25	module(load="imklog" permitnonkernelfacility="on")
    26
    27	###########################
    28	#### GLOBAL DIRECTIVES ####
    29	###########################
    30
    31	#
    32	# Use traditional timestamp format.
    33	# To enable high precision timestamps, comment out the following line.
    34	#
    35	$ActionFileDefaultTemplate RSYSLOG_TraditionalFileFormat
    36
    37	# Filter duplicated messages
    38	$RepeatedMsgReduction on
    39
    40	#
    41	# Set the default permissions for all log files.
    42	#
    43	$FileOwner syslog
    44	$FileGroup adm
    45	$FileCreateMode 0640
    46	$DirCreateMode 0755
    47	$Umask 0022
    48	$PrivDropToUser syslog
    49	$PrivDropToGroup syslog
    50
    51	#
    52	# Where to place spool and state files
    53	#
    54	$WorkDirectory /var/spool/rsyslog
    55
    56	#
    57	# Include all config files in /etc/rsyslog.d/
    58	#
    59	$IncludeConfig /etc/rsyslog.d/*.conf
ubuntu@niu0217:~/Dev/Test$

#简化
ubuntu@niu0217:~/Dev/Test$ grep -v '^$' /etc/rsyslog.conf | grep -v '^#'
module(load="imuxsock") # provides support for local system logging
module(load="imklog" permitnonkernelfacility="on")
$ActionFileDefaultTemplate RSYSLOG_TraditionalFileFormat
$RepeatedMsgReduction on
$FileOwner syslog
$FileGroup adm
$FileCreateMode 0640
$DirCreateMode 0755
$Umask 0022
$PrivDropToUser syslog
$PrivDropToGroup syslog
$WorkDirectory /var/spool/rsyslog
$IncludeConfig /etc/rsyslog.d/*.conf
ubuntu@niu0217:~/Dev/Test$
```

```bash
# g??d g和d之间一定有两个字符
ubuntu@niu0217:~/Dev/Test$ grep -n 'g..d' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.^M
16:The world <Happy> is the same with "glad".
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 查找需要至少2个o的字符串
ubuntu@niu0217:~/Dev/Test$ grep -n 'ooo*' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 字符串开头与结尾都是g,但是两个g之间仅能存在至少一个o,比如gog、goog、gooooog
ubuntu@niu0217:~/Dev/Test$ grep -n 'goo*g' regular_express.txt
18:google is the best tools for search keyword.
19:goooooogle yes!
ubuntu@niu0217:~/Dev/Test$
```

```bash
#g开头与g结尾的字符串，其中的字符串可有可无
#.代表任意字符。*代表重复前一个字符，0次或多次。因此.*就是重复任意字符，0次或多次
ubuntu@niu0217:~/Dev/Test$ grep -n 'g.*g' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
14:The gd software is a library for drafting programs.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.
ubuntu@niu0217:~/Dev/Test$
```

```bash
# 查找两个o的字符串
ubuntu@niu0217:~/Dev/Test$ grep -n 'o\{2\}' regular_express.txt
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.^M
18:google is the best tools for search keyword.
19:goooooogle yes!
ubuntu@niu0217:~/Dev/Test$

# 查找g后面是2个到5个o，然后再接一个g的字符串
ubuntu@niu0217:~/Dev/Test$ grep -n 'go\{2,5\}g' regular_express.txt
18:google is the best tools for search keyword.
ubuntu@niu0217:~/Dev/Test$

# 查找g后面是2及以上的o，然后再接一个g的字符串
ubuntu@niu0217:~/Dev/Test$ grep -n 'go\{2,\}g' regular_express.txt
18:google is the best tools for search keyword.
19:goooooogle yes!
ubuntu@niu0217:~/Dev/Test$
```

## 3. 使用sed

```bash
#将/etc/passwd的内容列出并且打印行号，同时将2～行删除
ubuntu@niu0217:~/Dev/Test$ nl /etc/passwd | sed '2,5d'
     1	root:x:0:0:root:/root:/bin/bash
     6	games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7	man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
```

```bash
#将/etc/passwd的第2行后面加入字符drink tea
ubuntu@niu0217:~/Dev/Test$ nl /etc/passwd | sed '2a drink tea'
     1	root:x:0:0:root:/root:/bin/bash
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
drink tea
     3	bin:x:2:2:bin:/bin:/usr/sbin/nologin
```

```bash
#将/etc/passwd的第2行后面新增两行字符串
ubuntu@niu0217:~/Dev/Test$ nl /etc/passwd | sed '2a drink tea....\
> ghghghh'
     1	root:x:0:0:root:/root:/bin/bash
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
drink tea....
ghghghh
     3	bin:x:2:2:bin:/bin:/usr/sbin/nologin
```

```bash
#替换2～5行的数据为no no bo
ubuntu@niu0217:~/Dev/Test$ nl /etc/passwd | sed '2,5c no no bo'
     1	root:x:0:0:root:/root:/bin/bash
no no bo
     6	games:x:5:60:games:/usr/games:/usr/sbin/nologin
```

```bash
#打印你想要的行
ubuntu@niu0217:~/Dev/Test$ nl /etc/passwd | sed -n '2,5p'
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
     3	bin:x:2:2:bin:/bin:/usr/sbin/nologin
     4	sys:x:3:3:sys:/dev:/usr/sbin/nologin
     5	sync:x:4:65534:sync:/bin:/bin/sync
ubuntu@niu0217:~/Dev/Test$
```

```bash
#提取IP地址
ubuntu@niu0217:~/Dev/Test$ /sbin/ifconfig eth0
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.0.16  netmask 255.255.252.0  broadcast 10.0.3.255
        inet6 fe80::5054:ff:fe8b:5282  prefixlen 64  scopeid 0x20<link>
        ether 52:54:00:8b:52:82  txqueuelen 1000  (Ethernet)
        RX packets 33407989  bytes 7436261956 (7.4 GB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 31683094  bytes 5649778977 (5.6 GB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
        
ubuntu@niu0217:~/Dev/Test$ /sbin/ifconfig eth0 | grep 'inet ' | sed 's/^.*inet//g'  | sed 's/ *netmask.*$//g'
 10.0.0.16
ubuntu@niu0217:~/Dev/Test$
```

```bash
#将每一行.结尾的替换成!
ubuntu@niu0217:~/Dev/Test$ sed -i 's/\.$/\!/g' regular_express.txt
ubuntu@niu0217:~/Dev/Test$ cat -n regular_express.txt
     1	"Open Source" is a good mechanism to develop programs!
     2	apple is my favorite food!
     3	Football game is not use feet only!
     4	this dress doesn't fit me!
     5	However, this dress is about $ 3183 dollars.^M
     6	GNU is free air not free beer.^M
     7	Her hair is very beauty.^M
     8	I can't finish the test.^M
     9	Oh! The soup taste good.^M
    10	motorcycle is cheap than car!
    11	This window is clear!
    12	the symbol '*' is represented as start!
    13	Oh!     My god!
    14	The gd software is a library for drafting programs.^M
    15	You are the best is mean you are the no. 1!
    16	The world <Happy> is the same with "glad"!
    17	I like dog!
    18	google is the best tools for search keyword!
    19	goooooogle yes!
    20	go! go! Let's go!
    21	# I am VBird
    22
ubuntu@niu0217:~/Dev/Test$
```

```bash
#在文件的最后一行添加# this is a test
ubuntu@niu0217:~/Dev/Test$ sed -i '$a #this is a test' regular_express.txt
ubuntu@niu0217:~/Dev/Test$ cat -n regular_express.txt
     1	"Open Source" is a good mechanism to develop programs!
     2	apple is my favorite food!
     3	Football game is not use feet only!
     4	this dress doesn't fit me!
     5	However, this dress is about $ 3183 dollars.^M
     6	GNU is free air not free beer.^M
     7	Her hair is very beauty.^M
     8	I can't finish the test.^M
     9	Oh! The soup taste good.^M
    10	motorcycle is cheap than car!
    11	This window is clear!
    12	the symbol '*' is represented as start!
    13	Oh!     My god!
    14	The gd software is a library for drafting programs.^M
    15	You are the best is mean you are the no. 1!
    16	The world <Happy> is the same with "glad"!
    17	I like dog!
    18	google is the best tools for search keyword!
    19	goooooogle yes!
    20	go! go! Let's go!
    21	# I am VBird
    22
    23	#this is a test
ubuntu@niu0217:~/Dev/Test$
```

## 4. 扩展规则

| RE 字符 | 意义和范例                                                   |
| ------- | ------------------------------------------------------------ |
| `+`     | 意义：重复【一个或一个以上】的前一个RE字符；<br>举例：查找`god good gooood`等字符串，`o+`代表【一个以上的o】；<br>`egrep -n 'go+d' regular_express.txt` |
| `?`     | 意义：【零个或一个】的前一个RE字符；<br>举例：查找`gd god`这个两个字符串，`o?`表示【空的或1个o】；<br>`egrep -n 'go?d' regular_express.txt` |
| `|`     | 意义：用或（or）的方式找出数个字符；<br>`egrep -n 'gd|good' regular_express.txt`<br>`egrep -n 'gd|good|dog' regular_express.txt` |
| `()`    | 意义：找出【群组】字符串；<br>举例：`egrep -n 'g(la|oo)d' regular_express.txt` |
| `()+`   | 意义：多个重复群组的判别；<br>举例：`echo 'AxyzxyzxyzxyzC' | egrep 'A(xyz)+C'`；<br>含义：查找开头是A，结尾是C，中间有一个以上的“xyz”字符串 |

## 5. 使用awk

```bash
ubuntu@niu0217:~/Dev/Test$ last -n 5
ubuntu   pts/0        125.85.244.64    Thu Nov 30 14:39   still logged in
ubuntu   pts/0        125.85.244.64    Thu Nov 30 13:06 - 14:37  (01:31)
ubuntu   pts/0        125.85.244.64    Thu Nov 30 11:46 - 12:26  (00:40)
ubuntu   pts/0        125.85.244.64    Thu Nov 30 11:28 - 11:46  (00:18)
ubuntu   pts/0        125.85.244.64    Thu Nov 30 11:22 - 11:28  (00:05)

wtmp begins Tue Apr 13 14:22:36 2021
ubuntu@niu0217:~/Dev/Test$ last -n 5 | awk '{print $1 "\t" $3}'
ubuntu	125.85.244.64
ubuntu	125.85.244.64
ubuntu	125.85.244.64
ubuntu	125.85.244.64
ubuntu	125.85.244.64

wtmp	Tue
ubuntu@niu0217:~/Dev/Test$
```

```bash
ubuntu@niu0217:~/Dev/Test$ last -n 5 | awk '{print $1 "\t lines: "NR"\t columns: " NF}'
ubuntu	 lines: 1	 columns: 10
ubuntu	 lines: 2	 columns: 10
ubuntu	 lines: 3	 columns: 10
ubuntu	 lines: 4	 columns: 10
ubuntu	 lines: 5	 columns: 10
	 lines: 6	 columns: 0
wtmp	 lines: 7	 columns: 7
ubuntu@niu0217:~/Dev/Test$
```

```bash
ubuntu@niu0217:~/Dev/Test$ cat /etc/passwd | awk '{FS=":"} $3 < 10 {print $1 "\t " $3 }'
root:x:0:0:root:/root:/bin/bash
daemon	 1
bin	 2
sys	 3
sync	 4
games	 5
man	 6
lp	 7
mail	 8
news	 9
ubuntu@niu0217:~/Dev/Test$
```

```bash
ubuntu@niu0217:~/Dev/Test$ cat /etc/passwd | awk 'BEGIN {FS=":"} $3 < 10 {print $1 "\t " $3 }'
root	 0
daemon	 1
bin	 2
sys	 3
sync	 4
games	 5
man	 6
lp	 7
mail	 8
news	 9
ubuntu@niu0217:~/Dev/Test$
```

```bash
ubuntu@niu0217:~/Dev/Test$ cat pay.txt
Name    1st     2nd     3th
VBird   23000   24000   25000
DMTsai  21000   20000   23000
Bird2   43000   42000   41000
ubuntu@niu0217:~/Dev/Test$ cat pay.txt | \
> awk 'NR==1{printf "%10s %10s %10s %10s %10s\n", $1, $2, $3, $4, "Total"}
> NR>=2{total = $2 + $3 + $4
> printf "%10s %10d %10d %10d %10.2f\n", $1, $2, $3, $4, total}'
      Name        1st        2nd        3th      Total
     VBird      23000      24000      25000   72000.00
    DMTsai      21000      20000      23000   64000.00
     Bird2      43000      42000      41000  126000.00
ubuntu@niu0217:~/Dev/Test$
```

