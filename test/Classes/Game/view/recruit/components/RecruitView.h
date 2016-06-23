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
	CCLabelTTF* _name;		// Ӷ������
	CCLabelTTF* _blood;		// Ӷ��hp
	CCLabelTTF* _stamina;	// ���
	CCLabelTTF* _brawn;		// ����
	CCLabelTTF* _intell;    // ����

	CCLabelTTF* _txtAbout;	// figure info
	CCLabelTTF* _txtForce;	// init attack

	CCLabelTTF* _txtCareer;

	CCLabelTTF* _money;      // ��������
	CCLabelTTF* _fame;       // �ﵽ����

	CCLabelTTF* _rebirthPic; // ת������  ��ͼ 

	CCSprite* _icon1;		// �ؼ�1ͼ��
	SkillPic* _pic1;

	CCSprite* _icon2;      // �ؼ�2ͼ��
	SkillPic* _pic2;

	CCSprite* _icon3;		// ����ͼ��
	SkillPic* _pic3;
	
	//private var _selected:MovieClip; 	// ͼƬƤ�� 
	CCSprite* _icon;		// ͼƬicon
	
	CCMenuItemSprite* _tabMc1;	 // Juqing TAB
	CCMenuItemSprite* _tabMc2;	 // Yongbing TAB
	
	CCMenu* _recruitBtn;	 // ��ļ��ť
	CCMenu* _dismissBtn;  //  ��Ͱ�ť 

	RecruitPanel* _recPanel;	// ����ļӶ����� 

	int _curIndex; 		// ��ǰ��ǩҳ
	RecruitInfo* _info; 	// ��ǰ����Item��Ϣ  

	int _page;			// ��ǰ�ж���ҳ
	int _totalPage;   // ��ǰ��ҳ��
	//private var _colorTips:String;    //Ӷ����ɫƷ����ʾ��Ϣ

	CCUIBackground* m_selectedSpriteImage;
	CCPoint m_locationInView;
	CCMenuItemSprite* m_helpBtn;
	CCUIBackground* _bgSkillTips;
};

#endif