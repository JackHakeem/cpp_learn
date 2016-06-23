#ifndef _GoldLevyPanel_H_
#define _GoldLevyPanel_H_

#include "PopContainer.h"

class GoldLevyPanel : public LayerNode
{
public:
	GoldLevyPanel();
	~GoldLevyPanel(){};

public:

	bool init();
	LAYER_NODE_FUNC(GoldLevyPanel);
public:
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void setInfo( int c_levyCost, int reward, int d_rest );
	void onGoldLevy(CCObject* obj);
	void initGoldPannel();
	void lockBtn(ccTime dt);

public:
	CCLabelTTF* openTxt;
	int _levyCost;
	int reward;
	CCMenuItemSprite *_GoldItem;
};

#endif