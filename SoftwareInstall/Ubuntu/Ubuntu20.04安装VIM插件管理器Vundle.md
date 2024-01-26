# Ubuntu20.04安装VIM插件管理器Vundle

## [官网](https://github.com/VundleVim/Vundle.vim?tab=readme-ov-file#quick-start)

## 安装教程

参考资料：

+ https://zhuanlan.zhihu.com/p/98344227
+ https://cloud.tencent.com/developer/article/1722394

1. 首先用下面的命令将仓库clone下来到~/.vim/bundle/Vundle.vim上，估计以后的插件都会在bundle/这个文件夹下面。

   ```bash
   git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
   ```

   这一步可能出现的错误：GnuTLS recv error (-110): The TLS connection was non-properly terminated

   解决办法网址：https://stackoverflow.com/questions/52529639/gnutls-recv-error-110-the-tls-connection-was-non-properly-terminated

   具体方案：

   ```bash
   sudo apt remove git -y
   
   sudo apt update && sudo apt upgrade
   
   DEBIAN_FRONTEND=noninteractive
   
   sudo apt install build-essential autoconf dh-autoreconf libcurl4-openssl-dev \
                    tcl-dev gettext asciidoc docbook2x install-info \
                    libexpat1-dev libz-dev -y
   
   wget https://raw.githubusercontent.com/paul-nelson-baker/git-openssl-shellscript/master/compile-git-with-openssl.sh .
   
   sh ./compile-git-with-openssl.sh -skiptests
   ```

2. 编辑`~/.vimrc`

   vimrc是修改vim基本设置的文件，保存后下次打开自动生效，下面是github上面推荐的设置，其中有五个Plugin的命令，其中只有第一个需要加，其他都可以去掉。其他的几个Plugin的设置需要下载，由于网络的原因，github上获取代码非常缓慢，而且没啥用，所以去掉即可，我已经做好标注。建议大家看一下github上面的README.md，这样每一句命令是干什么的也很清楚了。

   ```bash
   set nocompatible              
   filetype off                  
   
   " 加入Vundle插件的路径
   set rtp+=~/.vim/bundle/Vundle.vim
   call vundle#begin()
   
   Plugin 'VundleVim/Vundle.vim' "这个必须要加
   
   Plugin 'tpope/vim-fugitive "可不加
   
   Plugin 'git://git.wincent.com/command-t.git' "可不加
   
   Plugin 'file:///home/gmarik/path/to/plugin' "可不加
   
   Plugin 'rstacruz/sparkup', {'rtp': 'vim/'} "可不加
   
   
   call vundle#end()            " required
   filetype plugin indent on    " required
   ```

3. 安装Vundle

   打开 Vim：

   ```bash
   vim
   ```

   然后键入下列命令安装插件： 

   ```bash
   :PluginInstall
   ```

   等几秒就会出现一个Done！你的界面变成了双编辑器，安装成功，退出就ok了。

