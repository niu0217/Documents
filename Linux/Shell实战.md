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