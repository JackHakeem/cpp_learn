#include <string>
#include <stdio.h>

using namespace std;



string& Rtrim(string& s)
{
	int (*func)(int) = isspace;

	string::reverse_iterator iter;
	iter = find_if(s.rbegin(), s.rend(), not1(ptr_fun(func)));
	s.erase(iter.base(), s.end());

	return s;
}



int main()
{
	string s = "abcdddd\r    \n";
	string s2 = Rtrim(s);
	printf("[%s]\n", s2.c_str());
	return 0;
}




