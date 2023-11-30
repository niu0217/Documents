# Shell实战

## 1. 优雅的打印$PATH

```bash
ubuntu@niu0217:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
ubuntu@niu0217:~$ echo $PATH | tr ":" "\n"
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
/usr/games
/usr/local/games
/snap/bin
ubuntu@niu0217:~$
```

tr命令：https://www.runoob.com/linux/linux-comm-tr.html

`tr ":" "\n"`表示用`\n`来代替`:`

## 2. 新增环境变量

```bash
ubuntu@niu0217:~/bin$ PATH=${PATH}:~/bin
ubuntu@niu0217:~/bin$ echo $PATH | tr ":" "\n"
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
/usr/games
/usr/local/games
/snap/bin
/home/ubuntu/bin
ubuntu@niu0217:~/bin$
```

其余使用可以设置为：`export PATH`