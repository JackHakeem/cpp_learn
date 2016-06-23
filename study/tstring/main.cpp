#include <string>
#include <sstream>
#include <map>

using namespace std;

void _UpsertString(string& dest, const string& src, const string& s)
{
	string stmp(src);
	stmp += ":";
	string::size_type p, e;

	//empty
	if (dest.empty())
	{
		dest = s;
		return;
	}

	string::size_type len = dest.length();

	for (size_t i=0; i<len; ++i)
	{
		p = dest.find(stmp,i);
		if ( p == string::npos )
		{//not found
			dest = dest + "," + s;
			return;
		}
		if ( p!=0 && dest[p-1]!=',' )
		{//not found,continue;
			i=p;
			continue;
		}
		//found
		e = dest.find(",",p);
		if ( e == string::npos )
			e = len;

		dest.replace(p, e-p, s);

		break;
	}
}

void UpsertString(string& dest, const string& src, const string& i)
{
	string s;
	{
		stringstream ss;
		ss << src << ":" << i;
		s = ss.str();
	}

	_UpsertString(dest, src, s);
}

//存在则替换，不存在追加
void UpsertString(string& dest, const string& src, int32_t i)
{
	string s;
	{
		stringstream ss;
		ss << src << ":" << i;
		s = ss.str();
	}

	_UpsertString(dest, src, s);
	
}

void UpsertString(string& dest, const string& src, int64_t i)
{
	string s;
	{
		stringstream ss;
		ss << src << ":" << i;
		s = ss.str();
	}

	_UpsertString(dest, src, s);
}
template<class T>
void AppendString(string& dest, const string& src, T i)
{
	UpsertString(dest, src, i);

}

map<string, int> g_keyword;
bool iskeyword(const string& s)
{
	map<string, int>::iterator iter = g_keyword.find(s);
	return iter != g_keyword.end();
}

int main()
{
	g_keyword["cas"]=1;
	g_keyword["mid"]=1;
	g_keyword["_id"]=1;
	
	string sss = "_idi";
	const char* p = "i_id";
	if (! iskeyword(p) )
		printf("no no no!!!!\n");

	string s = "123456789abc";
	
	if ( s[1] == 'e' )
		printf("s[1]=='e'");
	
	printf("s[2]=%c\n", s[2]);
	string::size_type len = s.length();

	printf("len=%d\n", len);

	for ( size_t i=0; i<10; i++)
	{
		printf("%c", s[i]);
		if (s[i] == '4')
			i=6;
		
	}


	printf("\n\r");


	stringstream ss;

	ss << "i am " << 123;

	printf("%s\n",ss.str().c_str());

	ss << "i am " << 456;

	printf("%s\n",ss.str().c_str());


	{
		
		string s = "mid:19,cas:22,nn:8,kk:9";
		printf("%s\n", s.c_str());
		AppendString(s, "mm", 20);
		
		printf("%s\n", s.c_str());
		AppendString(s, "mm", 99);
		printf("%s\n", s.c_str());  
		AppendString(s, "mid", 30);

		printf("%s\n", s.c_str());

		AppendString(s, "cas", 23);

		printf("%s\n", s.c_str());

		AppendString(s, "as", 333);
		printf("%s\n", s.c_str());
		AppendString(s, "s", 888);
		printf("%s\n", s.c_str());

		AppendString(s, "id", 888);
		printf("%s\n", s.c_str());
		int64_t n=0xFFFFFFFFFFFFFFF;

		AppendString(s, "id", n);
		 printf("%s\n", s.c_str());

		int32_t i = 1<<30-1;
		AppendString(s, "id", i);

		 printf("%s\n", s.c_str());

		string ss = "hello";
		AppendString(s, "id", ss);

		 printf("%s\n", s.c_str());

	}



	return 0;
}



