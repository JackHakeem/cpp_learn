#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;


bool GetUserData(const string& strval, const string& field, string& val)
{
    int index = strval.find(field.c_str(), 0);
    if(index == -1)
    {
        val = "";
        return false;
    }
    int keyendindex = strval.find(',', index);
    int keymidindex = strval.find(':', index);
    val = strval.substr(keymidindex+1, keyendindex-keymidindex-1);
    return true;
}



int GET_STRING(const string& src, const string& key, string& val)
{
	//empty
	if (src.empty())
	{
		return -1;
	}
	string::size_type p=0, e=0;
	string::size_type len = src.length();
	string::size_type kl = key.length();

	for (size_t i=0; i<len; ++i)
	{
		p = src.find(key,i);
		if ( p == string::npos )
		{//not found
			return -1;
		}
		if ( p!=0 && src[p-1]!=',' )
		{//not found,continue;
			i=p;
			continue;
		}
		if ( src[p+kl]!=':')
		{//not found,continue;
			i=p;
			continue;
		}
		//found
		e = src.find(",",p);
		if ( e == string::npos )
			e = len;

		val = src.substr(p+kl+1, e-p-kl-1);

		return 0;
	}
	//此代码只有代码有错才会跑到这里
	//LOG_ERROR_EX("IChat_DBClass GET err <%s>, <%s>", src.c_str(), key.c_str());
	printf("error\n");
	return -1;
}

int main(int argc, char** argv)
{
	string vv = "3key:10,2key:20,key:50";
	vv.assign(argv[1]);
	
	string v;
	GET_STRING(vv, argv[2], v);
	printf("%s\n", v.c_str());
	return 0;
}


