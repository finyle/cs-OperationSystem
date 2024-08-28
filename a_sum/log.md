## 1. 下载 qemu for windows
## 2. 下载 xv6 source， 并修改源码：
### 定位到xv6目录下的kernel.ld的
```
.stab:{ 修改成
.stab : AT(LOADADDR(.rodata) + SIZEOF(.rodata)){
```
## 3. wsl 编译 makefile： make & make xv6memfs, 复制*.img 文件到windows中(clone for windows, make 命令查找不到)

## 4.  运行qemu： 注意路径配置：
### qemu-system-i386 -m 512 -drive file=C:\Users\linsh\Desktop\fs.img,index=1,media=disk,format=raw -drive file=C:\Users\linsh\Desktop\xv6.img,index=0,media=disk,format=raw