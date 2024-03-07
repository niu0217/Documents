# mac上完整卸载MySQL

参考网址：https://juejin.cn/post/7068970449509548046



首先我们来看下mysql是否在启动，需要关闭mysql。

```bash
ps -ef|grep mysqld
```

然后执行如下命令：

```bash
brew uninstall mysql

sudo rm /usr/local/mysql  

sudo rm -rf /usr/local/mysql* 

sudo rm -rf /Library/StartupItems/MySQLCOM  

sudo rm -rf /Library/PreferencePanes/My* 

rm -rf ~/Library/PreferencePanes/My*  

sudo rm -rf /Library/Receipts/mysql*  

sudo rm -rf /Library/Receipts/MySQL*  

sudo rm -rf /var/db/receipts/com.mysql.* 

sudo rm -rf /usr/local/Cellar/mysql

sudo rm -rf /usr/local/var/mysql

sudo rm -rf /tmp/mysql*

brew cleanup
```

找不到的文件夹不用管。这样就完全卸载了。

