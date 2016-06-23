#include "CenterView.h"
#include "model/notice/NoticeManager.h"
#include "NoticeItem.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"

const float w_frame_bg1 = 730.0f;
const float h_frame_bg1 = 480.0f;
const float w_frame_bg2 = 700.0f;
const float h_frame_bg2 = 400.0f;
const float w_frame = 700.0f;
const float h_frame = 400.0f;
const int COUNTPAGE =  5;
const int TAG_PARENT_LAYER = 1001;
CenterView::CenterView()
{
	_type = 0;
	_noticeManager = g_pNoticeManager;
	_pListView = 0;
}

bool CenterView::init(int type, NoticeManager::NoteElmArr* arr)
{
	if (!LayerNode::init())
		return false;
	//初始化key
	key = 0;	

	_type = type;

	//CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCLayer *pParentLayer = new CCLayer();
	pParentLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setPosition(POS(ccp(115, 80), ScaleUtil::CENTER));
	this->addChild(pParentLayer, 0, TAG_PARENT_LAYER);
	pParentLayer->release();
	//float x = POSX(winsize.width - w_frame)/2.0f;
	//float y = 100;

	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();//POSX(winsize.width - w_frame_bg1)/2.0f, POSX(y)
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(0, 0), ccp(0,0), CCSizeMake(POSX(w_frame_bg1), POSX(h_frame_bg1)));
	_bg1->setAnchorPoint(CCPointZero);
	pParentLayer->addChild(_bg1, CenterViewZ_bg1, CenterViewTAG_bg1);
	//Doyang 20120712
	_bg1->release();
	//bg2
	CCUIBackground* _bg2 = new CCUIBackground();//POSX(winsize.width - w_frame_bg2)/2.0f, POSX(y+15)
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(w_frame_bg1 - w_frame_bg2)/2, POSX(15.0f)), ccp(0,0), CCSizeMake(POSX(w_frame_bg2), POSX(h_frame_bg2)));
	_bg2->setAnchorPoint(CCPointZero);
	pParentLayer->addChild(_bg2, CenterViewZ_bg2, CenterViewTAG_bg2);	
	//Doyang 20120712
	_bg2->release();
	//title
	CCLabelTTF* pLable_title = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NTC001").c_str(), CCSizeMake(POSX(200), POSX(30)),CCTextAlignmentCenter, "Arial", POSX(30));
	pLable_title->setAnchorPoint(CCPointZero);
	pLable_title->setColor(ccc3(254, 189, 0));
	pLable_title->setPosition(ccp(POSX(260), POSX(465)));//
	pParentLayer->addChild(pLable_title, CenterViewZ_title, CenterViewTAG_title);
	//list
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(w_frame_bg1 - w_frame_bg2)/2, POSX(15.0f), POSX(w_frame), POSX(h_frame)), false);
	_pListView->setIsRelativeAnchorPoint(true);
	_pListView->setAnchorPoint(CCPointZero);
	_pListView->setSpacingVertical(0);

	//_pListView->setClipLayerRect(CCRectMake(30+MAP_X_LEN, this->getPosition().y+90, 200+this->getPosition().x, 360));
	_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pListView->getPosition(), pParentLayer->getPosition()));//getScreenPos(this, true)
	_pListView->setOnItemActionListener(this);
	pParentLayer->addChild(_pListView, CenterViewZ_ListView, CenterViewTAG_ListView);
	_pListView->release();//Kenfly 20130125

	//Close button
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
	CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this, 
		menu_selector(CenterView::clickCloseHandler) );
	_btnClose->setPosition( ccp(POSX(w_frame_bg1), POSX(h_frame_bg1)) );

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0);
    buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_NoticeCenter);
	pParentLayer->addChild(buttonMenu, CenterViewZ_closeBtn, CenterViewTAG_closeBtn);



	reLocate();
	return true;
}

void CenterView::reLocate()
{
	clear();
	NoticeManager::NoteElmArr* arr = _noticeManager->getArrByType(_type);

	NoticeManager::NoteElmArr::iterator it;
	for (it = arr->begin(); it != arr->end(); it++)
	{
		NM_ELM_INFO info = *it;
		NoticeItem* ni = new NoticeItem();
		ni->init(&info, _type);
		ni->setAnchorPoint(CCPointZero);
		ni->setPosition(CCPointZero);
		_itemArr.push_back(ni);
	}

	//更新列表
	updateRes();

	//清除按钮
	if (arr->size() <= 0)
	{
		switch (_type)
		{
		case NoticeManager::ADD_FRI:
			{//清除友字按钮
				CCMenu* buttonMenu = (CCMenu*)LayerManager::sceneUILayer->getChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend);
				if (buttonMenu)
				{
					LayerManager::sceneUILayer->removeChildByTag(SceneUILayer::SceneUILayerTAG_btnFriend, true);
				}
			 //关闭面板
				clickCloseHandler(0);
			}
			break;
		}	
	}

}

void CenterView::clear()
{
	_itemArr.clear();
}

void CenterView::pageLayout(int32 now, int32 max)
{
	
}

void CenterView::updateRes()
{
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
	_pListView->setAdapter(this);
}

int CenterView::getCount()
{
	return _itemArr.size();
}

LayerNode * CenterView::getView( int position )
{
	if (position>=0 && position<_itemArr.size())
		return _itemArr[position];
	else
		return 0;
}

void CenterView::onItemClickListener( LayerNode *itemCell, int position )
{
	CCLog("click...position=%d", position);

	//this.dispatchEvent(new ParamEvent(GO_TO_NPC,_vo.id))
}




