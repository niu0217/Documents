# 和Github仓库建立连接

## SSH Key

**什么是SSH Key？**

SSH key：由于github的代码是开源的，每个人都可以查看代码，但是只有自己能够修改代码，那么github如何识别出提交是用户本人推送的呢？SSH Key就如同一把“钥匙”，只有这把钥匙才能够针对相应的代码进行操作。

**为何要设置SSH Key？**

机器本地Git仓库和GitHub仓库之间的传输，是通过SSH进行加密的，因此需要设置SSH Key。



## 1. git绑定用户

```shell
#GitHub相对应的帐号名称
git config --global user.name "niu0217"

#GitHbu相对应的邮箱帐号
git config --global user.email "1033856427@qq.com"
```



## 2. 本地创建SSH Key

查看有没有.ssh目录，查看.ssh目录下有没有id_rsa和id_rsa.pub文件，如果有，可直接跳到下一步。

如果没有，执行下述命令：

```shell
ssh-keygen -t rsa -C "email@XXX.com"
```

找到.ssh目录，里面有id_rsa和id_rsa.pub两个文件，这两个就是SSH Key的秘钥对，id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。



## 3. 在Github上设置SSH Key，从而建立“关系”

+  打开“Settings”
+ 选择“SSH and GPG Keys”
+  点击“New SSH Key”
+ 填上相应的Title（自己想填啥填啥），Key type选择Authentication key，在Key文本框里粘贴id_rsa.pub文件的内容
+ 点“Add Key”，你就应该看到已经添加的Key

GitHub允许添加多个Key。假定有若干电脑，只要把每台电脑的Key添加到GitHub，就可以在每台电脑上向GitHub上推送了。

测试是否连接成功：

```shell
#测试连接是否成功
ssh -T git@github.com

#PS:  You've successfully authenticated 表示连接成功
```





## 4. 建立Github仓库



## 5. 在本地和Github仓库建立连接

主电脑：

```shell
echo "# testtest" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin git@github.com:niu0217/Tiny.git
git push -u origin main
```

如果是另一台电脑的话：

```shell
git init
git remote add origin git@github.com:niu0217/Tiny.git
git pull git@github.com:niu0217/Tiny.git
git add .
git commit -m "first commit"
git branch -M main
git push -u origin main
```

