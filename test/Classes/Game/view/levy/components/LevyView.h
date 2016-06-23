#ifndef _LevyView_H_
#define _LevyView_H_

#include "PopContainer.h"
#include "BaseType.h"
#include "model/player/vo/AccountInfoVo.h"
#include "CustomCD.h"

class CDEvent;
class LevyInfoVo;

class LevyView : public PopContainer
{
public:
	LevyView();
	~LevyView();
public:

	bool init();
	LAYER_NODE_FUNC(LevyView);
public:
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void rest( uint iValue );
	void setInfo( LevyInfoVo* info );
	void setParamInfo( int starNum, int uniteLv, int earth, int roleLev );
	void limit( uint iValue );
	void cdChangedHandler( CCNode* n, void* data );
	void isLockHandler( int lock );
	void reward( uint iValue);
	void onLevy( CCObject* pSender );
	void lockBtn(ccTime dt);
	void showLevyButton();
	CCNode * getNewHandItem(int id);
	void clickCloseHandler(CCObject * pSender);
	virtual void removeDataObjectChild();
public:

	CCLayer *pParentLayer;
	CCLayer *pParentLayerGold;

	CCLabelTTF* _txtLevySilver;
	//CCLabelTTF* _txtLevyGold;
	CCLabelTTF* _txtAmount;
	uint _rest;										//ʣ�����մ���
	uint _limit;									//���մ�������
	uint _silver;
	CCMenu* _levy;									//���հ�ť
	CCMenuItemSprite *_LevyItem;
	CCMenu* _goldLevy;								//ǿ����ť
	CCLabelTTF* _goldCost;
	CCLabelTTF* _cdTime;
	CCLabelTTF* _txtIn1;
	CCLabelTTF* _txtIn2;
	//CCLabelTTF* _txtIn3;
	//CCLabelTTF* _txtIn4;

	uint _levyReward;								//���ջ�ý���
	uint _levyCost;									//ǿ�����Ľ��
	CustomCD* _cd;				//��ȴʱ��
	//private var _activityLabel:PicLoadingContent;
	AccountInfoVo* _info;
	//private var _btnTxt:TextField;

};

#endif