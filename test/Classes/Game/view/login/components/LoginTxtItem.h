#ifndef _LOGIN_TXT_ITEM_H_
#define _LOGIN_TXT_ITEM_H_

#include "cocos2d.h"
#include "LayerNode.h"

USING_NS_CC;

class LoginTxtItem : public CCLabelTTF
{
public:
	LoginTxtItem();
	~LoginTxtItem();
public:
	virtual bool init();
	static LoginTxtItem* ItemWithString( std::string msg, ccColor3B color = ccc3(0, 255, 0), int fontsize = 24 );
	void onTime( float dt );
};

#endif