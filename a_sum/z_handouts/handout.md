# lab1: C, Assembly, Tools, Bootstrapping
```
* pc bootstrap: x86 assembly, stimulating x86, pc's physical address space, rom bios
* boot loader: boot/boot.S, GDB command
* kernel: format printing to consle, stack(backtrace c在内核空间的栈上执行)
```
## hw1 Boot xv6
## hw2 shell

# lab2: Memory management
```
* physical page management (物理页管理 kern/pmap.c: page_alloc & free) 自定义数据结构记录内存页的使用，分配情况
* virtual memory (虚拟线性物理地址， 引用计数， 页表管理)
* kernel address space (内核地址空间：访问权限与失败隔离(地址空间的可读权限)；初始化内核地址空间; address space layout(可用地址空间查询))
```
## hw3 system calls
## hw4 lazy page allocation
## hw5 xv6 CPU alarm

# lab3: User-Level Environment(process)
```
* user environment(process) and exception handling (内核创建数据结构：track进程，创建，载入程序镜像并执行; 内核响应进程中的系统调用并处理相关异常) 
* page fault(页错误相关虚拟地址), breadkpoint exception(内核对程序断点的响应), system call(用户进程通过系统调用操作内核行为)
```
## hw6 multithreaded programming
## hw7 xv6 locks

# lab4: Preemptive Multitasking
```
* multiproessing(多进程支持： 进程管理相关的系统调用：round-robin(调度算法), 进程的创建销毁；内存的分配回收 
* copy-on-write fork(进程的自我拷贝)
* IPC(inter processs communcation) 进程间通信(多种模式：message send & recv | transfer page)
```
## hw8 uthreads
## hw9 barrier

# lab5: File system, spawn and shell
```
* spawn: (加载运行磁盘上的可执行文件的库)支持简单读写的文件系统
* on-disk file system structure: (sectors and blocks, superblocks, file-metadata)
* fs: (disk access, block cache, block bitmap, file operation,interface, file descriptors(基于fork和spawn共享文件描述符的状态))
* shell 
```
## hw10 big files
## hw11 crash
## hw12 mmap()

# lab6: Networking
```
* qemu's virtual net (基于qemu的仿真网络环境(对E1000的仿真器))
* network environment(serve, input, output, os中的网络进程 lib/nsipc, socket)
* net interface card(网卡硬件驱动(E1000): PCI(pci设备可以与cpu直接通信，实现内存的读写；MMIO(虚拟内存映射) DMA(direct memory access)
* transmitting packets: （网络传输包结构， 服务器包结构， tcpdump, wireshark)
```

