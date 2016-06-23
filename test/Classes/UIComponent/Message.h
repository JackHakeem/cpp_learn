#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "cocos2d.h"
#include "utils/Singleton.h"
#include "MessageItem.h"
using namespace cocos2d;

class Message : public CCObject, public Singleton<Message>
{
public:
	Message();
	~Message();

public:
	void layout();
	void show( string msg, ccColor3B color = ccc3(0, 255, 0), int delay = 3 );
	void loadingCallBack( CCObject* obj );

	int NumberOfSprites() const { return m_nNumberOfSprites; }
	void NumberOfSprites(int val) { m_nNumberOfSprites = val; }
	int NumberOfLoadedSprites() const { return m_nNumberOfLoadedSprites; }
	void NumberOfLoadedSprites(int val) { m_nNumberOfLoadedSprites = val; }

	CCMutableArray<MessageItem*> _msgList;
private:
	int m_nNumberOfSprites;
	int m_nNumberOfLoadedSprites;
	//vector<std::string> _msgList;
	//cocos2d::CCLabelTTF* _msgContainer;

	CCLayer* _msgContainer;

};

#endif