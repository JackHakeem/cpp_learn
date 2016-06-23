#include "MsgItem.h"
#include "KKLabelTTF.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

const float fontSize = 20.0f;
const float rowSize = 25.0f;

CMsgItem::CMsgItem()
{

}
CMsgItem::~CMsgItem()
{

}
bool CMsgItem::init(char* content, ccColor3B color)
{
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(ccp(0,0));

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(fontSize, rowSize, CCSizeMake(277, 26));

	//µÚNÂÖÕ½¶·
	{
		std::string showstr1 = "";
		showstr1 = content;

		kkttf->add(showstr1, color);
	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(277), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
	kkttf->release();

	return true;
}