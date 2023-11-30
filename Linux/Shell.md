# Shell

## 1. 基础

### 1.1 命令执行顺序

1、以相对/绝对路径执行命令，例如【/bin/ls】或【./ls】

2、由alias找到该命令来执行

3、由bash内置的（builtin）命令来执行

4、通过$PATH这个变量的顺序查找到的第一个命令来执行

同时，我们可以通过命令`type -a 命令`来查看命令的的执行顺序。比如：

```bash
ubuntu@niu0217:~$ type -a ls
ls is aliased to `ls --color=auto'
ls is /usr/bin/ls
ls is /bin/ls
ubuntu@niu0217:~$
ubuntu@niu0217:~$ type -a echo
echo is a shell builtin
echo is /usr/bin/echo
echo is /bin/echo
ubuntu@niu0217:~$
```

### 1.2 快速编辑与执行

```bash
ubuntu@niu0217:~/Dev/test$ cp comp/data1.txt comp/data2.txt \
> comp/data3.txt ./
```

中间用`\`后面跟`enter`来实现执行长命令。

| 组合键     | 功能                   |
| ---------- | ---------------------- |
| [ctrl] + u | 从光标处向前删除字符串 |
| [ctrl] + k | 从光标处向后删除字符串 |
| [ctrl] + a | 让光标移动到命令最前面 |
| [ctrl] + e | 让光标移动到命令最后面 |

### 1.3 别名

设置别名：

```bash
ubuntu@niu0217:~/Dev/Test$ alias grep='grep --color=auto'
ubuntu@niu0217:~/Dev/Test$ alias
alias grep='grep --color=auto'
ubuntu@niu0217:~/Dev/Test$
```

取消别名：

```bash
ubuntu@niu0217:~/Dev/Test$ unalias grep
```

此时的别名只是暂时有效，想让别名永久生效：

+ 打开`/etc/profile`文件
+ 在文件最后添加你想要的别名，比如`alias grep='grep --color=auto'`
+ 然后`source /etc/profile`

此时就是永久生效。

解释：

> profile（/etc/profile），**用于设置系统级的环境变量和启动程序，在这个文件下配置会对所有用户生效**。 当用户登录（login）时，文件会被执行，并从/etc/profile. d目录的配置文件中查找shell设置

当登入系统时候获得一个shell进程时，其读取环境设定档如下:

![环境变量读取顺序](Shell.assets/环境变量读取顺序.jpeg) 

图片来源：https://cloud.tencent.com/developer/article/1116370

## 2. 脚本

### 2.1 注意事项

+ 第一行`#!/bin/bash`，作用是声明这个脚本使用的shell名称，非常重要！！！
+ 程序内容的说明：
  + 1、内容与功能
  + 2、版本信息
  + 3、作者与联系方式
  + 4、建文件日期
  + 5、历史记录

### 2.2 hello

```sh
```

