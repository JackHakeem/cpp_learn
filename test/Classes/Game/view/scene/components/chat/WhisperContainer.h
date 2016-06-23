#ifndef _WHISPERCONTAINER_H_ 
#define _WHISPERCONTAINER_H_

#include "cocos2d.h"
#include "ChatContainer.h"

USING_NS_CC;

class WhisperContainer : public ChatContainer
{
public:
	WhisperContainer();
	virtual ~WhisperContainer();

	virtual void loadBackGround();
	void loadContent(std::string szContent);
	virtual void showContent(struct _VOICE_* _voice);
protected:
private:
};

#endif