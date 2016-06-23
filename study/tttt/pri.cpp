#include <iostream>

using namespace std;

class Printer{
    public:
        Printer(std::string name) {std::cout << name;}
};
class Container{
    public:
        Container() : b("b"), a("a") {}
    Printer a;
    Printer b;
};
int main(){
    Container c;
    return 0;
}

