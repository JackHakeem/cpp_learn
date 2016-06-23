#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

bool parse(const char* sessid, long long &uid1, long long &uid2)
{
    static char sz[128]={0};
    memcpy(sz, sessid, strlen(sessid) );
    char* p = strtok(sz, "_");
    uid1=atoll(p);
    return true;
}

int main()
{
    char s[]="ab-cd:ef-5";
    
    //string s = "ab-cd:ef-5";
    char* delim="-:";
    char*p;
    printf("%s\n", strtok(s,delim));
    while( (p=strtok(NULL,delim) ) )
        printf("%s\n",p);
    
    long long u1, u2;
    parse("188_90900",u1, u2);
    printf("%lld\n", u1);
    
    return 0;
}
