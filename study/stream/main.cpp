#include <sstream>
#include <iostream>

using namespace std;



int test_sstream(int bug)
{
stringstream stream;

stream<<"abc";
int n;
stream>>n;//这里的n将保持未初始化时的随机值

cout << "n=" << n << endl;
if (bug < 2) {
//stream.clear();//清除错误标志
}
if (bug < 1) {
//stream.str("");//清除内容“abc”
}

if (bug == 0)
{
stream.clear();
stream.str("");
}

if (bug==1)
{
stream.clear();
}

if (bug==2)
{
stream.str("");
}

if (bug==3)
{

}

//缺少上面两句中的任何一句都无法使得后面的s==“def”
//相反，s将等于 “” 或 “abcedf”

stream << "def";
string s;
stream>>s;
cout << "BUG=" << bug << " DEF = " << s <<endl;

return 0;
}

int main()
{
test_sstream(0);
test_sstream(1);
test_sstream(2);
test_sstream(3);
return 0;
}




