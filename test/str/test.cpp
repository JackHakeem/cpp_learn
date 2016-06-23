

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

static int sint = 45123;

int ssint = 6789;

int main (int argc, char** argv)
{
    string sz;
    int gid = 987;
    int uid = 456;
    sz.append( (char*)&sint, sizeof(sint) );   
    sz.append("abc", 3);
    sz.append( (char*)&gid, sizeof(gid) );

    cout <<"sz:"<< sz <<endl;

    sz.append( (char*)&uid, sizeof(uid) );
    
    sz.append( (char*)&ssint, sizeof(ssint) );
    
    cout << sz << endl;
    printf("p sz:%s\n", sz.c_str());
    
    
    return 0;
}

