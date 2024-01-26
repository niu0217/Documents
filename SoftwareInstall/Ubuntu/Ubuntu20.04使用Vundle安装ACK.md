# Ubuntu20.04使用Vundle安装ACK

## 必要条件

必须必须必须安装了Vundle。

## [ACK官网](https://github.com/mileszs/ack.vim)

## 安装步骤

1. 编辑文件：`vi ~/.vimrc`

   ```bash
   "安装插件管理器 Vundle"
   set nocompatible
   filetype off
   
   " 加入Vundle插件的路径
   set rtp+=~/.vim/bundle/Vundle.vim
   call vundle#begin()
   
   Plugin 'VundleVim/Vundle.vim' "这个必须要加
   Plugin 'mileszs/ack.vim'
   
   call vundle#end()            " required
   filetype plugin indent on    " required
   ```

   其中`Plugin 'mileszs/ack.vim'`是我们刚才加入进去的，然后退出并保存。

2. 打开 Vim：

   ```bash
   vim
   ```

   然后键入下列命令安装插件： 

   ```bash
   :PluginInstall
   ```

   等几秒就会出现一个Done！你的界面变成了双编辑器，安装成功，退出就ok了。

   可能发生的问题：配置好了vim 的ack插件，但是使用的时候报错，提示No command Ack，一开始以为是ack 的用法有问题，实际上是没有安装

   **安装**

   在Ubuntu平台安装ack插件的指令如下

   ```bash
   sudo apt install  ack-grep
   ```

   此时就完成了所有的安装

## ACK使用方法

在当前目录及其子目录下查找包含 "example" 的所有行：

```bash
:Ack example
```

