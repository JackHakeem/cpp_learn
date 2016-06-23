#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_
#include "BaseType.h"
#include "utils/Singleton.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <unordered_map>
#define MAP_STRING_STRING std::unordered_map<std::string ,std::string>
#define MAP_STRING_COLOR3B std::unordered_map<std::string , ccColor3B>
#else
#include <tr1/unordered_map>
#define MAP_STRING_STRING std::tr1::unordered_map<std::string ,std::string>
#define MAP_STRING_COLOR3B std::tr1::unordered_map<std::string , ccColor3B>
#endif

class ValuesUtil : public Singleton<ValuesUtil>
{
public:
	void init();
	std::string getString(std::string key);
	ccColor3B getColor( std::string key );
private:
	void initStrings();
	MAP_STRING_STRING _StringsMap;
	MAP_STRING_COLOR3B _ColorMap;
};
#endif