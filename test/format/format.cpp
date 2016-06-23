#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const char* format_key(const char* format, ...)__attribute__((format(printf,1,2)));

int main(int argc, char **argv)
{

	cout << "the key " << format_key("%d_%d", atoi(argv[1]), atoi(argv[2])) << endl;
	return 0;
}

const char* format_key(const char* format,...)
{
	static char the_key[128]={0};
	va_list ap;
	va_start(ap, format);
	vsnprintf(the_key, sizeof(the_key), format, ap);
	va_end(ap);
	return the_key;
}	
