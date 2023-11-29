# Linux常用命令

## 1. 修改文件权限

`chgrp`：修改文件所属用户组

`chown`：修改文件拥有者

`chmod`：修改文件的权限（全能）

重要知识：

```
r:4
w:2
x:1
```

使用`chgrp`

```bash
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-r--r----- 1 ubuntu ubuntu 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$ sudo chgrp users hello.cpp
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-r--r----- 1 ubuntu users 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$
```

使用`chown`

```bash
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-r--r----- 1 ubuntu users 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$ sudo chown root hello.cpp
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-r--r----- 1 root users 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$
```

使用`chmod`

```bash
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-r--r----- 1 root users 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$ sudo chmod 777 hello.cpp
ubuntu@niu0217:~/Dev/test$ ls -l
total 4
-rwxrwxrwx 1 root users 315 Nov 28 12:54 hello.cpp
ubuntu@niu0217:~/Dev/test$
```

## 2. 文件查找

### 2.1 which

`which`：根据【PATH】这个环境变量所规范的路径，去查找执行文件的文件名。

```bash
ubuntu@niu0217:~$ which ifconfig
/usr/sbin/ifconfig
ubuntu@niu0217:~$
```

### 2.2 whereis

`whereis`：只在特定路径下去查找。

```bash
ubuntu@niu0217:~$ whereis -l
bin: /usr/bin
bin: /usr/sbin
bin: /usr/lib/x86_64-linux-gnu
bin: /usr/lib
bin: /usr/lib64
bin: /etc
bin: /usr/games
bin: /usr/local/bin
bin: /usr/local/sbin
bin: /usr/local/etc
bin: /usr/local/lib
bin: /usr/local/games
bin: /usr/include
bin: /usr/local
bin: /usr/libexec
bin: /usr/share
bin: /snap/bin
man: /usr/share/man/fr
man: /usr/share/man/cs
man: /usr/share/man/es
man: /usr/share/man/fi
man: /usr/share/man/zh_TW
man: /usr/share/man/man2
man: /usr/share/man/nl
man: /usr/share/man/man9
man: /usr/share/man/man7
man: /usr/share/man/man6
man: /usr/share/man/it
man: /usr/share/man/pt_BR
man: /usr/share/man/sr
man: /usr/share/man/pl
man: /usr/share/man/man1
man: /usr/share/man/pt
man: /usr/share/man/man3
man: /usr/share/man/man4
man: /usr/share/man/ru
man: /usr/share/man/ja
man: /usr/share/man/zh_CN
man: /usr/share/man/sl
man: /usr/share/man/man8
man: /usr/share/man/man5
man: /usr/share/man/ko
man: /usr/share/man/id
man: /usr/share/man/tr
man: /usr/share/man/sv
man: /usr/share/man/de
man: /usr/share/man/hu
man: /usr/share/man/da
man: /usr/share/info
src: /usr/src/linux-headers-5.4.0-42
src: /usr/src/linux-headers-5.4.0-42-generic
ubuntu@niu0217:~$
```

```bash
ubuntu@niu0217:~$ whereis ifconfig
ifconfig: /usr/sbin/ifconfig /usr/share/man/man8/ifconfig.8.gz
ubuntu@niu0217:~$
```

### 2.3 locate

`updatedb`：根据`/etc/updatedb.conf`的设置去查找系统硬盘内的文件，并更新`/var/lib/mlocate`内的数据库文件

`locate`：根据`/var/lib/mlocate`内的数据库记录，找出用户所输入关键词的文件名

使用：

```bash
ubuntu@niu0217:~$ locate -l 5 passwd
/etc/passwd
/etc/passwd-
/etc/pam.d/chpasswd
/etc/pam.d/passwd
/etc/security/opasswd
ubuntu@niu0217:~$
```

### 2.4 find

`find`：会查找磁盘，速度比较慢

使用：

```bash
# 查找过去系统上面24小时内有修改过内容的文件
ubuntu@niu0217:~$ find / -mtime 0
```

```bash
# 查找/etc下面的文件，如果文件日期比/etc/passwd新就列出来
ubuntu@niu0217:~$ find /etc -newer /etc/passwd
```

```bash
# 查找/home下面属于ubuntu的文件
ubuntu@niu0217:~$ find /home -user ubuntu
```

```bash
# 查找系统中不属于任何人的文件
ubuntu@niu0217:~$ find / -nouser
```

```bash
# 查找文件名为passwd的文件
ubuntu@niu0217:~$ find / -name passwd

# 查找文件名包含了passwd这个关键字的文件
ubuntu@niu0217:~$ find / -name "*passwd*"
```

```bash
# 查找/run目录下，文件类型为socket的文件名有哪些
ubuntu@niu0217:~$ find /run -type s
```

```bash
# 找出系统中大于1M的文件
ubuntu@niu0217:~$ find / -size +1M
```

## 3. 文件系统相关命令

查看你的Linux系统支持的文件系统有哪些：

```bash
ubuntu@niu0217:/$ ls -l /lib/modules/$(uname -r)/kernel/fs
total 280
drwxr-xr-x 2 root root  4096 Jul 24  2020 9p
drwxr-xr-x 2 root root  4096 Jul 24  2020 adfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 affs
drwxr-xr-x 2 root root  4096 Jul 24  2020 afs
drwxr-xr-x 2 root root  4096 Jul 24  2020 aufs
drwxr-xr-x 2 root root  4096 Jul 24  2020 autofs
drwxr-xr-x 2 root root  4096 Jul 24  2020 befs
drwxr-xr-x 2 root root  4096 Jul 24  2020 bfs
-rw-r--r-- 1 root root 27321 Jul 10  2020 binfmt_misc.ko
drwxr-xr-x 2 root root  4096 Jul 24  2020 btrfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 cachefiles
drwxr-xr-x 2 root root  4096 Jul 24  2020 ceph
drwxr-xr-x 2 root root  4096 Jul 24  2020 cifs
drwxr-xr-x 2 root root  4096 Jul 24  2020 coda
drwxr-xr-x 2 root root  4096 Jul 24  2020 cramfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 dlm
drwxr-xr-x 2 root root  4096 Jul 24  2020 efs
drwxr-xr-x 2 root root  4096 Jul 24  2020 erofs
drwxr-xr-x 2 root root  4096 Jul 24  2020 f2fs
drwxr-xr-x 2 root root  4096 Jul 24  2020 fat
drwxr-xr-x 2 root root  4096 Jul 24  2020 freevxfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 fscache
drwxr-xr-x 2 root root  4096 Jul 24  2020 fuse
drwxr-xr-x 2 root root  4096 Jul 24  2020 gfs2
drwxr-xr-x 2 root root  4096 Jul 24  2020 hfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 hfsplus
drwxr-xr-x 2 root root  4096 Jul 24  2020 hpfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 isofs
drwxr-xr-x 2 root root  4096 Jul 24  2020 jffs2
drwxr-xr-x 2 root root  4096 Jul 24  2020 jfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 lockd
drwxr-xr-x 2 root root  4096 Jul 24  2020 minix
drwxr-xr-x 5 root root  4096 Jul 24  2020 nfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 nfs_common
drwxr-xr-x 2 root root  4096 Jul 24  2020 nfsd
drwxr-xr-x 2 root root  4096 Jul 24  2020 nilfs2
drwxr-xr-x 2 root root  4096 Jul 24  2020 nls
drwxr-xr-x 2 root root  4096 Jul 24  2020 ntfs
drwxr-xr-x 5 root root  4096 Jul 24  2020 ocfs2
drwxr-xr-x 2 root root  4096 Jul 24  2020 omfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 orangefs
drwxr-xr-x 2 root root  4096 Jul 24  2020 overlayfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 pstore
drwxr-xr-x 2 root root  4096 Jul 24  2020 qnx4
drwxr-xr-x 2 root root  4096 Jul 24  2020 qnx6
drwxr-xr-x 2 root root  4096 Jul 24  2020 quota
drwxr-xr-x 2 root root  4096 Jul 24  2020 reiserfs
drwxr-xr-x 2 root root  4096 Jul 24  2020 romfs
-rw-r--r-- 1 root root 43833 Jul 10  2020 shiftfs.ko
drwxr-xr-x 2 root root  4096 Jul 24  2020 sysv
drwxr-xr-x 2 root root  4096 Jul 24  2020 ubifs
drwxr-xr-x 2 root root  4096 Jul 24  2020 udf
drwxr-xr-x 2 root root  4096 Jul 24  2020 ufs
drwxr-xr-x 2 root root  4096 Jul 24  2020 xfs
ubuntu@niu0217:/$
```

系统目前已加载到内存中支持的文件系统：

```bash
ubuntu@niu0217:/$ cat /proc/filesystems
nodev	sysfs
nodev	tmpfs
nodev	bdev
nodev	proc
nodev	cgroup
nodev	cgroup2
nodev	cpuset
nodev	devtmpfs
nodev	configfs
nodev	debugfs
nodev	tracefs
nodev	securityfs
nodev	sockfs
nodev	bpf
nodev	pipefs
nodev	ramfs
nodev	hugetlbfs
nodev	devpts
	ext3
	ext2
	ext4
	squashfs
	vfat
nodev	ecryptfs
	fuseblk
nodev	fuse
nodev	fusectl
nodev	mqueue
nodev	pstore
	btrfs
nodev	autofs
nodev	rpc_pipefs
nodev	overlay
nodev	aufs
nodev	binfmt_misc
ubuntu@niu0217:/$
```

查看文件容量：

```bash
ubuntu@niu0217:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            948M     0  948M   0% /dev
tmpfs           199M  1.1M  198M   1% /run
/dev/vda2        50G  8.2G   39G  18% /
tmpfs           994M   24K  994M   1% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           994M     0  994M   0% /sys/fs/cgroup
/dev/loop2       74M   74M     0 100% /snap/core22/864
/dev/loop3       41M   41M     0 100% /snap/snapd/20092
/dev/loop4       56M   56M     0 100% /snap/core18/2790
tmpfs           199M     0  199M   0% /run/user/1000
/dev/loop5       41M   41M     0 100% /snap/snapd/20290
/dev/loop6      153M  153M     0 100% /snap/lxd/26093
/dev/loop1       56M   56M     0 100% /snap/core18/2796
/dev/loop0      153M  153M     0 100% /snap/lxd/26200
ubuntu@niu0217:~$
```

## 4. 解压缩命令

### 4.1 gzip

解压缩文件：

```bash
ubuntu@niu0217:~/Dev/test/test1$ tree
.
└── hello.cpp

0 directories, 1 file
ubuntu@niu0217:~/Dev/test/test1$ gzip -v hello.cpp  #压缩文件
hello.cpp:	 48.9% -- replaced with hello.cpp.gz
ubuntu@niu0217:~/Dev/test/test1$ tree
.
└── hello.cpp.gz

0 directories, 1 file
ubuntu@niu0217:~/Dev/test/test1$ zcat hello.cpp.gz #打印压缩的文件内容
/* ************************************************************************
> File Name:     hello.cpp
> Author:        程序员Carl
> 微信公众号:    代码随想录
> Created Time:  Tue 28 Nov 2023 07:53:15 PM CST
> Description:
 ************************************************************************/

ubuntu@niu0217:~/Dev/test/test1$ tree
.
└── hello.cpp.gz

0 directories, 1 file
ubuntu@niu0217:~/Dev/test/test1$ gzip -d hello.cpp.gz #解压缩文件
ubuntu@niu0217:~/Dev/test/test1$ tree
.
└── hello.cpp

0 directories, 1 file
ubuntu@niu0217:~/Dev/test/test1$
```

```bash
# 用最佳压缩比压缩，并保留原文件
ubuntu@niu0217:~/Dev/test/test1$ tree
.
└── hello.cpp

0 directories, 1 file
ubuntu@niu0217:~/Dev/test/test1$ gzip -9 -c hello.cpp > hello.cpp.gz
ubuntu@niu0217:~/Dev/test/test1$ tree
.
├── hello.cpp
└── hello.cpp.gz

0 directories, 2 files
ubuntu@niu0217:~/Dev/test/test1$
```

### 4.2 bzip2

用法和`gzip`一样，但是压缩更好。相应的时间更长。

```bash
ubuntu@niu0217:~/Dev/test/test1$ tree
.
├── hello.cpp
└── hello.cpp.gz

0 directories, 2 files
ubuntu@niu0217:~/Dev/test/test1$ bzip2 -v hello.cpp
  hello.cpp:  1.529:1,  5.232 bits/byte, 34.60% saved, 315 in, 206 out.
ubuntu@niu0217:~/Dev/test/test1$ ls -l
total 8
-rw-rw-r-- 1 ubuntu ubuntu 206 Nov 28 19:53 hello.cpp.bz2
-rw-rw-r-- 1 ubuntu ubuntu 189 Nov 28 20:31 hello.cpp.gz
ubuntu@niu0217:~/Dev/test/test1$ bzip2 -d hello.cpp.bz2
ubuntu@niu0217:~/Dev/test/test1$ tree
.
├── hello.cpp
└── hello.cpp.gz

0 directories, 2 files
ubuntu@niu0217:~/Dev/test/test1$
```

### 4.3 xz

用法和`gzip`一样，但是压缩更好。相应的时间更长。

```bash
ubuntu@niu0217:~/Dev/test/test1$ tree
.
├── hello.cpp
└── hello.cpp.gz

0 directories, 2 files
ubuntu@niu0217:~/Dev/test/test1$ xz -v hello.cpp
hello.cpp (1/1)
  100 %               224 B / 315 B = 0.711
ubuntu@niu0217:~/Dev/test/test1$ ls -l
total 8
-rw-rw-r-- 1 ubuntu ubuntu 189 Nov 28 20:31 hello.cpp.gz
-rw-rw-r-- 1 ubuntu ubuntu 224 Nov 28 19:53 hello.cpp.xz
ubuntu@niu0217:~/Dev/test/test1$ xz -d hello.cpp.xz
ubuntu@niu0217:~/Dev/test/test1$ tree
.
├── hello.cpp
└── hello.cpp.gz

0 directories, 2 files
ubuntu@niu0217:~/Dev/test/test1$
```

### 4.4 tar

一般使用：

+ 压缩：`tar -jcv -f filename.tar.bz2 要被压缩的文件或目录名称`
+ 查询：`tar -jtv -f filename.tar.bz2`
+ 解压缩：`tar -jxv -f filename.tar.bz2 -C 想要解压缩的目录`

```bash
ubuntu@niu0217:~/Dev/test$ tree
.
├── data1.txt
├── data2.txt
├── data3.txt
└── data4.txt

0 directories, 4 files
ubuntu@niu0217:~/Dev/test$ tar -jcv -f data.tar.bz2 ./ #压缩
./
./data2.txt
./data1.txt
./data4.txt
./data3.txt
tar: .: file changed as we read it
ubuntu@niu0217:~/Dev/test$ tree
.
├── data1.txt
├── data2.txt
├── data3.txt
├── data4.txt
└── data.tar.bz2

0 directories, 5 files
ubuntu@niu0217:~/Dev/test$ tar -jtv -f data.tar.bz2 #查询
drwxrwxr-x ubuntu/ubuntu     0 2023-11-28 21:07 ./
-rw-rw-r-- ubuntu/ubuntu     0 2023-11-28 21:02 ./data2.txt
-rw-rw-r-- ubuntu/ubuntu     0 2023-11-28 21:02 ./data1.txt
-rw-rw-r-- ubuntu/ubuntu     0 2023-11-28 21:02 ./data4.txt
-rw-rw-r-- ubuntu/ubuntu     0 2023-11-28 21:02 ./data3.txt
ubuntu@niu0217:~/Dev/test$
ubuntu@niu0217:~/Dev/test$ mkdir comp
ubuntu@niu0217:~/Dev/test$ tree
.
├── comp
├── data1.txt
├── data2.txt
├── data3.txt
├── data4.txt
└── data.tar.bz2

1 directory, 5 files
ubuntu@niu0217:~/Dev/test$ tar -jxv -f data.tar.bz2 -C ./comp #解压缩
./
./data2.txt
./data1.txt
./data4.txt
./data3.txt
ubuntu@niu0217:~/Dev/test$ tree
.
├── comp
│   ├── data1.txt
│   ├── data2.txt
│   ├── data3.txt
│   └── data4.txt
├── data1.txt
├── data2.txt
├── data3.txt
├── data4.txt
└── data.tar.bz2

1 directory, 9 files
ubuntu@niu0217:~/Dev/test$
```

进阶使用：

+ 压缩：
  + `time tar -zpcv -f /root/etc.tar.gz /etc`
  + `time tar -jpcv -f /root/etc.tar.bz2 /etc `
  + `time tar -Jpcv -f /root/etc.tar.xz /etc`

+ 查看所占空间：`du -sm /etc`

+ 查看：`tar -jtv -f /root/etc.tar.bz2`

+ 解压：
  + `tar -jxv -f/root/etc.tar.bz2 -C /tmp`
