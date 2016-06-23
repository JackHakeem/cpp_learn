#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;


class TS
{
public:
    TS()
    {
        printf("cotr\n");
    }
    ~TS()
    {
        printf("dtor\n");
    }

    int i;
    char* name;
};


int main(int argc, char** argv)
{

    string s = "hello world!";
    char fn[64];

    snprintf(fn, sizeof(fn), "%s", s.c_str());
    
    printf("%s\n", fn);
    
    int a = 12;
    TS* sz = new TS[a];
     
    for (int i=0; i<a; ++i)
    {
        TS* p = sz+i;
        p->i = i;
    }

    for (int i=0; i<a; ++i)
    {
        printf("i=%d ", (sz+i)->i);
    }
    printf("\n");

    delete[] sz;


    return 0;
}

