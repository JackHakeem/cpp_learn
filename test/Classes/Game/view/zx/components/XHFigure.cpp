#include "XHFigure.h"

#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/FigureCfgBaseVo.h"
#include "model/player/FigureBaseManage.h"
#include "utils/ValuesUtil.h"

#include "manager/ViewManager.h"

#include "BaseType.h"
#include "utils/ScaleUtil.h"
#include "view/scene/components/Player.h"

#include "model/skill/vo/SkillType.h"
#include "manager/RenderManage.h"
#include "model/com/ResourceManage.h"
#include "model/com/vo/ResourceVo.h"
#include "utils/loader/KKAnimationFactory.h"
#include "utils/BitmapMovieClip.h"
#include "manager/TouchLayerEnum.h"
#include "view/zx/ZXMediator.h"
#include "XHView.h"

XHFigure::XHFigure(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
}


XHFigure::~XHFigure()
{
   
}


XHFigure* XHFigure::figureScrollViewWithCCRect(const CCRect& mRect)
{
	XHFigure *pScrollView = new XHFigure(mRect);
	if(pScrollView && pScrollView->init()){
		pScrollView->setIsTouchEnabled(false);//That may not be the touch
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}


bool XHFigure::init()
{	
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* listEx = RoleManage::Instance()->mercListEx();
	int page = 0;
	bool bool_checked = false;

	int index = 0;
	for(std::map<RoleManage::MercKeyIndex, PlayerInfoVo>::iterator iterEx = listEx->begin();iterEx != listEx->end(); iterEx++, index++)
	{
		CCLayer* subLayer = this->getLayerByTag(index);
		if (!subLayer)
		{
			this->addLayerByTag(index);

			int id = iterEx->first.id;

			showModel(id, index);
			m_vPage2Figure[index] = id;
		}


	}


	return true;
}

int XHFigure::getCurScreenFigureId()
{
	if ( currentScreen<= 0)
		return 0;
	return m_vPage2Figure[currentScreen-1];
}

void XHFigure::showModel(int figureID, int page)
{
	CCLayer * figureLayer = this->getLayerByTag(page);
	if (!figureLayer)
	{
		return;
	}
	
	// load model
	SpriteNode * pBaseSprite = new SpriteNode();
	if (pBaseSprite)
	{
		pBaseSprite->init();
		//pBaseSprite->setContentSize(CCSizeMake(50, 150));
		pBaseSprite->setPosition(ccp(POSX(401-124-74/2)/2, POSX(505-186-72)/2));

		PlayerInfoVo* pInfo = RoleManage::Instance()->getMercenary(figureID);
		if ( !pInfo )	return;//jae note
		ResourceVo* pResVo = ResourceManage::Instance()->getRes(1, pInfo->playerBaseInfo.cloth);
        if(!pResVo) return; //Doyang 20120828
		CCAnimation * standAnimation = 0;
		char path[128] = {0};
		int frame_cnt = 5;
		std::string szFilePath("");
		sprintf(path,"assets/res/%d/stand-2.plist",pResVo->id,pResVo->id);
		if (BitmapMovieClip::isFileExist(path))
		{
			szFilePath.assign(path);
			memset((void *)path,0,sizeof(path));
			sprintf( path, "%d/stand-%d", pResVo->id, 2);
		}
		else
		{
			szFilePath.assign("assets/res/1/stand-2.plist");
			memset((void *)path,0,sizeof(path));
			sprintf( path, "%d/stand-%d", 1, 2);
		}
		std::string szFrameName = std::string(path) + "-000%d.png";
		standAnimation = g_pKKAnimationFactory->registModelAnimation( szFilePath.c_str(), szFrameName.c_str(), frame_cnt, 0.3 );	
		if (standAnimation)
		{
			pBaseSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(standAnimation)));
		}

		if (figureLayer->getChildByTag(TAG_MODEL))
		{
			figureLayer->removeChildByTag(TAG_MODEL,true);
		}
		figureLayer->addChild(pBaseSprite,0,TAG_MODEL);
		pBaseSprite->release();


		//find string info
		std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
		std::map<int ,PlayerInfoVo>::iterator itInfo = list->find(figureID);
		if (itInfo == list->end())
		{
			return;
		}
		//name
		{
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(itInfo->second.playerBaseInfo.name.c_str(), CCSizeMake(POSX(400), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(22));
			pLabel->setPosition(ccp(POSX(401-124-74/2)/2, POSX(35)));
			figureLayer->addChild(pLabel, 5);
			pLabel->setColor(ccc3(251, 216, 0));
		}
		//career
		{
			char career[8];
			sprintf(career,"CAR%d",itInfo->second.playerBaseInfo.career);
			char career_lv[50];
			sprintf(career_lv, "%s  Lv.%d", ValuesUtil::Instance()->getString(career).c_str(), itInfo->second.playerBaseInfo._lev);
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(career_lv, CCSizeMake(POSX(400), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(22));
			pLabel->setPosition(ccp(POSX(401-124-74/2)/2, POSX(15)));
			figureLayer->addChild(pLabel, 5);
			pLabel->setColor(ccc3(251, 216, 0));
		}

	}
}

void XHFigure::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_zx-1, true);
}



void XHFigure::refreshFigureEquipXH()
{
	ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
	if (pZXMediator)
	{
		std::map<int, int>::iterator it = m_vPage2Figure.find(currentScreen-1);
		if (it != m_vPage2Figure.end())
			pZXMediator->m_pXHView->showFigureXH(it->second);
		else
			pZXMediator->m_pXHView->showFigureXH(0);

	}
}

void XHFigure::handleTouchEndPagePre()
{
	refreshFigureEquipXH();
}

void XHFigure::handleTouchEndPageNext()
{
	refreshFigureEquipXH();
}

