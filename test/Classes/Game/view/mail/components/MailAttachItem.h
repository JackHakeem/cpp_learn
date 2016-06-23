#pragma once
#include "cocos2d.h"
#include "model/mail/vo/MailContentVo.h"

USING_NS_CC;

class MailAttachItem : public CCLayer
{
public:
	MailAttachItem(MailContentVo contentVo);
	virtual ~MailAttachItem();

	void setItem(MailContentVo contentVo);
	void onGetAttach(CCObject * pSender);

public:
	MailContentVo _contentVo;
	enum
	{
		TAG_Grid = 0,
		TAG_ItemImage,
		TAG_Text,
	};
protected:
private:
};