#ifndef _LEFTCHATCONTAINER_H_ 
#define _LEFTCHATCONTAINER_H_

#include "cocos2d.h"
#include "ChatContainer.h"

USING_NS_CC;

class LeftChatContainer : public ChatContainer
{
public:
	LeftChatContainer();
	virtual ~LeftChatContainer();

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