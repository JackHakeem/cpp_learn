
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>


using namespace std;

int main(int argc, char** argv)
{
    const char* str = "192.168.202.127:8088";
    const char* p = strstr(str, ":");
    int port = atoi(p+1);
    //*p = '\0';
    printf("%s, %d\n", str, port);
    string ip;
    ip.assign(str, p);

    printf("ip:%s", ip.c_str());
    return 0;
}
