*********************************************************************

lab1
1. rom bios: gdb si(步进)查看 bios加载
2. boot loader: 
   3. 在0x7c00 (boot sector的加载地址)打断点，trace boot.S; 比较boot/boot.S和obj/boot/boot.S的区别
   4. trace main.c 中的bootmain(), 查看每次redsect的地址是否相同
   load kernel: 
      5. 理解 c 中的pointer
      6. 修改boot/Makefrag 中的link address(0x7c00)，重新编译，查看错误
      7. gdb x(x/Nx ADDR) 打印在addr的n个单词的内存地址；重启机器,在0x00100000处检测8个单词;再查看bootloader 加载 kernel的地址 是否相同
3. 在 kern/entry.S 中的 movl %eax, %cr0 处打断点
   4. 找到在obj/kern/kernel.asm中的test_backtrace()函数，断点调试
   5. debuginfo_eip 中的 __STAB_*来自 kern/kernel.ld 中的 __STAB_*

*********************************************************************

lab2 (内存管理: 两部分(kernel使用物理内存分配器实现内存的分配回收，维护数据结构记录那些内存被回收，分配，共享))
相关文件(inc/memlayout.h; kern/pmap.c & pmap.h & kclock.h & kclock.c), 特别注意 memlayout.h & pmap.h || inc/mmu.h
1. physical mem: 实现kern/pmap.c 中的5个函数： boot_alloc, mem_init, page_init, page_alloc, page_free 
2. virtual mem: gdb 只允许通过虚拟地址访问qemu的内存； qemu monitor命令 xp 可以 inspect 物理地址; 在启动qemu的cmd中ctrl-a c && xp, 在gdb中键入x
   3. page table 页表管理： 实现kern/pmap.c 中的5个函数： pgdir_walk(), boot_map_region(), page_lookup(), page_remove(), page_insert()
4. kernel address space： 完成 kern/pmap.c 中mem_init()在调用完 check_page()后的内容

*********************************************************************

lab3 (创建受保护的用户进程空间，增强kernel用以跟踪用户进程，创建于给单独的用户进程，向其中加载如一个程序镜像并启动 & 内核处理来自进程的系统调用并捕获任何由它造成的异常)
相关文件：
inc/ evn.h          进程结构定义
     trap.h         trap
     syscall.h      进程至kernel的系统调用    
     lib.h          进程 support lib
kern/ evn           kernel中的进程结构定义
      trap          trap
      syscall       kernel私有的系统调用
      trapentry.S   entry-point 控制trap的汇编
lib/  Makefrag       构建进程库的makefile参数   
      entry.S        进程的汇编 entry-point
      libmain.c      entry.S的启动入口
      syscall        进程的panic实现
      console        进程的console实现 putchar, getchar
      exit           进程的exit实现   
      panic          进程的panic实现
user/ *
进程与异常捕获
1. 修改kern/pmap.c中的mem_init() 
2. 完成kern/env.c 中的6个函数： env_init, env_setup_vm, region_alloc, load_icode, env_create, env_run 
3. 修改 trapentry.S 和 trap.c 实现trap

page fault, breakpoint exceptions and syscall
4. 修改 trap_dispatch() 
5. 编辑 kern/trapentry.S, kern/trap.c 处理内核中的异常 
6. 修改 lib/libmain.c和 lib/exit.c 让其在破坏进程时被kernel监控到
7. 修改 kern/trap.c syscall.c

*********************************************************************

lab4 (多进程支持3部分：
    a.round-robin调度算法,添加基础的系统调用(创建销毁进程，分配映射内存);)
    b.实现类unix风格的fork 允许进程复制
    c.实现进程进间通信(实现同步)
相关文件: 
kern/cpu                kernel 多进程支持的私有定义
     mpconfig           多进程相关配置
     lapic              每个核中驱动本地APIC
     mpentry.S          non-boots CPU 汇编entry
     spinlock           kernel 自旋锁实现
     sched              调度实现
1. 实现 kern/pmap.c 中的mmio_map_region 函数： 
2. 理解 kern/init.c 中的boot_aps, mp_main 和 kern/mpentry.S, 启动应用进程时的控制流
3. 修改kern/pmap.c 中的mem_init_map函数 映射每个在KSTACKTOP开始的cpu 栈
4. kern/trap 中的trap_init_percpu 初始化TSS描述符
5. 完成 kern/spinlock 并正确调用 lock_kernel && unlock_kernel 
6. 实现kern/sche 中的sched_yield函数,即 round-robin调度

7. 实现kern/syscall 系统调用，user/dumbfork 正确执行
8. 实现系统调用： sys_env_set_pagefualt_upcall 
9. 实现kern/trap 中的 page_fault_handelr 分发 pagefault 到 进程handler
10. 实现 lib/pfentry.S 中的_pgfault_upcall： 模拟切换栈和重载 EIP
11. 实现 lib/fork 中的 fork, dupage

12. 修改 kern/trapentry.S和kern/trap 初始化IDT entry
13. 修改 kern 的trap_dispatch 函数，发生时钟中断时调用 sched_yield找到
14. 实现 kern/syscall 中的sys_ipc_recv和sys_ipc_try_send 实现ipc通信中消息收发

*********************************************************************

lab5 (实现 spawn： 加载并运行磁盘上的可执行文件(简易的读写文件系统))
相关文件：
fs/fs           描述磁盘结构的文件系统封装
    bc          block cache
    ide         最小ide驱动
    serv        文件系统服务器(通过ipc与用户环境交互)
lib/fd          类unix的文件描述符接口
    file        磁盘文件类型驱动(作为文件系统ipc客户端实现)
    console     console 中输入输出的文件类型
    spawn       
1. 修改 env 中的 env_create函数，确保文件系统的io权限
2. 实现 fs/bc 中的bc_pgfault和flush_block函数
3. 实现 fs/fs 中的 alloc_block ，以free_block作model
4. 实现 file_block_walk 和file_get_block 
5. 实现 fs/serv中的serve_read 函数
6. 实现新 sys_call: sys_env_set_trapframe  spawn依赖
7. 实现 lib/fork 中的duppage 
8. 在 kern/trap中的调用 kdb_intr 处理中断 IRO_OFFSET+IRQ_KBD
9. shell 通过操作符 < 实现 io重定向

*********************************************************************

lab6 (实现网卡驱动 基于intel82540e芯片(E1000)) 网卡驱动还不足以使jos连接到网络,net中提供了简易的网络协议栈和网络服务器
驱动外的3部分：1. 创建新的系统调用handle驱动; 2. 完成网络服务器中处理网络栈和驱动间transfer packets的功能;3. 整合所有部分实现web服务器(可处理来自文件系统的文件)

1. 实现kern/syscall 系统调用 sys_time_msec, 实现attach func
2. 实现kern/pci 中初始化 e1000
3. 在attach_func中为e1000的bar 调用 mmio_map_region 创建虚拟内存映射
4. 通过检测下一个描述符是否free的形式实现 数据包的传输
5. 添加系统调用传输来自 user space的数据包

6. 实现 net/output
7. 实现函数 接收来自 e1000的数据包 并同通过添加系统调用的方式将其发送到user sapce
8. 实现 net/input
9. 实现 user/httpd 中的 send_file & send_data