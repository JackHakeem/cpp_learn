#include "DropCheckView.h"
#include "CustomComboBox.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "EqItem.h"
#include "view/equipmentDrop/DropMediator.h"
#include "manager/ViewManager.h"
#include "utils/TipHelps.h"

int lvBox[6] = {20,40,60,80,90,100};

DropCheckView::DropCheckView()
{
	_curLevIndex = 0;
	_curTypeIndex = 0;
	_pListView = 0;
	_levComboBox = 0;
	_typeComboBox = 0;
}

bool DropCheckView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(ccp(0,0));
	
	//this->setContentSize(CCSizeMake(POSX(860), POSX(600)));
//	this->setPopContentSize(this->getContentSize());
	//
//	key = 0;//PopEventName::MAP;
//	setNeedBg(NeedBg_NO);
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(125), POSX(640-600)),ccp(0,0),
		CCSizeMake(POSX(850-125), POSX(600-75)));
	this->addChild(_bg1, DropCheckViewZ_bg1, DropCheckViewTAG_bg1);
	_bg1->release();
	//
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(135), POSX(640-590)),ccp(0,0),
		CCSizeMake(POSX(830-135), POSX(590-90)));
	this->addChild(_bg2, DropCheckViewZ_bg2, DropCheckViewTAG_bg2);
	_bg2->release();
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, DropCheckViewZ_blackBG, DropCheckViewTAG_blackBG);
	//
	_levComboBox = CustomComboBox::customComboBoxWithCCRect(CCRectMake(POSX(0), POSX(0), POSX(80), POSX(70)));
	_levComboBox->initWithParam(this, callfuncND_selector(DropCheckView::levSelectHandler), 0);
	_levComboBox->m_pri = TLE::IntervalLayer_eqdrop;
	this->addChild(_levComboBox, DropCheckViewZ_levComboBox, DropCheckViewTAG_levComboBox);
	_levComboBox->setPosition(ccp(POSX(300-80/2), POSX(640-150)));

	//
	_typeComboBox = CustomComboBox::customComboBoxWithCCRect(CCRectMake(POSX(0), POSX(0), POSX(80), POSX(70)));
	_typeComboBox->initWithParam(this, callfuncND_selector(DropCheckView::typeSelectHandler), 0);
	_typeComboBox->m_pri = TLE::IntervalLayer_eqdrop;
	this->addChild(_typeComboBox, DropCheckViewZ_typeComboBox, DropCheckViewTAG_typeComboBox);
	_typeComboBox->setPosition(ccp(POSX(660-80/2), POSX(640-150)));
	//
	
	for (int i = 0; i < 6; i++)
	{
		char str[20];
		sprintf(str, ValuesUtil::Instance()->getString("DC001").c_str(), lvBox[i]);
		_levComboBox->dataProvider(lvBox[i], str);//getIndexByCrastalLev(lvBox[i])
	}
	//
	_typeComboBox->dataProvider(0, ValuesUtil::Instance()->getString("DC002").c_str());
	_typeComboBox->dataProvider(1, ValuesUtil::Instance()->getString("DC003").c_str());
	//
	{
		CustomComboBox* box = _levComboBox;
		CCSize cellsize = CCSizeMake(80, 70);
		float offsetX = 20.0f;
		CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		CCMenuItemSprite *pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			box,
			menu_selector(CustomComboBox::moveToPreviousPageClick) );
		pDirectItem->setPosition( ccp(box->getPosition().x+POSX(-cellsize.width-offsetX), box->getPosition().y+POSX(cellsize.height/2)) );
		CCMenu* pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( box->m_pri );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect, DropCheckViewZ_direct, DropCheckViewTAG_direct1 );

		// right direct image btn
		pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			box,
			menu_selector(CustomComboBox::moveToNextPageClick) );
		CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
		pS->setFlipX( true );
		pS = (CCSprite*)pDirectItem->getSelectedImage();
		pS->setFlipX( true );
		pDirectItem->setPosition( ccp(box->getPosition().x+POSX(cellsize.width*2+offsetX), box->getPosition().y+POSX(cellsize.height/2)) );
		pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( box->m_pri );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect, DropCheckViewZ_direct, DropCheckViewTAG_direct2 );
	}
	//
	{
		CustomComboBox* box = _typeComboBox;
		CCSize cellsize = CCSizeMake(80, 70);
		float offsetX = 20.0f;

		CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		CCMenuItemSprite *pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			box,
			menu_selector(CustomComboBox::moveToPreviousPageClick) );
		pDirectItem->setPosition( ccp(box->getPosition().x+POSX(-cellsize.width-offsetX), box->getPosition().y+POSX(cellsize.height/2)) );
		CCMenu* pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( box->m_pri );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect, DropCheckViewZ_direct, DropCheckViewTAG_direct3 );

		// right direct image btn
		pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			box,
			menu_selector(CustomComboBox::moveToNextPageClick) );
		CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
		pS->setFlipX( true );
		pS = (CCSprite*)pDirectItem->getSelectedImage();
		pS->setFlipX( true );
		pDirectItem->setPosition( ccp(box->getPosition().x+POSX(cellsize.width*2+offsetX), box->getPosition().y+POSX(cellsize.height/2)) );
		pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
		pMenuDirect->setTouchLayer( box->m_pri );
		pMenuDirect->setPosition( CCPointZero );
		this->addChild( pMenuDirect, DropCheckViewZ_direct, DropCheckViewTAG_direct4);
	}
	//ccp(POSX(135), POSX(640-590))
	_pListView = EqCreate::listViewWithCCRect(CCRectMake(POSX(135+((830-135)-(815-155))/2 ), POSX(640-590), POSX(815-155), POSX(575-165)), false);
	_pListView->setIsRelativeAnchorPoint(true);
	_pListView->setAnchorPoint(CCPointZero);
	_pListView->setSpacingVertical(10.0f);
	_pListView->m_pri = TLE::IntervalLayer_eqdrop;
	_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pListView->getPosition(), this->getPosition()));//getScreenPos(this, true)
	_pListView->setOnItemActionListener(this);
	this->addChild(_pListView, DropCheckViewZ_ListView, DropCheckViewTAG_ListView);
	_pListView->release();
	//
	//
	if (_typeComboBox)
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(DropCheckView::dispear) );
		_btnX->setPosition(ccp(POSX(875), POSX(640-50)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(_typeComboBox->m_pri);
		this->addChild(buttonMenu, DropCheckViewZ_btnX, DropCheckViewTAG_btnX);
	}
	//
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/equipmentdrop/res_equipmentdrop.plist");
	SpriteNode* pTitle = new SpriteNode();
	pTitle->initWithSpriteFrameName("equipmentdrop/0.png");
	pTitle->setPosition(ccp(POSX(960/2), POSX(640-70)));
	this->addChild(pTitle, DropCheckViewZ_title, DropCheckViewTAG_title);

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/equipmentdrop/res_equipmentdrop.plist");
	return true;
}
/**
	* 设置查看装备的初始条件（显示武器）
	* @param level 水晶等级
	* @param type	装备类型索引
	* 
	*/		
void DropCheckView::setDefaultEqs(int lev, int typeIndex)
{
	startListener();
	getIndexByCrastalLev(lev);
	_curTypeIndex = typeIndex;
	_levComboBox->setselectedIndex(lvBox[_curLevIndex]);//_curLevIndex
	_typeComboBox->setselectedIndex(_curTypeIndex);
	createEqList(lvBox[_curLevIndex],_curTypeIndex);//_curLevIndex
}

void DropCheckView::startListener()
{
	//if(_levComboBox && !_levComboBox.hasEventListener(Event.CHANGE)){
	//	_levComboBox.addEventListener(Event.CHANGE,levSelectHandler);
	//}
	//if(_typeComboBox && !_typeComboBox.hasEventListener(Event.CHANGE)){
	//	_typeComboBox.addEventListener(Event.CHANGE,typeSelectHandler);
	//}
}
		
/**
	* 根据水晶等级段，设置下拉表的默认选项
	* @param lev
	* 
	*/		
int DropCheckView::getIndexByCrastalLev(int lev)
{
	if(lev <= 20){
		_curLevIndex = 0;
	}else if(lev > 20 && lev <= 40){
		_curLevIndex = 1;
	}else if(lev > 40 && lev <= 60){
		_curLevIndex = 2;
	}else if(lev > 60 && lev <= 80){
		_curLevIndex = 3;
	}else{//武器最高等级为90级，水晶等级大于90级时，显示90级的武器
		_curLevIndex = 4;
	}
	return _curLevIndex;
}



/**
	* 创建装备列表 
	* @param levIndex 	等级索引
	* @param typeIndex 类型索引
	* 
	*/			
void DropCheckView::createEqList(int lev, int typeIndex)
{
	//var eqs:Array = getEquips(levIndex,typeIndex);
	m_dstEQItem.clear();
	getEquips(lev, typeIndex, m_dstEQ);

		
	buildItems();
	//_eqCreate.buildItems(eqs);
}

/**
	* 装备数组（按品质、装备类型、职业排序）
	* @param levIndex 	等级索引
	* @param typeIndex 类型索引
	* @return 
	* 
	*/		
void DropCheckView::getEquips(int lev, int typeIndex, std::vector<GoodsBasic*>& dstEQ)
{
	//g_pGoodsManager->getEquips(id);

	//var arr:Array = [];
	//var lev:int = _levComboBox.getItemAt(levIndex).lev;
	dstEQ.clear();
	if(typeIndex == 0)
	{
		g_pGoodsManager->getEquips(lev,5,m_dstEQ);
	}
	else
	{
		g_pGoodsManager->getEquips(lev,1,dstEQ);
		g_pGoodsManager->getEquips(lev,2,dstEQ);
		g_pGoodsManager->getEquips(lev,3,dstEQ);
		g_pGoodsManager->getEquips(lev,4,dstEQ);
		g_pGoodsManager->getEquips(lev,6,dstEQ);
	}
	//arr.sortOn(["equip_type","career_id"],Array.NUMERIC);
}

#include "model/config/ConfigManager.h"
void DropCheckView::buildItems()
{
	//PS:把委托任务条目都去掉begin (测试部s需求)
	std::vector<GoodsBasic*>::iterator it = m_dstEQ.begin();
	while (it != m_dstEQ.end())
	{
		vector<std::string> _dropInfoArr;
		ConfigManager::splitStringByCharacterEx((*it)->drop_from, "|", _dropInfoArr);
		int sceneId = atoi(_dropInfoArr[0].c_str());
		if (sceneId == 1)//委托
		{
			it = m_dstEQ.erase(it);
		}
		else
			it++;
	}
	//end
	for (int i = 0; i < m_dstEQ.size(); i++)
	{
		EqItem* pItem = new EqItem();
		pItem->init(m_dstEQ[i]);
		m_dstEQItem.push_back(pItem);
	}

	_pListView->setAdapter(this);	
	
	for (int i = 0; i < m_dstEQItem.size(); i++)
	{
		EqItem* pItem = m_dstEQItem[i];
		if (pItem)
			pItem->release();
	}
}

int DropCheckView::getCount()
{
	return m_dstEQ.size();
}

LayerNode * DropCheckView::getView( int position )
{
	if (position <= (m_dstEQItem.size()-1) && position >= 0)
		return m_dstEQItem[position];
	else
		return 0;
}

void DropCheckView::levSelectHandler(CCNode *pNode, void *pData)
{
	if(_levComboBox->getselectedIndex() != _curLevIndex)
	{
		_curLevIndex = _levComboBox->getselectedIndex();
		createEqList(lvBox[_curLevIndex],_curTypeIndex);
	}
}
		
void DropCheckView::typeSelectHandler(CCNode *pNode, void *pData)
{
	if(_typeComboBox->getselectedIndex() != _curTypeIndex)
	{
		_curTypeIndex = _typeComboBox->getselectedIndex();
		createEqList(lvBox[_curLevIndex], _curTypeIndex);
	}		
}

//void DropCheckView::onEnter()
//{
//	this-> setIsTouchEnabled (true);
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::IntervalLayer_eqdrop-10, true);
//	CCLayer::onEnter();
//}

void DropCheckView::onExit()
{
	this->setIsTouchEnabled (false);
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

//bool DropCheckView::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//	return true;
//}

void DropCheckView::dispear(CCObject* pSender)
{
	DropCheckView* eqview = (DropCheckView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_eqdrop);
	if (eqview)
	{
		eqview->removeFromParentAndCleanup(true);
	}
}

void DropCheckView::onItemClickListener(LayerNode *itemCell, int position)
{
	if (position <= (m_dstEQItem.size()-1) && position >= 0)
	{
		EqItem* eqitem = m_dstEQItem[position];
		if (!eqitem)
			return;
		eqitem->myTip->rollOverHander();	
	}

}