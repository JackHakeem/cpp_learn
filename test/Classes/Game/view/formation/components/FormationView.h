#ifndef _FORMATION_VIEW_H_
#define _FORMATION_VIEW_H_
#include "UIListView/CCUIListView.h"
#include "PopContainer.h"
#include "model/formation/vo/FormationInfo.h"
#include "FormationClip.h"
#include "FormationItem.h"
#include "HeadItem.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "FormationSprite.h"

class UpGradeInfo;

class FormationView : public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum SpriteTag
	{
		DEFAULT = 0,
		HEAD_ICON_1,
		HEAD_ICON_2,
		HEAD_ICON_3,
		HEAD_ICON_4,
		HEAD_ICON_5,
		HEAD_ICON_6,
		HEAD_ICON_7,
		HEAD_ICON_8,
		FORMATION_ICON_1,
		FORMATION_ICON_2,
		FORMATION_ICON_3,
		FORMATION_ICON_4,
		FORMATION_ICON_5,
		FORMATION_ICON_6,
		FORMATION_ICON_7,
		FORMATION_ICON_8,
		FORMATION_ICON_9,
		FORMATION_ORDER_1 = 51,
		FORMATION_ORDER_2,
		FORMATION_ORDER_3,
		FORMATION_ORDER_4,
		FORMATION_ORDER_5,
		TAG_BTN_IMG_ACTIVATE = 101,
		TAG_BTN_ACTIVATE = 201,
		TAG_BTN_GOU = 301,
	};
	CCUIListView *_pListView;
	int _touchBeginTag, _touchMoveTag, _touchEndTag;
	SpriteNode* _panel;
	SpriteNode* copySprite;                              // clone out of the picture
	std::map<int, FormationClip * > _formatMap; // formation list, key: id 10 ~ ~ 23 formation, value: formationclip
	std::map<int, FormationItem * > _playMap; // the current battle formations of FormationItem characters
	std::map<int, HeadItem * > _headMap; // player portrait
	std::map<int, int > _idMap; // key: enum value: the above three map of all key
	uint32 _curWatchFormation; // the current view formation id
	uint32 _curFormation; // current opening formation id
	FormationClip * _preActiveClip;
	FormationClip * _preWatchClip;
	int32 _roleId; // protagonist id
	int teamStatus; // whether group formation  

	int _highLightTag;

	CCTouch *_pPreTouch;

	std::map<int, UpGradeInfo*> _posIDMap; 

	//LayerNode * _curLightItem;
	int _curLightItemPos;
	//LayerNode * _curActivatedItem;
	int _curActivatedItemPos;
	//LayerNode * _curSelectedItem;
	int _curSelectedItemPos;
	//int _curSelectedItemPos;
	FormationSprite * _curSelectHeadSprite;

	LayerNode * _formInfoLayer;
	LayerNode * _merhInfoLayer;
	
	CCLayer *_pContainer;

	CCRect _selectRect;

	CC_SYNTHESIZE(bool , _isSelected , IsSelected);

public:
	FormationView()
	{
		_highLightTag = _touchBeginTag = _touchMoveTag = _touchEndTag = 0;
		iconSpritesArray = new CCMutableArray<FormationSprite *>();
		//_curLightItem = 0;
		_curLightItemPos = -1;
		//_curActivatedItem = 0;
		_curActivatedItemPos = -1;
		//_curSelectedItem = 0;
		_curSelectedItemPos = -1;
		_formInfoLayer = 0;
		_merhInfoLayer = 0;
		_curSelectHeadSprite = 0;
	}
	~FormationView();

	virtual bool init();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	void createFormationList( int teamStatus , int watchFormationId , std::map<int, FormationInfo*> formationMap );
	void createHeadList();
	void watchFormation( FormationClip* clip);
	void setOnFormation( int sitGrid, int figureId );
	void setDownFormation( uint32 sitGrid );
	void sendExchangeMsg( uint32 figureId ,uint8 oldPos ,uint8 newPos );
	void sendPutOnMsg( uint32 figureId , uint32 newPos );
	void sendPutDownMsg( uint32 figureId , uint32 oldPos );
	void updateFormation( char * data );
	void updateActiveFormation( int startID );
	void onClickActivateFormation(CCObject *pSender);
	void clearFormationItem();
	void showFormationInfo(int curWatchFormation);
	void showMerhInfo(int merhID);
	CCRect &addSelectedItems();
	void onSelectedChange(CCObject * pSender);
	void showAttackOrder(bool bVar);

	int getTagByFingerOn(CCTouch *pTouch);

	void setHighLight(int tag, bool isHighLight);

	void EnableActivateButton(bool var);

	CCNode * getNewHandItem( int id );

	void specialHandlerForInit();

protected:
	CC_SYNTHESIZE(CCMutableArray<FormationSprite *>*, iconSpritesArray, IconSpritesArray);
	CC_SYNTHESIZE(CCMutableArray<CCSprite *>*, formationSpritesArray, FormationSpritesArray);
	CC_SYNTHESIZE(CCSprite *, movingSprite, MovingSprite);

	virtual int getCount();

	virtual LayerNode * getView( int position );

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

};

#endif