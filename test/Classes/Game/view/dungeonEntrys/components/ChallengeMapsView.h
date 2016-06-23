#ifndef HLQS_ChallengeMapsView_H_
#define HLQS_ChallengeMapsView_H_
#include "PopContainer.h"
#include "ChallengeMapLists.h"
#include "CCUIBackground.h"

class ChallengeMapsView: public PopContainer
{
public:
	ChallengeMapsView();
	~ChallengeMapsView();
	bool init();
	void addScrollViews();
	void setViewAdapter();
	void addIcons(std::vector<MapData>& data);
	void clickCloseHandler(CCObject* pSender);

	void setChallengeTimes(uint8 times);
	void onBuy(CCObject* pSender);

	void clickCancel(CCObject * pSender);
	void clickOK(CCObject * pSender);
public:
	/*StoryCityLists* _storyCityList;
	StoryMapLists* _storyMapList;
	CCUIBackground* _container1;
	CCUIBackground* _container2;*/
	ChallengeMapLists* _challengeMapLists;
	CCLayer* layer;

	///=>hwj
	CCUIBackground* _container1;
	CCUIBackground* _container2;

	uint8 _canChallengeTimes;
	uint8 _buyTimes;
	CCMenu* _buttonBuy;
	CCMenuItemSprite* _buttonSprit;
	CCLabelTTF* _lableChaTimes;
	//CCLabelTTF* _Tips;
	//CCLabelTTF* _TipsContent;
	///<=end_hwj
	enum
	{
		CHALLENGEMAP_LAYER = 0,
		CHALLENGEMAP_CONTAINER1,
		CHALLENGEMAP_CONTAINER2,
		CHALLENGEMAP_BUY,
	};
};

#endif