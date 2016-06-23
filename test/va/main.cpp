#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#include <vadefs.h>

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

void arg_test(int i, ...);

bool printargs(const char *fmt,...);

int main(int argc, char *argv[])
{
    int int_size = _INTSIZEOF(int);
    printf("int_size=%d\n", int_size);

    arg_test(0, 4);
    
    printargs("hello %s and %s", "jack", "shantina");

    return 0;

}


void arg_test(int i, ...)
{
    int j = 0;
    va_list arg_ptr;
    va_start(arg_ptr,i);

    printf("&i = %p\n",&i);//打印参数i在堆栈中的地址
    printf("arg_ptr = % p\n",arg_ptr);

    //打印va_start之后arg_ptr地址,
    //应该比参数i的地址高sizeof(int)个字节
    //这时arg_ptr指向下一个参数的地址
      
    j=*((int *)arg_ptr);
    printf("%d %d\n", i, j); 
    j=va_arg(arg_ptr, int); 
    printf("arg_ptr = %p\n", arg_ptr);
    //打印va_arg后arg_ptr的地址
    //应该比调用va_arg前高sizeof(int)个字节
    //这时arg_ptr指向下一个参数的地址
    va_end(arg_ptr); 
    printf("%d %d\n", i, j); 

}

bool printargs(const char *fmt,...)
{
    const char *c = fmt;
    va_list ap;
    va_start(ap,fmt);
    char **str;
    int argc = 0;
    while(*c != '\0') {
        if (*c != '%' || c[1] == '\0') {
            str = realloc(str, sizeof(char*)*(++argc));
            str[argc-1] = *c;
        }else{
            char *arg;
            size_t size;

            switch(c[1]) {
            case 's':
                arg = va_arg(ap,char*);
                size = strlen(arg);
                if(size>0)
                    str = realloc(str,sizeof(char*)*(argc+len));
                    memcpy(str+argc,arg,size);
                    argc += len;
                c++;
                break;
            //case 'd':
                //int j = va_arg(ap,int);
                
            }
        }
        c++;
    }

    printf("%s", str);

    return true;
}
















