# Shell

## 1. 快速编辑与执行

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

## 2. 别名

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

![img](https://ask.qcloudimg.com/http-save/yehe-1751832/kjopmerin0.jpeg) 

图片来源：https://cloud.tencent.com/developer/article/1116370
