#pragma once

#include "cocos2d.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "socket/command/s2c/SCMD2C9.h"

using namespace cocos2d;

class LayerNode;

class DamageRankView : public CCLayer,public CCUIListViewAdapter,public CCUIListViewItemActionListener
{
public:
	DamageRankView();
	virtual ~DamageRankView();

	virtual bool init();

	void loadItems();

	void resetMyDamage(int dmg);

	void updateDamageRankList(std::list<SCMD2C9::SCMD2C9Node> dmgRankList , int nTotalDamageLow , int nTotalDamageHigh);

	void onClickShowRewordTips(CCObject * pSender);

	enum ITEM_TAG
	{
		TAG_MyDamage_text = 101,
		TAG_DamageList_Item = 201,
	};

protected:
private:
};