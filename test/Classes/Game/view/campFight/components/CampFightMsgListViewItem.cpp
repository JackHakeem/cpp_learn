#include "CampFightMsgListViewItem.h"
#include "KKLabelTTF.h"
#include "utils/ScaleUtil.h"

const float fontSize = 20.0f;
const float rowSize = 25.0f;

CampFightMsgListViewItem::CampFightMsgListViewItem()
{

}
CampFightMsgListViewItem::~CampFightMsgListViewItem()
{

}
CampFightMsgListViewItem* CampFightMsgListViewItem::itemStrFactory(
						          char* content, ccColor3B color , 
								  float width,float size)
{
	CampFightMsgListViewItem* node = new CampFightMsgListViewItem();
	node->init(content,color,width,size);

	return node;
}

bool CampFightMsgListViewItem::init(char* content, ccColor3B color , 
									float width, float size)
{
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);

	KKLabelTTF* kkttf = new KKLabelTTF();
	kkttf->init(size, rowSize, CCSizeMake(/*400*/width, 20));

	//µÚNÂÖÕ½¶·
	{
		std::string showstr1 = "";
		showstr1 = content;

		kkttf->add(showstr1, color);
	}

	kkttf->setPosition(ccp(0, kkttf->m_iRow*kkttf->m_fFontRealHeight));
	this->addChild(kkttf, 1);
	this->setContentSize(CCSizeMake(POSX(860), kkttf->m_fFontRealHeight*(kkttf->m_iRow+1)));
	this->setvisibleSize(this->getContentSize());
	kkttf->release();

	return true;	
}