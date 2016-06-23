#ifndef HLQS_TouchMapNode_H_
#define HLQS_TouchMapNode_H_
#include "BaseType.h"
#define KUANG_H 100
#define KUANG_W 160
#include "LayerNode.h"

USING_NS_CC;

struct MapData
{
	int _id;
	int _star;
	std::string _name;
};

class TouchMapNode: public LayerNode
{
public:
	int _rowId;
	int _colId;
	std::map<int/*index*/, MapData> _nodeList;
	MapData _mapData;
	CCSprite* sp;
	bool _spClicked;
	int _copyType; // 0- story copy, 1-challenge copy,
	bool _isNoTongGuan;

	CCTouch *_pBeganTouch;
	CCMenuItemImage* _btnGUA;
public:
	TouchMapNode();
	TouchMapNode(std::map<int/*index*/, MapData>& list);
	~TouchMapNode();
	void setSpriteIcon(bool open);
	void handleClickEvent(CCObject* pSender);
	void onTAOFA(CCObject* pSender);
	void setNoTongGuan();
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
};

#endif