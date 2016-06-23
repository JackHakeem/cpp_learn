#include "memcheck.h"
#include "log.h"
#include "stdio.h"

class Father
{
public:
	Father() { printf("father __ctor__\n"); }

	~Father() { printf("father __dtor__\n"); }

};




int main()
{
	init_log("main", "./log/", 2, 1024*1024);
	set_log_level(7);
	Father* f;
	NEW(Father, f);

	DELETE(f);
	return 0;
}


