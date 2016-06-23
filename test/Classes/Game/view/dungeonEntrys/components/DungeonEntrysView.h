#ifndef HLQS_DungeonEntrysView_H_
#define HLQS_DungeonEntrysView_H_
#include "PopContainer.h"
#include "DungeonEntrysCreate.h"

USING_NS_CC;

class DungeonEntrysView: public PopContainer
{
public:
	DungeonEntrysView();
	~DungeonEntrysView();
	bool init();
	void addDirs();
	void onClickDir(CCObject * pSender);
	void updateDirText(std::string str);
	void addScrollViews();
	CCNode * getNewHandItem(int id);
	void clickCloseHandler(CCObject* pSender);//kevinshit

public:
	enum
	{
		TAG_DIR_LEFT = 70,
		TAG_DIR_RIGHT,
		TAG_DIR_Text = 81,
	};

	CCSize _viewSize;
	DungeonEntrysCreate* dungeonScrollView;
	CCLayer *_pContainer;
};

#endif