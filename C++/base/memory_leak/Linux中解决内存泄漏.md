# Linux中解决内存泄漏

##  单个文件的C内存泄漏

```c
//test.c

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

bool memleakEnable = false;

void* _malloc(size_t size, const char* filename, int line) {
    void* ptr = malloc(size);
    if(memleakEnable) {
        char buff[64] = { 0 };
        snprintf(buff, 64, "./mem/%p", ptr);

        FILE* fp = fopen(buff, "w");
        fprintf(fp, "[+] mem_addr: %p, filename: %s, line: %d\n", ptr, filename, line);
        fflush(fp);
        fclose(fp);
    }
    return ptr;
}

void _free(void* ptr, const char* filename, int line) {
    if(memleakEnable) {
        char buff[64] = { 0 };
        snprintf(buff, 64, "./mem/%p", ptr);
        if(unlink(buff) < 0) {
            printf("double free\n");
            return;
        }
    }
    free(ptr);
}

#define malloc(size) _malloc(size, __FILE__, __LINE__);
#define free(ptr) _free(ptr, __FILE__, __LINE__);

int main(int argc, char* argv[])
{
    if(argc > 1) {
        memleakEnable = true;
    }
    void* p1 = malloc(5);
    void* p2 = malloc(10);
    void* p3 = malloc(15);

    free(p1);
    free(p2);
}
```

注意点：自己在当前目录建一个`mem`的文件夹。然后执行的时候：

```bash
./test [想填什么填什么]
```

比如：

```bash
./test -memleak
```

## 采用公司的成熟的日志

## dmalloc

常见的内存泄漏检测工具：https://blog.csdn.net/gatieme/article/details/51959654

dmalloc的官网：https://dmalloc.com/

参考网站：

+ 使用方法：https://www.cnblogs.com/wangkangluo1/archive/2012/06/05/2535509.html

