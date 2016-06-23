#ifndef _NPCCHAT_H_
#define _NPCCHAT_H_

#include "cocos2d.h"
#include "chat/ChatContainer.h"

USING_NS_CC;

class LiveThing;

struct _VOICE_;

class NPCChat : public CCLayer
{
public:
	NPCChat(int disppearTime =1, int color = 16777215);
	~NPCChat();

	void hideDialog();
	void	showContent(struct _VOICE_ *voice);
	void whisper(std::string content);
	void talk(std::string content,std::string name, int id=33, int style=2);
	void dispose();
public:
	enum
	{
		Z_WHISCONTAIN = 0,
		Z_LEFTCONTAIN = Z_WHISCONTAIN,
		Z_RIGHTCONTAIN = Z_LEFTCONTAIN,
	};
	enum
	{
		TAG_WHISCONTAIN = 0,
		TAG_LEFTCONTAIN,
		TAG_RIGHTCONTAIN
	};

	/*ChatContainer * _whisperContainer; 
	ChatContainer * _leftChatContainer;
	ChatContainer * _rightChatContainer;*/

protected:
private:
};

#endif