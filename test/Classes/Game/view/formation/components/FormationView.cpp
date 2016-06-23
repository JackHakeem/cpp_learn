#include "FormationView.h"
#include "utils/ScaleUtil.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "model/skill/vo/SkillVo.h"
#include "model/skill/SkillManager.h"
#include "FormationClip.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c30/CCMD30F.h"
#include "manager/TouchLayerEnum.h"
#include "socket/command/s31/SCMD310.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "model/skill/vo/SkillType.h"
#include "SpriteNode.h"
#include "model/skill/SkillProxy.h"
#include "model/formation/vo/FormationInfo.h"
#include "control/AppFacade.h"
#include "BaseType.h"
#include "socket/command/c31/CCMD311.h"
#include "utils/ColorUtil.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "CCCommon.h"
#include "manager/ViewManager.h"

const int TAG_HEAD_ITEM = 2001;
const int TAG_HIGH_LIGHT = 2002;
const int TAG_OPEN = 2003;

/*
  80 * 80

  -1-   -2-
  -3-   -4-
  -5-   -6-
  -7-   -8-
*/
#define FLOAT_HEAD_SPACING POSX(22)
#define FLOAT_HEAD_SIZE POSX(74)
#define FLOAT_HEAD_DISTANCE POSX(96)

#define POINT_HEAD_1 ccp(POSX(54), POSX(392))
#define POINT_HEAD_2 ccp(POSX(138), POSX(392))


/*
  122 * 122

  //-1-  -2-  -3- 
  //-4-  -5-  -6- 
  //-7-  -8-  -9- 

  -1-  -4-  -7- 
  -2-  -5-  -8- 
  -3-  -6-  -9- 
  */
const float FLOAT_FORMATION_ICON_SCALE = 1.4 ;/*/ CCDirector::sharedDirector()->getContentScaleFactor();*/
#define FLOAT_FORMATION_ICON		POSX(112)
#define POINT_FORMATION_ICON_1		ccp(POSX(262), POSX(372))
#define POINT_FORMATION_ICON_2		ccp(POSX(262), POSX(232))
#define POINT_FORMATION_ICON_3		ccp(POSX(262), POSX(90))
#define FLOAT_FORMATION_ICON_DISTANCE POSX(142)

#define POINT_FORMATION_LIST		ccp(POSX(756), POSX(120))
#define SIZE_FORMATION_LIST			CCSizeMake(POSX(106), POSX(386))
#define CCPOINT_FORMATION_ITEM		ccp(POSX(26),POSX(27))
#define CCPOINT_FORMATION_INFO		ccp(POSX(40),POSX(500))
#define CCPOINT_MERH_INFO			ccp(POSX(30),POSX(40))

#define CCPOINT_BTN_SELECT			ccp(POSX(520),POSX(500))

const int MOVING_SPRITE_TAG = 1001;


bool FormationView::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	
	setIsSelected(true);

	teamStatus = 0;

	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formation_1.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formation_2.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formationOrder.plist");


	setContentSize(CCDirector::sharedDirector()->getWinSize());
	setPopContentSize(this->getContentSize());

	this->setIsTouchEnabled(true);

	key = PopEventName::FORMATION;

	float scale = 0.77f;// FLOAT_HEAD_SIZE / 96;Doyang1
	
	_pContainer = new CCLayer();
	_pContainer->setAnchorPoint(CCPointZero);
	_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));

	// Change this 
	// CCSpirteBatchNode.

	// add left user icons.
	for(int i=0; i<4; ++i)
	{
		FormationSprite *pLeftSprite = FormationSprite::spriteWithSpriteFrameName("pack/unlock.png");
		pLeftSprite->setAnchorPoint(CCPointZero);
		pLeftSprite->setIsRelativeAnchorPoint(true);
		pLeftSprite->setScale(scale);
		pLeftSprite->setPosition(ccp(POINT_HEAD_1.x, POINT_HEAD_1.y - i * FLOAT_HEAD_DISTANCE));
		pLeftSprite->setTag(i * 2);
		getIconSpritesArray()->addObject(pLeftSprite);
		_pContainer->addChild(pLeftSprite);
		//Doyang 20120719
		pLeftSprite->release();

		FormationSprite *pRightSprite = FormationSprite::spriteWithSpriteFrameName("pack/unlock.png");
		pRightSprite->setAnchorPoint(CCPointZero);
		pRightSprite->setIsRelativeAnchorPoint(true);
		pRightSprite->setScale(scale);
		pRightSprite->setTag(i * 2 + 1);
		pRightSprite->setPosition(ccp(POINT_HEAD_2.x, POINT_HEAD_2.y - i * FLOAT_HEAD_DISTANCE));
		getIconSpritesArray()->addObject(pRightSprite);
		_pContainer->addChild(pRightSprite);
		//Doyang 20120719
		pRightSprite->release();
	}

	// add center formation icons.
	for(int i=0; i<3; ++i)
	{
		FormationSprite *pLeftSprite = FormationSprite::spriteWithSpriteFrameName("formation/formation_block_close.png");
		pLeftSprite->setAnchorPoint(CCPointZero);
		pLeftSprite->setIsRelativeAnchorPoint(true);
		pLeftSprite->setPosition(ccp(POINT_FORMATION_ICON_1.x + i * FLOAT_FORMATION_ICON_DISTANCE, 
			POINT_FORMATION_ICON_1.y));
		pLeftSprite->setTag(i * 3 + 8);
		_pContainer->addChild(pLeftSprite);
		getIconSpritesArray()->addObject(pLeftSprite);
		//Doyang 20120719
		pLeftSprite->release();

		FormationSprite *pCenterSprite = FormationSprite::spriteWithSpriteFrameName("formation/formation_block_close.png");
		pCenterSprite->setAnchorPoint(CCPointZero);
		pCenterSprite->setIsRelativeAnchorPoint(true);
		pCenterSprite->setPosition(ccp(POINT_FORMATION_ICON_2.x + i * FLOAT_FORMATION_ICON_DISTANCE, 
			POINT_FORMATION_ICON_2.y));
		pCenterSprite->setTag(i * 3 + 9);
		_pContainer->addChild(pCenterSprite);
		getIconSpritesArray()->addObject(pCenterSprite);
		//Doyang 20120719
		pCenterSprite->release();

		FormationSprite *pRightSprite = FormationSprite::spriteWithSpriteFrameName("formation/formation_block_close.png");
		pRightSprite->setAnchorPoint(CCPointZero);
		pRightSprite->setIsRelativeAnchorPoint(true);
		pRightSprite->setPosition(ccp(POINT_FORMATION_ICON_3.x + i * FLOAT_FORMATION_ICON_DISTANCE,
			POINT_FORMATION_ICON_3.y));
		pRightSprite->setTag(i * 3 + 10);
		_pContainer->addChild(pRightSprite);
		getIconSpritesArray()->addObject(pRightSprite);
		//Doyang 20120719
		pRightSprite->release();
	}

	// add right formations list.
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POINT_FORMATION_LIST.x,
		POINT_FORMATION_LIST.y,
		SIZE_FORMATION_LIST.width,
		SIZE_FORMATION_LIST.height), 
		false);
	if(!_pListView) 
		return false;
	_pListView->setAnchorPoint(CCPointZero);
	//_pListView->setBackgroundWithFile("assets/task/TaskListBg.png");
	//_pListView->setClipLayerRect(CCRECT_TASK_LIST_CLIP);
	_pListView->setSpacingVertical(POSX(10));
	_pListView->setAdapter(this);
	_pListView->setOnItemActionListener(this);
	_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pContainer->getPosition(), _pListView->getPosition()));
	_pListView->m_pri = TLE::WindowLayer_FormationView;
	_pContainer->addChild(_pListView, 2);
	_pListView->release();//20130125

	// button
	CCPoint btnPos = ccp(POINT_FORMATION_LIST.x+SIZE_FORMATION_LIST.width/2,POINT_FORMATION_LIST.y-POSX(50));


	

	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return false;
	}
	CCMenuItemSprite *pMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(FormationView::onClickActivateFormation));
	CCMenu * pMenuActivateForm = CCMenu::menuWithItem(pMenuImg);
	pMenuImg->setTag(TAG_BTN_IMG_ACTIVATE);
	pMenuActivateForm->setPosition(btnPos);
	pMenuActivateForm->setTouchLayer(TLE::WindowLayer_FormationView);
	pMenuActivateForm->setTag(TAG_BTN_ACTIVATE);
	_pContainer->addChild(pMenuActivateForm,0);
	CCLabelTTF * pButtonText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("ZX3").c_str(),
		CCSizeMake(POSX(80), POSX(20)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(20.0f));
	pButtonText->setColor(ccc3(255,215,25));
	pButtonText->setPosition(btnPos);
	_pContainer->addChild(pButtonText,1);	

	// center logo
	SpriteNode * pSpriteLogo = new SpriteNode;
	pSpriteLogo->initWithSpriteFrameName("formation/formation_logo.png");
	pSpriteLogo->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height-POSX(80)));
	_pContainer->addChild(pSpriteLogo,1);


	NewhandConst::Instance()->registerItem(NewhandConst::ITEM_FORMATION_SIT6, getIconSpritesArray()->getObjectAtIndex(6 + 7));
	NewhandConst::Instance()->registerItem(NewhandConst::ITEM_FORMATION_SIT5, getIconSpritesArray()->getObjectAtIndex(5 + 7));
	/*NewhandConst.registerItem(NewhandConst.ITEM_FORMATION_CLOSE, _panel["_btnClose"]);*/
	NewhandConst::Instance()->registerItem(NewhandConst::ITEM_FORMATION_ACTIVE, pMenuImg);
	this->addChild(_pContainer);

	// selected items
	_selectRect = addSelectedItems();

	// default click item
	onItemClickListener( 0 , _curActivatedItemPos );
	
	return true;
}

void FormationView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::WindowLayer_FormationView, true);
}

bool FormationView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	_touchBeginTag = -1;
	_touchEndTag = -1;
	_touchMoveTag = -1;
	_pPreTouch = pTouch;
	CCPoint curPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	int tag = this->getTagByFingerOn(pTouch);
	if(tag >= 0)
	{
		_touchBeginTag = tag;
		CCLog("ccTouchBegan=, tag=%d", _touchBeginTag);
		this->setHighLight(tag, true);

		// Add moving sprite
		FormationSprite *pIconSprite = this->getIconSpritesArray()->getObjectAtIndex(tag);
		if(!pIconSprite || !pIconSprite->_pInfo)
		{
			this->setHighLight(tag, false);
			return false;
		}

		// show merh info
		if (tag <= 7)
		{
			FormationSprite * pHeadSprite = getIconSpritesArray()->getObjectAtIndex(tag);
			if (pHeadSprite)
			{
				if (pHeadSprite->_pInfo)
				{
					int merhID = pHeadSprite->_pInfo->playerBaseInfo.id;
					showMerhInfo(merhID);
				}
				if ((_curSelectHeadSprite)&&(_curSelectHeadSprite->getTag() != tag))
				{
					if (_curSelectHeadSprite->getChildByTag(TAG_HIGH_LIGHT))
					{
						_curSelectHeadSprite->getChildByTag(TAG_HIGH_LIGHT)->setIsVisible(false);
					}					
				}
				if (pHeadSprite->getChildByTag(TAG_HIGH_LIGHT))
				{
					pHeadSprite->getChildByTag(TAG_HIGH_LIGHT)->setIsVisible(true);
				}
				_curSelectHeadSprite = pHeadSprite;
			}			
		}

		if ((tag>=8)&&(tag<=16))
		{
			// 20120627
			// Doyang.
			NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_DEPLOY_OP_CHANGE_TYPE);


			if(!pIconSprite->getChildByTag(TAG_OPEN))
			{
				this->setHighLight(tag, false);
				return false;
			}	
		}

		//char *pIconPath = new char[20];
		char pIconPath[32] = {0}; // LH0713LEAK
		int cloth = pIconSprite->_pInfo->playerBaseInfo.cloth;
		
		// by LH 0730
		if (cloth <= 0)
		{
			this->setHighLight(tag, false);
			return false;
		}
		//sprintf(pIconPath, "head/%d.png", pIconSprite->_pInfo->playerBaseInfo.cloth);
		//CCSprite *pMovingSprite = CCSprite::spriteWithSpriteFrameName(pIconPath);
		sprintf(pIconPath, "assets/icon/head/%d.png", pIconSprite->_pInfo->playerBaseInfo.cloth);
		CCSprite *pMovingSprite = CCSprite::spriteWithFile(pIconPath);
		if (pMovingSprite)
		{
			//pMovingSprite->setAnchorPoint(CCPointZero);
			pMovingSprite->setPosition(/*pIconSprite->getPosition()*/curPos);
			setMovingSprite(pMovingSprite);
			pMovingSprite->setTag(MOVING_SPRITE_TAG);
			pMovingSprite->setScale(2.0);
		}
		// LH0713
		if (_pContainer->getChildByTag(MOVING_SPRITE_TAG))
		{
			_pContainer->removeChildByTag(MOVING_SPRITE_TAG,true);
		}
		if (movingSprite)
		{
			_pContainer->addChild(movingSprite, 1,MOVING_SPRITE_TAG);
		}

		return true;
	}
	else
	{
		if (CCRect::CCRectContainsPoint( _selectRect , curPos) )
		{
			onSelectedChange(0);
			return true;
		}
		
		return false;
	}
}

void FormationView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	int tag = getTagByFingerOn(pTouch);

	// move moving sprite.
	//CCPoint nextPos = this->convertToWorldSpace(pTouch->locationInView(pTouch->view()));
	CCPoint nextPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	CCSprite *pMovingSprite = (CCSprite *) _pContainer->getChildByTag(MOVING_SPRITE_TAG);
	if(pMovingSprite)
	{
		pMovingSprite->setPosition(nextPos);
	}

	_pPreTouch = pTouch;
	//
	if(tag >= 0)
	{
		if(tag != _touchBeginTag && tag != _touchMoveTag)
		{
			_touchMoveTag = tag;

			bool isHighLight = false;
			if(_touchBeginTag < 8)
			{
				// From head list.
				if(_touchMoveTag >= 8)
				{
					isHighLight = true;
				}
			}
			else if(_touchBeginTag < 17)
			{
				// From formation list.
				if(_touchMoveTag < 8)
				{
					isHighLight = true;
				}
			}
			if(isHighLight)
			{
				// Cancel HighLight
				this->setHighLight(_highLightTag, false);

				// Reset HighLight
				this->setHighLight(_touchMoveTag, true);
			}

			CCLog("ccTouchMoved, tag=%d", tag);
		}
	}
	else
	{
		_touchMoveTag = tag; // -1
	}
}

void FormationView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	_touchEndTag = _touchMoveTag;
	CCLog("ccTouchEnded=, tag=%d", _touchEndTag);

	this->setHighLight(_highLightTag, false);

	if (_touchEndTag < 0) {	_pContainer->removeChildByTag(MOVING_SPRITE_TAG,true); return; }

	//FormationSprite *pTouchEndSprite = getIconSpritesArray()->getObjectAtIndex(_touchEndTag);
	FormationSprite *pTouchBeginSprite = getIconSpritesArray()->getObjectAtIndex(_touchBeginTag);
	if(_touchEndTag < 8)
	{
		// put down
		if (_touchBeginTag != _touchEndTag)
		{
			if ((_touchBeginTag >= 8) && (_touchBeginTag < 17))
			{
				if(pTouchBeginSprite!= NULL && pTouchBeginSprite->_pInfo != NULL)
				{
					int oldID = pTouchBeginSprite->_pInfo->playerBaseInfo.id;
					int oldPos = _touchBeginTag-7;
					if (oldID == RoleManage::Instance()->roleInfo()->playerBaseInfo.id)
					{
						Message::Instance()->show(ValuesUtil::Instance()->getString("ZX0"),ccc3(233,122,12),1);
					}
					else
					{
						sendPutDownMsg( oldID, oldPos );
					}
				}
			}
		}
	}
	else if(_touchEndTag < 17)
	{
		if(_touchBeginTag != _touchEndTag)
		{
			if(_touchBeginTag < 8)
			{
				// put on
				if(pTouchBeginSprite!= NULL && pTouchBeginSprite->_pInfo != NULL)
				{
					int oldID = pTouchBeginSprite->_pInfo->playerBaseInfo.id;
					int newPos = _touchEndTag-7;
					sendPutOnMsg( oldID, newPos );
				}
			}
			else if(_touchBeginTag < 17)
			{
				// change
				if(pTouchBeginSprite!= NULL && pTouchBeginSprite->_pInfo != NULL)
				{
					int oldID = pTouchBeginSprite->_pInfo->playerBaseInfo.id;
					int oldPos = _touchBeginTag-7;
					int newPos = _touchEndTag-7;
					sendExchangeMsg( oldID, oldPos, newPos);
				}
			}
		}
	}
	else
	{

	}
	_pContainer->removeChildByTag(MOVING_SPRITE_TAG,true);
}


int FormationView::getTagByFingerOn( CCTouch *pTouch )
{
	/*CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(locationInView);*/
	CCPoint nodeSpacePoint = this->convertTouchToNodeSpace(pTouch);
	CCMutableArray<FormationSprite *>::CCMutableArrayIterator it;
	int tag = -1;
	for(it = getIconSpritesArray()->begin(); it != getIconSpritesArray()->end(); ++it)
	{
		FormationSprite *pSprite = *it;
		CCRect spriteRect = CCRectMake(_pContainer->getPosition().x + pSprite->getPosition().x,
			_pContainer->getPosition().y + pSprite->getPosition().y,
			pSprite->getContentSize().width,
			pSprite->getContentSize().height);

		if(CCRect::CCRectContainsPoint(spriteRect, nodeSpacePoint))
		{
			tag = pSprite->getTag();
			break;
		}
	}

	if(tag > getIconSpritesArray()->count())
		tag = -1;

	return tag;
}

void FormationView::createFormationList( int teamStatus , int watchFormationId , std::map<int, FormationInfo*> formationMap )
{
	if(teamStatus==0)     //No state party
	{
		_curFormation = watchFormationId;
	}
	int sitNum=0;

	for(int i=10; i<=16; i++)       //id:10~16Single formation
	{
		std::map<int, FormationInfo*>::iterator it; 
		if( (it =formationMap.find(i)) == formationMap.end() ) continue;
		FormationInfo* info=formationMap.find(i)->second;
		//SkillVo* formationSkill=SkillManager::Instance()->getSkill(info->id);

		FormationClip* clip = new FormationClip(sitNum, info);   
		//if (clip)
		//{				
		//	CCLabelTTF* skillLabel = CCLabelTTF::labelWithString( formationSkill->name.c_str(), g_sSimHeiFont, (float)20 );
		//	skillLabel->setColor( ccRED );
		//	formationSkill->
		//	//_panel->addChild(skillLabel,3 , sitNum+18 );
		//	skillLabel-> setPosition(ccp(758, 443-sitNum*50));			 
		//}  

		/*_formatMap.insert(make_pair(i,clip));
		_idMap.insert(make_pair(sitNum+18,i));*/

		sitNum++;
		if(watchFormationId == info->getId())
		{	// default shows open formation
			watchFormation(clip);
		} 
		clip->release();

		if(_curFormation == info->getId())
		{
			//addForDes(info);			
		}	  


		if(i==13){
			NewhandConst::Instance()->registerItem(NewhandConst::ITEM_FORMATION_CLIP13, clip);
		}
	}
}

void FormationView::createHeadList()
{
	// LH0719
	for (int i = 0;i< 8 ;i++)
	{
		FormationSprite *pIconSprite = getIconSpritesArray()->getObjectAtIndex(i);
		//pIconSprite->removeFromParentAndCleanup(true);
		//pIconSprite->removeAllChildrenWithCleanup(true);
		//pIconSprite->release();
		//pIconSprite = 0;
		//pIconSprite->removeAllChildrenWithCleanup(true);
		pIconSprite->removeChildByTag(TAG_HEAD_ITEM, true);
		pIconSprite->_pInfo = 0;
	}
	//getIconSpritesArray()->removeAllObjects(true);

	uint32 sitGrid=0;

	RoleManage *pRoleManage = RoleManage::Instance();
	//Protagonist doesn't appear on the list of head, but must in the tactics, and never next array
	if(pRoleManage->accountInfo() == NULL)
		return;

	_roleId = pRoleManage->accountInfo()->roleId;
	cocos2d::CCLog("_roleId is %d",_roleId);

	//Add role information
	//addRoleDes(_roleId);

	//// LH0719
	//std::map<int,HeadItem*>::iterator iter = _headMap.begin();
	//for (;iter != _headMap.end();iter++)
	//{
	//	if (iter->second)
	//	{
	//		iter->second->release();
	//	}
	//}
	_headMap.clear();
	_idMap.clear();

	//std::map<int, PlayerInfoVo>* mercMap = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator it = mercMap->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* mercMap = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = mercMap->begin();
	int count = 0;
	for(it ;it != mercMap->end(); it++)
	{
		int firstHead=1;
		PlayerInfoVo  *info = &it->second;
		uint32 id=info->playerBaseInfo.id;
		if(id == _roleId) continue;
		CCLog("---count=%d,id=%d", count, id);

		HeadItem* item=new HeadItem(sitGrid, *info, FLOAT_HEAD_SIZE / 96);

		if(item)
		{
			/*item ->initWithSpriteFrameName("formation/8.png");*/
			//_panel->addChild(item,3,firstHead ); 
			//item->setPosition(ccp( (int)(sitGrid%2)*80+54, 393-(int)(sitGrid/2)*93));   //Calculating coordinates
			
			FormationSprite *pIconSprite = getIconSpritesArray()->getObjectAtIndex(count);
			if(pIconSprite)
			{
				pIconSprite->_pInfo = info;
				if (pIconSprite->getChildByTag(TAG_HEAD_ITEM))
				{
					pIconSprite->removeChildByTag(TAG_HEAD_ITEM,true);
				}
				pIconSprite->addChild(item,0,TAG_HEAD_ITEM);
				item->release(); // jae 20121112

				// add selected green light				
				SpriteNode *pListSpriteActivated = new SpriteNode();
				pListSpriteActivated->initWithSpriteFrameName("formation/formation_activated.png");
				pListSpriteActivated->setAnchorPoint(CCPointZero);
				pListSpriteActivated->setIsVisible(false);
				pListSpriteActivated->setPosition(ccp(-4,-4));
				if (!pIconSprite->getChildByTag(1))
				{
					pIconSprite->addChild(pListSpriteActivated,1,1);
					pListSpriteActivated->release();
				}
				else
				{
					pListSpriteActivated->release(); // jae 20121112
				}
			}
			else
			{
				item->release();
				item = 0;
			}

			_headMap.insert(make_pair(id, item));
			_idMap.insert(make_pair(firstHead,id));
		}

		if(count == 0)
		{
			NewhandConst::Instance()->registerItem(NewhandConst::ITEM_FORMATION_HEAD, item);
		}

		++count;

	}
	
	
}

void FormationView::watchFormation( FormationClip* clip )
{
	_curWatchFormation =clip->info->getId();    
	cocos2d::CCLog("_curWatchFormation is %d",_curWatchFormation );
	clearFormationItem();
	int formID = clip->info->getId();
	int formLev = clip->info->lev > 20 ? 20 : clip->info->lev;
	LevSkillVo *pLevSkillVo = SkillManager::Instance()->getLevSkill(formID, formLev);
	if(pLevSkillVo)
	{
		std::vector<int> arr = pLevSkillVo->arrParam;
		std::vector<int>::iterator iter = arr.begin();
		int tag = 8;
		while (iter != arr.end())
		{
			if (*iter)
			{
				FormationSprite * pFormSprite = getIconSpritesArray()->getObjectAtIndex(tag);
				CCSprite * pValidGrid = CCSprite::spriteWithSpriteFrameName("formation/formation_block_open.png");
				pValidGrid->setAnchorPoint(CCPointZero);
				if (pFormSprite->getChildByTag(TAG_OPEN))
				{
					pFormSprite->removeChildByTag(TAG_OPEN, true);
				}
				pFormSprite->addChild(pValidGrid, 0, TAG_OPEN);
			}
			++iter;
			++tag;
		}		
	}
	if(teamStatus == 0 && clip->info->getId()<17)
	{     //Single formation
		std::map<int, int>::iterator figureit;
		for(figureit=clip->info->figuresMap.begin();figureit!=clip->info->figuresMap.end();figureit++)
		{
			//People stand to designated spot
			setOnFormation((int)(figureit->first),(int)(figureit->second));
		}

	} 
}

void FormationView::setOnFormation( int sitGrid, int figureId )
{
	if(sitGrid<1 ||sitGrid>9 || figureId==0) return;

	PlayerInfoVo* info=RoleManage::Instance()->getMercenary(figureId);    //Through the figureId get mercenaries information, not to get the data, figureId = 11000002 is correct?
	if (!info)   //Get PlayerInfoVo test data
	{
		return;
		/*
		SpriteNode* playTest1=new SpriteNode();
		if(sitGrid%2==0)
		{
			playTest1->initWithSpriteFrameName("formation/jishinan.png");
		}
		else{
			playTest1->initWithSpriteFrameName("formation/youxianan.png");
		}
		
		*/
		//_panel->addChild(playTest1, 3, sitGrid+8 );  //Added to the formation of the panel
		//playTest1->setPosition(standPos[sitGrid-1]);    

	}
	 
	else
	{
		FormationItem* item = new FormationItem(sitGrid, info);      //The characters and create added to formation panel
		
		//char *pIconPath = new char[20];
		char pIconPath[32] = {0};
		sprintf(pIconPath, "assets/icon/head/%d.png", info->playerBaseInfo.cloth);
		if(item && item->initWithFile(pIconPath))
		{

			//Should through the resid get path
			CCSprite *pLeftGrid = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
			item->setScale(pLeftGrid->getContentSize().width*/*(FLOAT_HEAD_SIZE / 96)*/ 0.77 / item->getContentSize().width);
			CC_SAFE_DELETE(pLeftGrid);
			item->setAnchorPoint(CCPointZero);
			item->setPosition(CCPOINT_FORMATION_ITEM);
			//item->setScale(FLOAT_FORMATION_ICON_SCALE);
		}

		//_panel->addChild(item,3,sitGrid+8 );  //Added to the formation of the panel
		//item->setPosition(standPos[sitGrid-1]);   // should use sitGird to get coordinates death a coordinate array write FormationPoint [9]

		FormationSprite *pIconSprite = getIconSpritesArray()->getObjectAtIndex(sitGrid + 7);
		if(pIconSprite)
		{
			pIconSprite->_pInfo = info;
			if (item)
			{
				pIconSprite->addChild(item,1, TAG_HEAD_ITEM);
				item->release(); // LH0712
			}
		}

		std::map<int , HeadItem*>::iterator it;
		if ( (it = _headMap.find(figureId)) != _headMap.end())
		{
			it->second->setPlayIcon(true);
		}


		// show order
		showAttackOrder(getIsSelected());


		/*_playMap.insert(make_pair(sitGrid,item));
		_idMap.insert(make_pair(sitGrid+8 ,sitGrid));*/
	}
}

void FormationView::setDownFormation( uint32 sitGrid )
{
	if(sitGrid<1 || sitGrid>9) {return;}
	int tag = sitGrid + 7;
	CCMutableArray<FormationSprite *> * pArray = getIconSpritesArray();
	FormationSprite *pFormSprite = pArray->getObjectAtIndex(tag);
	if (!pFormSprite){	return;};

	if (pFormSprite->getChildByTag(TAG_HEAD_ITEM))
	{
		pFormSprite->removeChildByTag(TAG_HEAD_ITEM, true);
	}
	else
	{
		return;
	}

	int id = pFormSprite->_pInfo->playerBaseInfo.id;
	std::map<int , HeadItem*>::iterator it;
	if ( (it = _headMap.find(id)) != _headMap.end())
	{
		it->second->setPlayIcon(false);
	}


	// show order
	showAttackOrder(getIsSelected());
}

void FormationView::sendPutDownMsg( uint32 figureId , uint32 oldPos )
{
	CCMD30F* s = new CCMD30F();
	s->a_formationId=uint16(_curWatchFormation);
	s->b_mercId=figureId;
	s->c_oldPos=(uint8)oldPos;
	s->d_newPos=(uint8)0;
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if (pSocket)
		pSocket->sendMessage(s);

	CC_SAFE_DELETE(s); // LH0712LEAK
}

void FormationView::sendExchangeMsg( uint32 figureId ,uint8 oldPos ,uint8 newPos )
{
	CCMD30F* s = new CCMD30F();
	s->a_formationId=uint16(_curWatchFormation);
	s->b_mercId=figureId;
	s->c_oldPos=(uint8)oldPos;
	s->d_newPos=(uint8)newPos;
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if (pSocket)
		pSocket->sendMessage(s);

	CC_SAFE_DELETE(s); // LH0712LEAK
}

void FormationView::updateFormation( char * data )
{
	SCMD310 * pCmd = (SCMD310 *)data;

	if(pCmd->b_formationId != _curWatchFormation) {return;}
	setDownFormation(pCmd->d_srcPos);
	setDownFormation(pCmd->f_destPos);
	setOnFormation(pCmd->d_srcPos, pCmd->c_srcId);
	setOnFormation(pCmd->f_destPos, pCmd->e_destId);
}

void FormationView::updateActiveFormation(int startID )
{
	// LH0718	
	EnableActivateButton(false);

	_curFormation = startID;

	CCMutableArray<LayerNode *> * pListNodes = _pListView->getChilds();

	if (_curActivatedItemPos != -1)
	{
		LayerNode * pLightLayer = pListNodes->getObjectAtIndex(_curActivatedItemPos);
		if (pLightLayer)
		{
			if (pLightLayer->getChildByTag(1))
			{
				pLightLayer->removeChildByTag(1,true);
			}
		}
	}
	/*
	if (_curActivatedItem->getChildByTag(1))
	{
		_curActivatedItem->removeChildByTag(1,true);
	} 
	*/
	// LH0713
// 	if (_curActivatedItem)
// 	{
// 		_curActivatedItem->removeAllChildrenWithCleanup(true);
// 		_curActivatedItem->release();
// 	}

	if (_curSelectedItemPos != -1)
	{
		SpriteNode *pListSpriteActivated = new SpriteNode();
		pListSpriteActivated->initWithSpriteFrameName("formation/formation_activated.png");
		pListSpriteActivated->setAnchorPoint(CCPointZero);
		pListSpriteActivated->setIsVisible(true);

		LayerNode * pLightLayer = pListNodes->getObjectAtIndex(_curSelectedItemPos);
		if (pLightLayer)
		{
			CCPoint pos = pLightLayer->getChildByTag(0)->getPosition();
			pListSpriteActivated->setPosition(ccp(pos.x-4,pos.y-4));
			if (pLightLayer->getChildByTag(1))
			{
				pLightLayer->removeChildByTag(1,true);
			}

			pLightLayer->addChild(pListSpriteActivated,1,1);
			pListSpriteActivated->release(); //LH0712LEAK

			_curActivatedItemPos = _curSelectedItemPos;
		}
	}

	//Doyang 20120711
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		pChildLayer->release();
	}

	// refresh
	_pListView->setAdapter(this);

}

void FormationView::sendPutOnMsg( uint32 figureId , uint32 newPos )
{
	//if(_teamStatus == 0){

	/*if(_playDic[newPos] && _playDic[newPos].figureId==_roleId){
	LangManager.msgShow("FMT003");
	return;
	}*/
	CCMD30F* s = new CCMD30F();
	s->a_formationId=uint16(_curWatchFormation);
	s->b_mercId=figureId;
	s->c_oldPos=(uint8)0;
	s->d_newPos=(uint8)newPos;
	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if (pSocket)
		pSocket->sendMessage(s);

	CC_SAFE_DELETE(s); // LH0712LEAK
	//dispatchEvent(new ParamEvent(MEMBER_CHANGE, {type:1, cmd:cmd1}));
	return;

	//}else{

	//	var desId:int = 0;
	//	if(_playDic[newPos]!=undefined){//阵型位置有人
	//		desId = _playDic[newPos].figureId;
	//		if(desId == _roleId){
	//			LangManager.msgShow("FMT003");
	//			return;
	//		}
	//		if(_roleManage.getMercenary(desId)==null){
	//			LangManager.msgShow("FMT004");
	//			return;
	//		}
	//	}else if(_myFigureNum>=3){//阵型位置没人，但总人数大于3
	//		LangManager.msgShow("FMT005");
	//		return;
	//	}
	//	var cmd2:CCMD386 = new CCMD386;
	//	cmd2.a_formation = new Int16(_curWatchFormation);
	//	cmd2.b_oldFigure = desId;
	//	cmd2.c_newFigure = figureId
	//		dispatchEvent(new ParamEvent(MEMBER_CHANGE, {type:2, cmd:cmd2}));
	//}
}

void FormationView::clearFormationItem()
{
	FormationSprite * pHeadSprite = 0;
	int tag = 0;
	for(tag = 0;tag < 8;tag++)
	{
		pHeadSprite = getIconSpritesArray()->getObjectAtIndex(tag);
		if (pHeadSprite)
		{
			if (pHeadSprite->_pInfo)
			{
				int figureId = pHeadSprite->_pInfo->playerBaseInfo.id;
				std::map<int , HeadItem*>::iterator it;
				if ( (it = _headMap.find(figureId)) != _headMap.end())
				{
					it->second->setPlayIcon(false);
				}
			}
		}		
	}

	FormationSprite * pFormSprite = 0;
//	tag = 8;
	for(tag = 8;tag < 17;tag++)
	{
		pFormSprite = getIconSpritesArray()->getObjectAtIndex(tag);
		pFormSprite->removeAllChildrenWithCleanup(true);
	}
}

int FormationView::getCount()
{
	std::map<int, SkillNode>* skillNode = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
	std::map<int, SkillNode>::iterator it = skillNode->begin();

	int count = 0;
	for (;it != skillNode->end();it++)
	{
		if (it->second.formationInfo->getId() >= 17){break;}
		++count;
	}
	/*
	std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::FORMATION);
	int count = 0;
	if(iter != rankDic->end())
	{
		std::map<int, SkillNode> * skillNode = &iter->second;
		std::map<int, SkillNode>::iterator it = skillNode->begin();

		for (;it != skillNode->end();it++)
		{
			if (it->second.formationInfo->getId() >= 17){break;}
			++count;
		}
	}
	*/
	return count;
}

LayerNode * FormationView::getView( int position )
{
	LayerNode *pListLayer = new LayerNode();
	CCSize itemSize = CCSizeMake(POSX(126), POSX(100));
	pListLayer->init();
	pListLayer->setContentSize(itemSize);
	pListLayer->setvisibleSize(itemSize);

	std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::FORMATION);
	if(iter != rankDic->end())
	{
		int count = 0;
		std::map<int, SkillNode> * skillNode = &iter->second;
		std::map<int, SkillNode>::iterator it = skillNode->begin();
		
		for (;it != skillNode->end();it++)
		{
			if (count == position){break;}
			if (it->second.formationInfo->getId() >= 17){break;}
			++count;
		}

		UpGradeInfo *info = new UpGradeInfo;
		//UpGradeInfo info;
		info->id = it->second.formationInfo->getId();
		info->lev = it->second.formationInfo->lev;
		info->active = it->second.formationInfo->active;
		std::map<int,UpGradeInfo *>::iterator iter = _posIDMap.find(position);
		if (iter != _posIDMap.end())
		{
			CC_SAFE_DELETE(iter->second); // LH0712LEAK
			_posIDMap.erase(position);
		}
		_posIDMap.insert(make_pair(position,info));

		CCPoint pos  = CCPointZero;
		int index = it->second.formationInfo->getId();

		SpriteNode *pListLayerSprite = new SpriteNode();
		char path[64] = {0};
		sprintf(path,"formation/formation_%d.png",index);
		if ( !pListLayerSprite->initWithSpriteFrameName(path) )
		{
			CCLog("newloc sprite node error!");
			pListLayerSprite->release();
		}
		else
		{
			pListLayerSprite->setAnchorPoint(CCPointZero);
			pos = pListLayerSprite->getPosition();
			pListLayer->addChild(pListLayerSprite,0,0);
			pListLayerSprite->release(); // LH0712LEAK
		}

		SpriteNode *pListSpriteLight = new SpriteNode();
		if ( !pListSpriteLight->initWithSpriteFrameName("formation/formation_ontouch.png") )
		{
			CCLog("newloc sprite node error!");
		}
		pListSpriteLight->setAnchorPoint(CCPointZero);
		pListSpriteLight->setIsVisible(false);
		pListSpriteLight->setPosition(ccp(pos.x-POSX(4),pos.y-POSX(4)));
		pListLayer->addChild(pListSpriteLight,2,2);
		pListSpriteLight->release(); // LH0712LEAK

		if (info->active)
		{
			SpriteNode *pListSpriteActivated = new SpriteNode();
			if ( !pListSpriteActivated->initWithSpriteFrameName("formation/formation_activated.png") )
			{
				CCLog("newloc sprite node error!");
			}
			pListSpriteActivated->setAnchorPoint(CCPointZero);
			pListSpriteActivated->setIsVisible(true);
			//CCPoint pos = pListLayerSprite->getPosition();
			pListSpriteActivated->setPosition(ccp(pos.x-POSX(4),pos.y-POSX(4)));
			pListLayer->addChild(pListSpriteActivated,1,1);
			pListSpriteActivated->release(); // LH0712LEAK
			_curActivatedItemPos = position;
		}
		else
		{
			if (pListLayer->getChildByTag(1))
			{
				pListLayer->removeChildByTag(1,true);
			}			
		}

	}
	else
	{
		return NULL;
	}
	return pListLayer;
}

void FormationView::onItemClickListener( LayerNode *itemCell, int position )
{
	_curSelectedItemPos = position;
	
	if (_curSelectedItemPos == _curActivatedItemPos)
	{
		EnableActivateButton(false);
	}
	else
	{
		EnableActivateButton(true);
	}
	
	// LH0713LEAK
// 	if (_curSelectedItem)
// 	{
// 		_curSelectedItem->release();
// 	}

	//_curSelectedItem = itemCell;

	SkillProxy* _skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	std::map<int, FormationInfo*> info;
	std::map<int, SkillNode>::iterator iter = _skillProxy->_formationDic->begin();
	for(; iter != _skillProxy->_formationDic->end(); ++iter)
	{
		if(iter->second.formationInfo)
		{
			info.insert(make_pair(iter->first, iter->second.formationInfo));
		}
	}
	int _curWatchFormation = _posIDMap[position]->id;

	createFormationList(0,_curWatchFormation,info);

	showFormationInfo(_curWatchFormation);

	CCMutableArray<LayerNode *> * pListNodes = _pListView->getChilds();
	
	if (_curLightItemPos != -1)
	{
		LayerNode * pLightLayer = pListNodes->getObjectAtIndex(_curLightItemPos);
		if (pLightLayer)
		{
			if (pLightLayer->getChildByTag(2))
			{
				pLightLayer->getChildByTag(2)->setIsVisible(false);
			}
		}
	}
	if (itemCell)
	{
		if (itemCell->getChildByTag(2))
		{
			itemCell->getChildByTag(2)->setIsVisible(true);
		}
	}

	_curLightItemPos = position;
	
	/*
	if (_curLightItem)
	{
		if (_curLightItem->getChildByTag(2))
		{
			_curLightItem->getChildByTag(2)->setIsVisible(false);
		}
	}
	if (itemCell)
	{
		if (itemCell->getChildByTag(2))
		{
			itemCell->getChildByTag(2)->setIsVisible(true);
		}
		_curLightItem = itemCell;
	}
	*/
}

void FormationView::onItemTouchListener( LayerNode *itemCell, int position )
{
}

void FormationView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{
}

void FormationView::setHighLight( int tag, bool isHighLight )
{
	if(tag < 0)
	{
		return;
	}

	_highLightTag = tag;
	if(getIconSpritesArray()->count() <= tag)
	{
		return;
	}

	FormationSprite *highLightSprite = getIconSpritesArray()->getObjectAtIndex(tag);
	if(highLightSprite)
	{
		highLightSprite->setIsHighLight(isHighLight);
	}
}

void FormationView::onClickActivateFormation(CCObject *pSender)
{
	if (_curSelectedItemPos == -1)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("ZX6"),ccc3(12,223,25),1);
		return;
	}
	if (_posIDMap.find(_curSelectedItemPos) != _posIDMap.end())
	{
		if (_posIDMap[_curSelectedItemPos]->active)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("ZX5"),ccc3(12,233,25),1);
			return;
		}
	}

	// send request
	CCMD311 cmd;
	cmd.a_formationId = (uint16)_curWatchFormation;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void FormationView::showFormationInfo(int curWatchFormation)
{
	SkillVo * skillVo = SkillManager::Instance()->getSkill(curWatchFormation);
	if (skillVo)
	{
		if (!_formInfoLayer)
		{
			_formInfoLayer = new LayerNode;
			_formInfoLayer->setContentSize(CCSizeMake(POSX(600),POSX(30)));
		}
		_formInfoLayer->removeAllChildrenWithCleanup(true);
		char str[32] = {0};
		// name
		sprintf(str,ValuesUtil::Instance()->getString("ZX7").c_str(),skillVo->name.c_str());
		CCLabelTTF * pTextName = CCLabelTTF::labelWithString(str,CCSizeMake(POSX(100),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextName->setColor(ccc3(255,215,25));
		pTextName->setAnchorPoint(CCPointZero);
		pTextName->setPosition(ccp(POSX(0),POSX(0)));
		_formInfoLayer->addChild(pTextName,0,0);

		// level
		memset(str,0,sizeof(str));
		int level = 0;
		SkillProxy* _skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
		std::map<int, FormationInfo*> info;
		std::map<int, SkillNode>::iterator iter = _skillProxy->_formationDic->find(_curWatchFormation);
		if(iter != _skillProxy->_formationDic->end())
		{
			level = iter->second.formationInfo->lev;
		}
		sprintf(str,ValuesUtil::Instance()->getString("ZX8").c_str(),level);
		CCLabelTTF * pTextLev = CCLabelTTF::labelWithString(str,CCSizeMake(POSX(60),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextLev->setColor(ccc3(244,244,244));
		pTextLev->setAnchorPoint(CCPointZero);
		pTextLev->setPosition(ccp(POSX(110),POSX(0)));
		_formInfoLayer->addChild(pTextLev,0,1);

		// describe
		CCLabelTTF * pTextDes = CCLabelTTF::labelWithString(skillVo->des.c_str(),CCSizeMake(POSX(400),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextDes->setColor(ccc3(12,233,25));
		pTextDes->setAnchorPoint(CCPointZero);
		pTextDes->setPosition(ccp(POSX(200),POSX(0)));	
		_formInfoLayer->addChild(pTextDes,0,2);

		if (!_formInfoLayer->getParent())
		{
			_formInfoLayer->setPosition(CCPOINT_FORMATION_INFO);
			_pContainer->addChild(_formInfoLayer);
		}
	}
}

void FormationView::showMerhInfo(int merhID)
{
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<int ,PlayerInfoVo>::iterator iter = list->find(merhID);
	PlayerInfoVo infoVo;
	if (iter != list->end())
	{
		infoVo = iter->second;
		 
		if (!_merhInfoLayer)
		{
			_merhInfoLayer = new LayerNode;
			_merhInfoLayer->setContentSize(CCSizeMake(POSX(300),POSX(30)));
		}
		_merhInfoLayer->removeAllChildrenWithCleanup(true);

		char str[32] = {0};
		// name 
		memset(str,0,sizeof(str));
		sprintf(str,ValuesUtil::Instance()->getString("ZX7").c_str(),infoVo.playerBaseInfo.name.c_str());
		CCLabelTTF * pTextName = CCLabelTTF::labelWithString(str,CCSizeMake(POSX(190),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextName->setColor(ColorUtil::getMerchColor(infoVo.playerBaseInfo.color));
		pTextName->setAnchorPoint(CCPointZero);
		pTextName->setPosition(ccp(POSX(50),POSX(0)));	
		_merhInfoLayer->addChild(pTextName,0,0);

		// level
		memset(str,0,sizeof(str));
		sprintf(str,ValuesUtil::Instance()->getString("ZX8").c_str(),infoVo.playerBaseInfo._lev);
		CCLabelTTF * pTextLev = CCLabelTTF::labelWithString(str,CCSizeMake(POSX(60),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextLev->setColor(ccc3(244,244,244));
		pTextLev->setAnchorPoint(CCPointZero);
		pTextLev->setPosition(ccp(POSX(250),POSX(0)));	
		_merhInfoLayer->addChild(pTextLev,0,1);

		// career
		memset(str,0,sizeof(str));
		sprintf(str,"CAR%d",infoVo.playerBaseInfo.career);
		CCLabelTTF * pTextCareer = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(str).c_str(),CCSizeMake(POSX(60),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextCareer->setColor(ccc3(240,133,25));
		pTextCareer->setAnchorPoint(CCPointZero);
		pTextCareer->setPosition(ccp(POSX(330),POSX(0)));
		_merhInfoLayer->addChild(pTextCareer,0,2);

		// attack point
		memset(str,0,sizeof(str));
		sprintf(str,ValuesUtil::Instance()->getString("ZX9").c_str(),infoVo.figureBaseInfo.attPoint);
		CCLabelTTF * pTextAttPoint = CCLabelTTF::labelWithString(str,CCSizeMake(POSX(200),POSX(30)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
		pTextAttPoint->setColor(ccc3(12,233,25));
		pTextAttPoint->setAnchorPoint(CCPointZero);
		pTextAttPoint->setPosition(ccp(POSX(410),POSX(0)));
		_merhInfoLayer->addChild(pTextAttPoint,0,3);

		if (!_merhInfoLayer->getParent())
		{
			_merhInfoLayer->setPosition(CCPOINT_MERH_INFO);
			_pContainer->addChild(_merhInfoLayer);
			_merhInfoLayer->release(); // LH0709
		}
	}
}

void FormationView::EnableActivateButton(bool var)
{
	if (_pContainer)
	{
		CCMenu * pActivateBtn = (CCMenu *)_pContainer->getChildByTag(TAG_BTN_ACTIVATE);
		if (pActivateBtn)
		{
			CCMenuItemImage* pBtnImage = (CCMenuItemImage*)pActivateBtn->getChildByTag( TAG_BTN_IMG_ACTIVATE );
			if(pBtnImage)
			{
				pBtnImage->setIsEnabled(var);
				
			}
		}
	}
}

void FormationView::specialHandlerForInit()
{
	_curSelectedItemPos = _curActivatedItemPos;
	onItemClickListener(NULL , _curSelectedItemPos);
}

CCNode * FormationView::getNewHandItem( int id )
{
	if(id == 98) 
	{
		if (_pContainer)
		{
			return _pContainer->getChildByTag(1);
		}		
	}
	else if (id == 6)
	{
		if (_pContainer)
		{
			return _pContainer->getChildByTag(0);
		}
	}
	else if (id == 7)
	{
		if (_pContainer)
		{
			return _pContainer->getChildByTag(13);
		}
	}
	
	

	return NULL;
}

CCRect & FormationView::addSelectedItems()
{
	if (!_pContainer)
	{
        CCRect tmpRect = CCRectMake(0,0,0,0);
		return  tmpRect;
	}

	CCPoint pos = ccp(0,0);
	CCSize size= CCSizeMake(0,0);

	CCSprite *pBgSprite = CCSprite::spriteWithSpriteFrameName("peiyang/bg_kuang.png");
	if(pBgSprite)
	{
		pBgSprite->setAnchorPoint(CCPointZero);
		pBgSprite->setPosition(CCPOINT_BTN_SELECT);
		_pContainer->addChild(pBgSprite);

		pos = getScreenPos(pBgSprite);
		size = pBgSprite->getContentSize();
	}

	CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName("peiyang/gou1.png");
	if(pIconSprite)
	{
		pIconSprite->setAnchorPoint(CCPointZero);
		pIconSprite->setPosition(CCPOINT_BTN_SELECT);
		pIconSprite->setTag(TAG_BTN_GOU);
		pIconSprite->setIsVisible(getIsSelected());
		_pContainer->addChild(pIconSprite , 1);
	}
	
	CCLabelTTF * pText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("ZX10").c_str() , CCSizeMake(POSX(150) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(24));
	pText->setColor(ccc3(233,133,25));
	pText->setPosition(ccp(pBgSprite->getPosition().x + POSX(115) , pBgSprite->getPosition().y + POSX(15)));
	_pContainer->addChild(pText , 1);

    CCRect tmpRect = CCRectMake(pos.x , pos.y , size.width , size.height);
	return tmpRect;
}

void FormationView::onSelectedChange(CCObject * pSender)
{
	if (!_pContainer)
	{
		return;
	}
	
	setIsSelected(!getIsSelected());

	bool bVar = getIsSelected();

	CCSprite *pIconSprite = (CCSprite *)_pContainer->getChildByTag(TAG_BTN_GOU);
	if (pIconSprite)
	{
		pIconSprite->setIsVisible(bVar);
	}
	
	showAttackOrder(bVar);
}

void FormationView::showAttackOrder(bool bVar)
{
	if (!_pContainer)
	{
		return;
	}

	for (int i = FORMATION_ORDER_1 ; i< FORMATION_ORDER_1+5 ; i++)
	{
		_pContainer->removeChildByTag(i , true);
	}	

	if (!bVar)
	{
		return;
	}	

	CCMutableArray<FormationSprite *> * pArray = getIconSpritesArray();
	if (!pArray)
	{
		return;
	}

	int tag = 8;
	int index = 1;
	for (tag = 8 ; tag < 17 ; tag++)
	{
		FormationSprite *pFormSprite = pArray->getObjectAtIndex(tag);
		if (pFormSprite && pFormSprite->getChildByTag(TAG_HEAD_ITEM))
		{
			char path[128] = {0};
			sprintf(path , "formationOrder/%d.png" , index);
			CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName(path);
			if (pIconSprite)
			{
				pIconSprite->setPosition(ccp(POINT_FORMATION_ICON_1.x + FLOAT_FORMATION_ICON - POSX(10) + ((tag-8) / 3) * FLOAT_FORMATION_ICON_DISTANCE, 
					POINT_FORMATION_ICON_1.y + FLOAT_FORMATION_ICON - POSX(10) - ((tag-8) % 3) * FLOAT_FORMATION_ICON_DISTANCE));
				pIconSprite->setTag(FORMATION_ORDER_1 + index - 1);
				_pContainer->addChild(pIconSprite , 5);
				++index;
			}
		}		
	}	
}

FormationView::~FormationView()
{
	ViewManager::getInstance()->formationView = 0;

	std::map<int, UpGradeInfo*>::iterator it = _posIDMap.begin();
	for (;it != _posIDMap.end(); it++)
	{
		CC_SAFE_DELETE(it->second);
	}
	_posIDMap.clear();

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/formation/res_formation_1.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/formation/res_formation_2.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/formation/res_formationOrder.plist");
}