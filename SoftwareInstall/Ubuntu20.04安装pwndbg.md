# Ubuntu20.04安装pwndbg

该方案来自于：[网址](https://hgg-bat.github.io/2021/10/04/pwn%E5%85%A5%E9%97%A8%E4%B9%8B%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA/#%E5%AE%89%E8%A3%85pwndbg-pwngdb-%E8%81%94%E5%90%88%E8%B0%83%E8%AF%95%E7%8E%AF%E5%A2%83)

**第一步：安装pwntools**

```bash
sudo apt-get install python3 python3-pip python3-dev git libssl-dev libffi-dev build-essential
sudo python3 -m pip install --upgrade pip
sudo python3 -m pip install --upgrade pwntools
```

**第二步：安装pwngdb和pwndbg**

```bash
cd ~/
git clone https://github.com/scwuaptx/Pwngdb.git 
cp ~/Pwngdb/.gdbinit ~/
```

```bash
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
./setup.sh
```

**第三步：修改文件**

```bash
vim ~/.gdbinit

注释掉第一行 然后在第二行写入
source ~/pwndbg/gdbinit.py
```

**简单使用**

```
带源码调试: gdb -q [file] -d [path]（默认为.）
打印链接库: vmmap
```

