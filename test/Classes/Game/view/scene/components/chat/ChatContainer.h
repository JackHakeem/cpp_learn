#ifndef _CHATCONTAINER_H_ 
#define _CHATCONTAINER_H_

#include "cocos2d.h"

USING_NS_CC;

struct _VOICE_;
class ChatContainer : public CCLayer
{
public:
	ChatContainer();
	virtual ~ChatContainer();

	bool init();
	virtual void loadBackGround();
	virtual void showContent(struct _VOICE_* _voice);
	virtual void dispose();

public:
	enum
	{
		TAG_BG = 0,
		TAG_ICON,
		TAG_NAME,
		TAG_CONTENT,
	};

	enum
	{
		Z_BG = 0,
		Z_ICON,
		Z_NAME = Z_ICON,
		Z_CONTENT = Z_NAME,
	};

protected:
private:
};

#endif