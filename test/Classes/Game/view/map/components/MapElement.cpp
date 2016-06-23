#include "MapElement.h"
#include "utils/ScaleUtil.h"

MapElement::MapElement()
{}

bool MapElement::createElement(int32 type, bool isRole, char* txt)
{
	if (!LayerNode::init())
		return false;
	char _iconStr[100];
	if (isRole)
	{
		sprintf(_iconStr, "map/5.png");//->
	}
	else
	{
		switch(type)
		{
		case 2:
			sprintf(_iconStr, "map/2.png");//!
			break;
		case 3:
			sprintf(_iconStr, "map/3.png");//yin ?
			break;
		case 4:
			sprintf(_iconStr, "map/4.png");//golden ?
			break;
		default:
			sprintf(_iconStr, "map/1.png");//.
			break;
		}
	}
	SpriteNode* _icon = new SpriteNode();
	_icon->initWithSpriteFrameName(_iconStr);
	if (type == 2 || type == 3 || type == 4)
		_icon->setScale(0.5f);

	if (isRole)
		_icon->setScale(0.7f);
	this->addChild(_icon, MapElementZ_icon, MapElementTAG_icon);

	_icon->release();

	if (txt)
	{
		CCLabelTTF* pNpcLable = CCLabelTTF::labelWithString(txt, CCSizeMake(POSX(250), POSX(20)), CCTextAlignmentLeft, "Arial", POSX(20));
		pNpcLable->setAnchorPoint(ccp(0,0));
		pNpcLable->setPosition(ccp(POSX(-20.0f), POSX(-35.0f)));
		pNpcLable->setColor(ccc3(0, 255, 0));
		this->addChild(pNpcLable, MapElementZ_txt, MapElementTAG_txt);	
	}
	return true;
}

void MapElement::iconSetRotation(float var)
{
	SpriteNode* _icon = (SpriteNode*)this->getChildByTag(MapElementTAG_icon);
	if (!_icon)
		return;

	_icon->setRotation(var);
}