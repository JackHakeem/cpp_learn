#ifndef _DIALOGUTIL_H_
#define _DIALOGUTIL_H_

#include "cocos2d.h"

using namespace cocos2d;

class DialogUtil
{
public:
	DialogUtil();
	~DialogUtil();

public:
	static std::string replaceContentWithName(std::string content, ccColor3B color);
	static std::string colorRoleName(ccColor3B &color);
	static std::string replaceColor(std::string content);
};

#endif