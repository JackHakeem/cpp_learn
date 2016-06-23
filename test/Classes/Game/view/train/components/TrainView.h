#ifndef _TRAINVIEW_H_
#define _TRAINVIEW_H_

#include "BaseType.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "PopContainer.h"
#include "model/train/vo/TrainVo.h"
#include "model/train/TrainProxy.h"
#include "CCUIBackground.h"

typedef std::map<int, PlayerInfoVo*> PLAYERINFOVOMAP;
class TrainTime;

static const int g_layerBg = 0;
static const int g_layerFront = 1;
static const int gs_MaxEmloyee = 7;

class TrainView : public PopContainer
{
public:
	TrainView();
	~TrainView();

public:
	enum
	{
		RENDERZ_Container = 0,
		RENDERZ_Selected_Time = 1,
	};

	enum
	{
		Tag_Selected_Time = 1,
		Tag_Custom_CD = 2,
		Tag_PopMenu = 3,
		Tag_PointLeft = 4,
		Tag_PointRight = 5,
		Tag_ListView = 101,
		Tag_TrainTips1 = 201,
		Tag_TrainTips2,
	};
	bool init();
	LAYER_NODE_FUNC(TrainView);

	std::vector<int> sDic;					// figure id list
	PLAYERINFOVOMAP itemDic;				// figure list
	void setRoleItem( int id, PlayerInfoVo* pPlayerInfoVo );

	// build figure list
	void createMercList( std::map<int, TrainVo*>* trainDic );
	void resetRoleItem();

	void roleItemClickHandler( int index );
	void startTrainHandler(CCObject* pSender);			//process request train
	void startDoubleTrainHandler(CCObject* pSender);			//process request train
	void openTrainPanel( TrainVo* trainVo );
	void openTimePanel( vector<TimeInitStruct>& infos );
	void setTimeItem( int i, TimeInitStruct* info );
	void resetTimeItem();
	void updateMercInfo( PlayerInfoVo* merc, bool notToCheck = false  );// update figure info

	//cur figure ID
	int getMercId();
	void setMercId( int id );
	void CloseBtCallback(CCObject* pSender);    // close btn 
	void SetVisibleTimePanel( bool bVar );				// hide time choose view
	void updateMercExp( int mercId, int curExp, int needExp );	// update figure exp
	void SetVisibleTrainPanel( bool bVar );
	void endTrainHandler(CCObject* pSender);
	void goldRapidHandler(CCObject* pSender);
	void updateRapicEffect( int mercId, int rapicExp, int critExp );
	void rapicFunction( float dt );
	void playCritEffect( int critExp );
	void buyClickHandler(CCObject* pSender);
	void updateTrainNumTips( int trainNum, int trainLim );
	void SetNotEnoughGold();
	void updateRapicTips( bool showCD, string tips, int exp );
	bool reinitcd();
	virtual void clickCloseHandler(CCObject* pSender);

	// new hand
	CCNode *  getNewHandItem(int id);
	void addScrollListView();
	void setTrainTips();
	void showIsTrained(int id);
	void updateLevelLabel(int figureId , int level);


public:
	int			  _mercId;              // cur merc key ID
	int			  m_SelectedItem;
	PlayerInfoVo* _merc;  				// cur merc
	TimeInitStruct* _timeObj;			// cur choose time

	CCLabelTTF* _txtSite;    // xunlian wei
	CCLabelTTF* _txtSiteCnt;    // 2
	
	CCLayer* m_ContentLayer;
	CCMenu* _btnStart; // _btnStart 
	CCMenu* _btnDoubleExpStart; // _btnStart 

	CCUIBackground* _trainBgNor;
	CCUIBackground* _trainBgRush;

	TrainTime* _trainTime;
	CCLabelTTF* _txtTrain;   //  _train time tips 
	CCLabelTTF* _txtTufeiGet;
	CCLabelTTF* _txtGoldRapid;   //  _train time tips 
	
	CCLabelTTF* _txtModeFont;			// train mode tips
	CCLabelTTF* _txtMode;				// train mode
	CCLabelTTF* _txtTrainUp;			// train mode tips

	CCLabelTTF* _txtTufe;			// Lilian Tufei
	CCLabelTTF* _txtTufeContent;    //  Lilian Tufei tips 
	CCLabelTTF* strs;				//  Lilian Tufei tips：exp add 
	CCMenu* _btnGold;					// gold tufei
	CCMenu* _btnEnd;					  // end btn

	CCMenuItemSprite* _btnExpImg;
	CCMenuItemSprite* _btnGoldImg;
	CCMenuItemSprite *_btnStartItem;

	CCMenu* _btnBuy;					 // buy seat btn

	TrainVo* _trainVo;					// record cur train  
	int _rapicGold;						// Gold tufei request gold

	TimeInitStruct timeDic[ gs_MaxEmloyee ];

	int m_vipLev;
	int m_selectTimeIndex;

	int _selectMode;
	int m_iInitVipLev;
};

#endif