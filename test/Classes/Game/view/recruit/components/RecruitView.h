#ifndef _RECRUITVIEW_H_
#define _RECRUITVIEW_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "RecruitItem.h"
#include "model/recruit/vo/RecruitInfo.h"
#include "CCUIBackground.h"

class RecruitPanel;
class RecruitInfo;
class SkillPic;

class RecruitView : public PopContainer
{
public:
	RecruitView();
	~RecruitView();

public:

	bool init();
	LAYER_NODE_FUNC(RecruitView);
	void onTab1( CCObject* pSender );
	void onTab2( CCObject* pSender );
	void setDefault( int tabIdx = 0 );
	void setTroops( int roleNum, int roleLim );
	void setMyExp( int silver );
	void createRecruitPanel( vector<RecruitInfo> array, int _page, uint totalPage, int pagesize );
	void recItemHandler( RecruitItem* item );
	void setContent( RecruitInfo* info );
	void cleanContent();
	void onRecruitClick( CCObject* pSender );
	void onDismissClick( CCObject* pSender );

	virtual void clickCloseHandler(CCObject* pSender);
	virtual void removeDataObjectChild();
	//virtual void setIsVisible( bool bIsVisible ); 
public:
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void helpHandler( CCObject* pSender );
	CCNode *getNewHandItem(int id);

public:
	CCLayer* pParentLayer;
	CCLabelTTF* _myPop;		// myexp -> my yinbi
	CCLabelTTF* _myExp;		// myexp -> my yinbi
	CCLabelTTF* _myTroops;				// my team
	CCLabelTTF* _name;		// 佣兵名称
	CCLabelTTF* _blood;		// 佣兵hp
	CCLabelTTF* _stamina;	// 体格
	CCLabelTTF* _brawn;		// 腕力
	CCLabelTTF* _intell;    // 智力

	CCLabelTTF* _txtAbout;	// figure info
	CCLabelTTF* _txtForce;	// init attack

	CCLabelTTF* _txtCareer;

	CCLabelTTF* _money;      // 银币消耗
	CCLabelTTF* _fame;       // 达到名声

	CCLabelTTF* _rebirthPic; // 转生次数  星图 

	CCSprite* _icon1;		// 特技1图标
	SkillPic* _pic1;

	CCSprite* _icon2;      // 特技2图标
	SkillPic* _pic2;

	CCSprite* _icon3;		// 奥义图标
	SkillPic* _pic3;
	
	//private var _selected:MovieClip; 	// 图片皮肤 
	CCSprite* _icon;		// 图片icon
	
	CCMenuItemSprite* _tabMc1;	 // Juqing TAB
	CCMenuItemSprite* _tabMc2;	 // Yongbing TAB
	
	CCMenu* _recruitBtn;	 // 招募按钮
	CCMenu* _dismissBtn;  //  解雇按钮 

	RecruitPanel* _recPanel;	// 可招募佣兵面板 

	int _curIndex; 		// 当前标签页
	RecruitInfo* _info; 	// 当前操作Item信息  

	int _page;			// 当前有多少页
	int _totalPage;   // 当前总页数
	//private var _colorTips:String;    //佣兵颜色品质提示信息

	CCUIBackground* m_selectedSpriteImage;
	CCPoint m_locationInView;
	CCMenuItemSprite* m_helpBtn;
	CCUIBackground* _bgSkillTips;
};

#endif