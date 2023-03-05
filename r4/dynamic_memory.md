---
marp: true
math: mathjax
---

# 动态内存

---
## 为啥需要动态内存  
- 栈区或者静态变量区内存不够大  
- 有些空间仅能通过运行时确定，且变化范围较大
- 一些大块内存尽在程序的一部分使用  
...

---

## 常用函数
- 头文件 <stdlib.h>
- 分配空间三巨头 malloc,calloc,realloc  
- 释放空间 free

---

## 如何使用  
- [malloc : 分配空间(未经初始化)](https://en.cppreference.com/w/cpp/memory/c/malloc)
```
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    //allocate 10 bytes memory
    char *str_p = (char *)malloc(sizeof(char) * 10);
    //have a look at what are they
    for(int i = 0 ; i < 10 ; printf("The ASCII of %d-th number is %d\n", i, str_p[i]), i++);
    //think of why I don't write printf("The ASCII of %d-th number is %d\n", i, str_p[i++])
    printf("\n----------------\n");
    //set some value to them
    memset(str_p, 'a', sizeof(char) * 10);
    //have a look at what are they
    for(int i = 0 ; i < 10 ; printf("The %d-th element is %c\n", i, str_p[i]), i++);
    //don't forget free the memory you allocate
    free(str_p);
    return 0;
}
```

---

## 如何使用
- 运行结果:
```
The ASCII of 0-th number is 13
The ASCII of 1-th number is -16
The ASCII of 2-th number is -83
The ASCII of 3-th number is -70
The ASCII of 4-th number is 13
The ASCII of 5-th number is -16
The ASCII of 6-th number is -83
The ASCII of 7-th number is -70
The ASCII of 8-th number is -32
The ASCII of 9-th number is 98

----------------
The 0-th element is a
The 1-th element is a
The 2-th element is a
The 3-th element is a
The 4-th element is a
The 5-th element is a
The 6-th element is a
The 7-th element is a
The 8-th element is a
The 9-th element is a
```

---

## 如何使用
- [calloc : 分配内存(全部初始化为0)](https://en.cppreference.com/w/cpp/memory/c/calloc)
```
#include <stdio.h>
#include <stdlib.h>
int main() {
    //allocate 40bytes memory
    int * arr_p = (int *)calloc(10, sizeof(int));
    //have a look at what are they
    for(int i = 0 ; i < 10 ; printf("The %d-th element is %d\n", i, arr_p[i]), i++);
    //don't forget free
    free(arr_p);
    return 0;
}
```

---

## 如何使用
- 运行结果:
```
The 0-th element is 0
The 1-th element is 0
The 2-th element is 0
The 3-th element is 0
The 4-th element is 0
The 5-th element is 0
The 6-th element is 0
The 7-th element is 0
The 8-th element is 0
The 9-th element is 0
```
---

## 如何使用
- [realloc : 重新分配内存](https://en.cppreference.com/w/cpp/memory/c/realloc)  
- 如果指定的大小比原来的大小要小，那些元素会被复制?
- 如果指定的大小比原来的要大，那么新分配内存的最后一些元素会是什么呢?
- 如何释放realloc的内存

---

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char * str1 = (char*)malloc(sizeof(char) * 10);
    memset(str1, 'a', sizeof(char) * 10);
    char * str2 = realloc(str1, 5);
    for(int i = 0 ; i < 5 ; printf("The %d-th char is %c\n", i, str2[i]), i++);
    char * str3 = realloc(str1, 15);
    printf("\n-----------\n");
    for(int i = 0 ; i < 15 ; printf("The %d-th char is %c", i, str3[i]), i++);
    //Here are some possible ways to free the memory, which is(are) true?
    //(1)free(str1); free(str2); free(str3)
    //(2) free only one of {str1, str2, str3}
    //(3) writting like this is not rigorous, we should writting like p1 = realloc(p1, new capacity)
    return 0;
}
```

---

### 实际上realloc重新分配有三种情况
1. 在原先分配的内存后扩展或收缩,返回原指针  
2. 自动free原指针指向的空间,重新分配一块内存,返回新指针  
3. 如果原内存后面既没有足够大的空间,其他地方又没有足够大的空间,会返回空指针，但平不会free掉原指针指向的空间
- 结合以上三点,我个人的意见是这样写

```
int *tmp = NULL;
int *p = (int *)malloc(sizeof(int) * 100);
tmp = (int *)realloc(p, sizeof(int) * 2000);
if(tmp != NULL) 
    p = tmp;
else 
    //raise some error(don't have enough space)
```