# GDB实战

## 1. 查看一个未定义的符号在哪个文件中定义

先查看未定义的符号：

```bash
ubuntu@niu0217:~/GithubFile/MallocLib/Dev/version2/malloclab-handout-TWO$ nm -u mdriver.o
         U __assert_fail
         U calloc
         U __errno_location
         U exit
         U fclose
         U fopen
         U free
         U fsecs
         U fwrite
         U getopt
         U _GLOBAL_OFFSET_TABLE_
         U init_fsecs
         U __isoc99_fscanf
         U malloc
         U mem_heap_hi
         U mem_heap_lo
         U mem_heapsize
         U mem_init
         U mem_reset_brk
         U memset
         U mm_free
         U mm_init
         U mm_malloc
         U mm_realloc
         U optarg
         U printf
         U putchar
         U puts
         U realloc
         U sprintf
         U __stack_chk_fail_local
         U stderr
         U strcat
         U strcpy
         U strdup
         U strerror
         U strlen
         U team
```

我们选择team来进行实验。这是一个在mdriver.o中未定义的符号，我们需要查找它在哪个文件中定义的。

```bash
ubuntu@niu0217:~/GithubFile/MallocLib/Dev/version2/malloclab-handout-TWO$ nm -gA *.o | grep 'team'
mdriver.o:         U team
mm.o:00000000 D team
ubuntu@niu0217:~/GithubFile/MallocLib/Dev/version2/malloclab-handout-TWO$
```

从这里我们看出来它在mm.o中模块中定义的。