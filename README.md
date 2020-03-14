# context_benchmark
some coroutines benchmark

## ucontext fcontext性能测试
1. 测试环境

```
Architecture: x86_64
CPU op-mode(s): 32-bit, 64-bit
Byte Order: Little Endian
CPU(s): 4
On-line CPU(s) list: 0-3
Thread(s) per core: 1
Core(s) per socket: 2
Socket(s): 2
NUMA node(s): 1
Vendor ID: GenuineIntel
CPU family: 6
Model: 158
Model name: Intel(R) Core(TM) i5-8500 CPU @ 3.00GHz
Stepping: 10
CPU MHz: 2999.995
BogoMIPS: 5999.99
Hypervisor vendor: VMware
Virtualization type: full
L1d cache: 32K
L1i cache: 32K
L2 cache: 256K
L3 cache: 9216K
NUMA node0 CPU(s): 0-3

gcc7.1.0 编译器优化-O2  开启jemalloc
```
2. 搭建

```
1. 测试ucontext切换:
切到scheduler分支 git reset --hard 871915ac 指向未实现scheduler之前
编译运行fiber_test.cc 最终ucontext切换消耗228ns
libtask 与 pdns底层压测均是ucontext 300+ns
或切到scheduler分支 把scheduler.cc中的 SYLAR_LOG_INFO(g_logger) << "idle fiber"; 注释掉
编译运行scheduler_test.cc  得到的ucontext切换消耗时间是183ns
2. 测试fcontext切换:
cherry-pick fcontext的commit:  git cherry-pick e4cfea88 同上编译运行scheduler_test.cc
30ns切换一次
3. 1/2测试的均是理想条件下即只有context切换 没有schduler调度 而在实际的scheduler框架中 
scheduler是fiber队列的消费者 需要不断的加锁解锁 遍历队列 删除队列 还有一系列判断等等
因此 会多消耗一些时间(大概50ns左右) 
测试用例为normal_test.cc编译运行  得到ucontext切换时间消耗250ns fcontext切换时间消耗90ns

```
