#pragma once
#include "cocos2d.h"
#include "model/mail/vo/MailHeadVo.h"

USING_NS_CC;

class MailItem : public CCLayer
{
public:
	MailItem(MailHeadVo headVo);
	virtual ~MailItem();
	bool isLenOverflow(std::string str , const int CNwordnum , int &nbyteCnt);

public:
	MailHeadVo _headVo;

protected:
private:
};