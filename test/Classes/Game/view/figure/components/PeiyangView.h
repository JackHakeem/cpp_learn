#ifndef HLQS_PeiyangView_H_
#define HLQS_PeiyangView_H_
#include "PopContainer.h"
#include "FocusNode.h"
#include "LayerNode.h"
#include "FigureView.h"
#include "../FigureMediator.h"

USING_NS_CC;

struct cache 
{
	int figureID;
	WashVo* washVo;
	cache()
	{
		figureID = 0;
		washVo = NULL;
	}
};

class PeiyangView : public PopContainer
{
public:
	PeiyangView();
	virtual ~PeiyangView();
	bool init();
	void initHeadMap();
	void moveBy(CCPoint pos);
	void loadSelectItems();
	void loadItems(bool isSaved);

	void clickRebornHandler(CCObject * pSender);
	void clickWashHandler(CCObject * pSender);
	void clickAcceptHandler(CCObject * pSender);
	void clickCancelHandler(CCObject * pSender);

	void sendRebornRequest(uint32 figureID);
	void sendWashRequest(uint32 figureID,uint8 type,uint8 useItem);
	void sendSaveRequest(uint32 figureID);

	void loadSelectIcon(int sigSelect,int mulSelect1,int mulSelect2,int mulSelect3);
	void loadStarIcon(int starLev);
	void loadTipsItems();
	void showWashResult();
	CCPoint * getWinPosition(CCPoint &p);
	int calcPractice();
	int calcGold(int type);
	void getPrice(int type);
	void setPrice(int price);
	void updatePrice(int price);

	void updatePractice();
	void updateGold();

	virtual void removeDataObjectChild();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
public:
	enum
	{
		Z_PY = 0,
	};

	enum
	{
		TAG_Price_Labtxt = 9,
	};
	FigureMediator * _figureMediator;
	CCSize _viewSize;
	LayerNode * _peiyangLayer;
	std::map<int,int> headMap;
	CCLabelTTF * _washText;
	CCLabelTTF * _acceptText;
	CCLabelTTF * _cancelText;
	CCMenu * _rebornButton;
	CCMenu * _washButton;
	CCMenu * _acceptButton;
	CCMenu * _cancelButton;
	int _curID;
	int _curAccount;
	int _type;
	int _useItem;
	int _baseStrength;
	int _baseIntellect;
	int _baseStamina;
	int _fullValue;
	int _practiceNeed;
	int _goldNeed;
	uint32 _price;  // SCMD295
	int _washType;
	int _vipLev;
	int _starLev;
	int _reBornNeedLev;
	int _CurScreen;
	int _caStrength;
	int _caStamina;
	int _caIntelect;
	int _sigSelect[MAX_ROLE_NUM];
	bool IsWashed[MAX_ROLE_NUM];
	bool _mulSelect1[MAX_ROLE_NUM];
	bool _mulSelect2[MAX_ROLE_NUM];
	bool _mulSelect3[MAX_ROLE_NUM];
	bool _isRecommend[MAX_ROLE_NUM];
	cache _cache[MAX_ROLE_NUM];
	enum 
	{
		BTN_STAT_PREWASH = 0,
		BTN_STAT_AFTWASH
	};
	enum 
	{
		TAG_SELECT = 100
	};
	CCPoint SELECTPOS[9];
};

#endif