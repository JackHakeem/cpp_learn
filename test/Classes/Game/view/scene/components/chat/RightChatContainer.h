#ifndef _RIGHTCHATCONTAINER_H_ 
#define _RIGHTCHATCONTAINER_H_

#include "cocos2d.h"
#include "ChatContainer.h"

USING_NS_CC;

class RightChatContainer : public ChatContainer
{
public:
	RightChatContainer();
	virtual ~RightChatContainer();

	virtual bool init();
	void loadBackGround();
	void loadIcon(int id);
	void loadName(std::string szName);
	void loadContent(std::string szContent);
	virtual void showContent(struct _VOICE_* _voice);
public:
	//CCSprite * _pBack;

protected:
private:
};

#endif