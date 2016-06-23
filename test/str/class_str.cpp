

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;



static int sint = 45123;

int ssint = 6789;




class Indx
{
public:
    Indx(int i, int j)
    {
        int nTimestamp = time(NULL);
        sz.append( (char*)&i, sizeof(i) );    
        sz.append( "---", 3);
        sz.append( (char*)&j, sizeof(j) );
        sz.append( "###", 3);
        sz.append( (char*)&nTimestamp, sizeof(nTimestamp) );
    }
    void p()
    {
        cout << "Indx:" << sz << endl;
    }
public:
    string sz;
};






int main (int argc, char** argv)
{
    string sz;
    int gid = 987;
    int uid = 456;

    cout << "gid sizeof is " << sizeof(gid) << endl;


    sz.append( (char*)&sint, sizeof(sint) );   
    sz.append("abc", 3);
    sz.append( (char*)&gid, sizeof(gid) );

    cout <<"sz:"<< sz <<endl;

    sz.append( (char*)&uid, sizeof(uid) );
    
    sz.append( (char*)&ssint, sizeof(ssint) );
    
    cout << sz << endl;
    printf("p sz:%s\n", sz.c_str());
    
    Indx in(87, 6);
    in.p();
    return 0;
}

