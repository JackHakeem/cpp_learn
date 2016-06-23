#ifndef HLQS_AttributeLayer_H_
#define HLQS_AttributeLayer_H_
#include "LayerNode.h"

USING_NS_CC;

class AttributeLayer : public LayerNode
{
public:
	AttributeLayer();
	AttributeLayer(CCSize &size);
	bool init();
public:
	void loadItems();
	void clickButtonBag(CCObject * pSender);
	void clickButtonReborn(CCObject * pSender);
	void onClickButtonRebornTips(CCObject * pSender);
	void clickButtonDismiss(CCObject * pSender);
	void shureToDismiss(CCObject* obj);
	void cancelToDismiss( CCObject* obj );
public:
	enum
	{
		Z_ITEM = 0
	};
	enum
	{
		TAG_BUTTON = 0,
		TAG_STRING = 10,
		TAG_VALUE = 100,
		TAG_VALUE_BG = 200
	};
	CCSize _layerSize;
};

#endif