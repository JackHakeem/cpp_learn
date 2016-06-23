#ifndef _MapAwardPanel_H_
#define _MapAwardPanel_H_

#include "PopContainer.h"
#include "BaseType.h"
#include "CCUIBackground.h"
#include "socket/command/s14/SCMD140.h"
#include "model/honor/vo/HonorGoodVo.h"

class MapAwardPanel : public PopContainer
{
public:
	MapAwardPanel();
	~MapAwardPanel(){};

public:
	enum
	{
		RENDERZ_Container = 0,
	};
	bool init();
	void init( HonorGoodVo* honorGoods );
	LAYER_NODE_FUNC(MapAwardPanel);
public:
	//void registerWithTouchDispatcher( void );
	//bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void clearItems();
	void createItem( int sit, int type, int num );
	void defClickHandler( CCObject* pSender );
	void tookItem( int awardId );
	void autoFindNpc(int taskId);

	void EnableButtonX( bool bVar );
	void showBagSeclet();
	void okFunction( CCObject* pObject );
	void cancelFunction( CCObject* pObject );
	void clickCloseHandler(CCObject* obj);
public:
	int _honorId;
	int _taskId;
	CCUIBackground* _pic[3];
	CCSprite* _picGoods[3];

	CCLabelTTF* _txtGoods[3];

	CCMenu *_buttonMenuX;
};

#endif