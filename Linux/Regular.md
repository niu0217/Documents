# Regular

## 1. 基本规则

| RE 字符   | 意义和范例                                                   |
| --------- | ------------------------------------------------------------ |
| `^word`   | 意义：带查找的字符串word在行首；<br>举例：查找行首为`#`开始的那一行，并列出行号；<br>`grep -n '^#' regular_express.txt` |
| `word$`   |                                                              |
| `.`       |                                                              |
| `\`       |                                                              |
| `*`       |                                                              |
| `[list]`  |                                                              |
| `[n1-n2]` |                                                              |
| `[^list]` |                                                              |
| `\{n,m\}` |                                                              |

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