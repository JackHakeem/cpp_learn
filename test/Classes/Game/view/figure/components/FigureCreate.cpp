#include "FigureCreate.h"
#include "model/figure/EquipmentManager.h"
#include "model/figure/vo/EquipmentVo.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/FigureCfgBaseVo.h"
#include "model/player/FigureBaseManage.h"
#include "utils/ValuesUtil.h"
#include "SkillView.h"
#include "manager/ViewManager.h"
#include "model/figure/LevelExpManage.h"
#include "NameUIPartialScrollView.h"
#include "BaseType.h"
#include "FigureView.h"
#include "utils/ScaleUtil.h"
#include "utils/ColorUtil.h"
#include "view/scene/components/Player.h"
#include "SkillItem.h"
#include "model/skill/vo/SkillType.h"
#include "manager/RenderManage.h"
#include "model/com/ResourceManage.h"
#include "model/com/vo/ResourceVo.h"
#include "utils/loader/KKAnimationFactory.h"
#include "utils/BitmapMovieClip.h"
#include "model/skill/SkillManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LevLimitConst.h"
#include "SkillUIPartialScrollView.h"
#include "LHLabelTTF.h"

FigureCreate * g_pFigureScrollView = 0;

FigureCreate::FigureCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_currentId = 0;
}

FigureCreate* FigureCreate::figureScrollViewWithCCRect(const CCRect& mRect)
{
	FigureCreate *pScrollView = new FigureCreate(mRect);
	if(pScrollView && pScrollView->init()){
		pScrollView->setIsTouchEnabled(false);//That may not be the touch
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

void FigureCreate::reNewScrollView()
{
	for (int i = 0; i < 16; i++)
	{
		if (g_pFigureScrollView->getLayerByTag(i))
		{
			g_pFigureScrollView->removeChildByTag(i,true);
		}
	}
	 
	g_pFigureScrollView->totalScreens = 0;

	int role_cnt = 0; 
	//std::map<int ,PlayerInfoVo>* list =  RoleManage::Instance()->mercList(); 
	//std::map<int ,PlayerInfoVo>::iterator it = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list =  RoleManage::Instance()->mercListEx(); 
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = list->begin();
	if(list)
	{
		role_cnt += list->size(); 
	}
	FigureView * pFigureView = (FigureView *)this->getParent();
	if (!pFigureView){return;}	
	memset(pFigureView->RoleID,0,sizeof(pFigureView->RoleID));
	for (int i = 0; i < role_cnt; i++)
	{
		pFigureView->RoleID[i] = it->second.figureBaseInfo.mercId;
		++it;
		g_pFigureScrollView->addLayerByTag(i);
	}
}

void FigureCreate::showEquipInfo()
{	
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* listEx = RoleManage::Instance()->mercListEx(); //  LH20121019listorder
	int page = 0;
	bool bool_checked = false;

	if (!g_pFigureScrollView){	return;}

	//ɾ���ͺ��Ӷ���?
	int curListNum = list->size();
	int curTotalPage = g_pFigureScrollView->totalScreens;
	if (curListNum < curTotalPage)
	{
		for (int i = curListNum; i < curTotalPage ; i++)
		{
			if (g_pFigureScrollView->getLayerByTag(i) && g_pFigureScrollView->getContentLayer())
			{
				 g_pFigureScrollView->getContentLayer()->removeChildByTag(i,true);
				 if (g_pFigureScrollView->totalScreens > 0){ --g_pFigureScrollView->totalScreens; }
				 if (g_pFigureScrollView->currentScreen > g_pFigureScrollView->totalScreens)
				 {
					 g_pFigureScrollView->currentScreen = g_pFigureScrollView->totalScreens;
				 }
				 if (_currentPage >= g_pFigureScrollView->totalScreens && _currentPage > 0)
				 {
					 --_currentPage;
				 }
			}			
		}
	}
	

	//����Ӷ��ҳ
	int index = 0;
	

	CCLayer * layer =0;
	std::map<int, PlayerInfoVo>::iterator iter;
	std::map<RoleManage::MercKeyIndex, PlayerInfoVo>::iterator iterEx;
	//for(iter = list->begin();iter != list->end(); ++iter)	

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist"); 
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");

	for(iterEx = listEx->begin();iterEx != listEx->end(); ++iterEx)
	{
		layer = g_pFigureScrollView->getLayerByTag(index);
		if (!layer)
		{
			if (index < list->size())
			{
				layer = g_pFigureScrollView->addLayerByTag(index);
				if (!layer)
				{
					continue;
				}
			}
			else
			{
				continue; // jae
			}
		}
		
		if (iterEx->second.playerBaseInfo.adLv)
		{
			//setIsReborn(iter->first,true);
			setIsReborn(iterEx->first.id,true);
		}
		else
		{
			//setIsReborn(iter->first,false);
			setIsReborn(iterEx->first.id,false);
		}

		CCLabelTTF * cTextName = CCLabelTTF::labelWithString(iterEx->second.playerBaseInfo.name.c_str(),
			CCSizeMake(POSX(120), POSX(48)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(24));
		cTextName->setAnchorPoint(CCPointZero);
		cTextName->setPosition(ccp(POSX(120 * index), POSX(10)));
		cTextName->setColor(ColorUtil::getMerchColor(iterEx->second.playerBaseInfo.color));
		if (layer->getChildByTag(index))
		{
			layer->removeChildByTag(index,true);
		}
		layer->addChild(cTextName,0,index);

		if (layer->getChildByTag(1999))
		{
			layer->removeChildByTag(1999,true);
		}
		if ( !iterEx->second.playerBaseInfo.isRole 
			&& (RoleManage::Instance()->roleLev()>=LevLimitConst::Limit_FigureLevBtn) )
		{
			CCMenuItemSprite *_bagButtonImg = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this, 
				menu_selector(AttributeLayer::clickButtonDismiss));
			CCMenu *_buttonBag = CCMenu::menuWithItems(_bagButtonImg, NULL);
			_buttonBag->setPosition(ccp(POSX(210), POSX(/*42*1+22+170*/252-10)));
			_buttonBag->setTouchLayer(TLE::WindowLayer_Figure);
			layer->addChild(_buttonBag,0, 1999);
			_bagButtonImg->setScale(0.8f);

			CCLabelTTF* pbagButtonLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString("RCR035").c_str(),
				CCSizeMake(POSX(200), POSX(20)), CCTextAlignmentCenter, "Arial", POSX(20));
			pbagButtonLabel->setPosition(
				ccp(_bagButtonImg->getContentSize().width/2, _bagButtonImg->getContentSize().height/2));
			_bagButtonImg->addChild(pbagButtonLabel, 0, 0);
			pbagButtonLabel->setColor(ccc3(254, 189, 0));
			//pbagButtonLabel->setScale(0.8f);
		}
		++index;
		
		if(!bool_checked)
		{
			bool_checked = true;
		}
		//int id = iter->first;
		int id = iterEx->first.id;
		currentId(id);
		_currentPage = page;
		showEquipInfo(id, page);
		++page;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist"); 
}

void FigureCreate::showEquipInfo(int role_id, int page) // ��ʾ��ɫ��Ϣ ����ɫID ҳ�룩
{
// 		std::map<int, EquiptmentItem*>::iterator iter = _equipDic.begin();
// 	 	for(; iter != _equipDic.end(); ++iter)
// 	 	{
// 	 		if(iter->second)
// 	 		{
// 	 			iter->second->removeAllChildrenWithCleanup(true);
// 	 			delete iter->second;
// 	 		}
// 	 	}

	//_equipDic.clear();

	setMercInfo(role_id,page);




	EquipmentVo* eqVo = EquipmentManager::Instance()->getEquipment(role_id/*_currentId*/);//_currentId The index of mercenaries were dismissed
	if(eqVo)
	{
		//for(int i = 0; i < eqVo->getAll(); i++)
		//{
		//	setEquipInfo(i, NULL, 0);
		//	continue;

		int nSitGrid = 0; 
		std::map<int, GoodsInfo>::iterator it;
		for (it = eqVo->m_equipments.begin();it != eqVo->m_equipments.end();it++)
		{
			if(it != eqVo->m_equipments.end())
			{

				GoodsInfo* info = &(it->second);
				setEquipInfo(nSitGrid, info, page); 
				++nSitGrid;
			}
		}

		//}
	}
}

void FigureCreate::setEquipInfo(int sitGrid, GoodsInfo* info, int page)
{
	if(/*_equipDic.find(sitGrid) == _equipDic.end()*/1) 
	{ 
		EquiptmentItem* eItem = new EquiptmentItem(info, sitGrid, page);
		//_equipDic[sitGrid] = eItem;

		CCLayer* layer = NULL;
		if (!g_pFigureScrollView)
		{
			eItem->release();
			return;
		}
		layer = g_pFigureScrollView->getLayerByTag(page); 
		if(layer)
		{
			if (layer->getChildByTag(sitGrid+TAG_EQUIP))
			{
				layer->removeChildByTag(sitGrid+TAG_EQUIP,true);
			}			
			layer->addChild(eItem, 2, sitGrid+TAG_EQUIP);
			eItem->release(); //Doyang1
		}
		else
		{
			eItem->release();
		}
	}
}

void FigureCreate::currentId(int value)
{
	_currentId = value;
}

int FigureCreate::currentId()
{
	return _currentId;
}

void FigureCreate::showModel(int figureID,int page)
{
	if (!g_pFigureScrollView)
	{
		return;
	}
	CCLayer * figureLayer = g_pFigureScrollView->getLayerByTag(page);
	if (!figureLayer)
	{
		return;
	}
	
	// load model
	CCSprite * pBaseSprite = new CCSprite();
	if (pBaseSprite)
	{
		pBaseSprite->init();
		pBaseSprite->setContentSize(CCSizeMake(50, 150));
		pBaseSprite->setPosition(ccp(POSX(210), POSX(400)));

		PlayerInfoVo* pInfo = RoleManage::Instance()->getMercenary(figureID);
		if ( !pInfo )	return;//jae note
		ResourceVo* pResVo = ResourceManage::Instance()->getRes(1, pInfo->playerBaseInfo.cloth);
        if(!pResVo) return; //Doyang 20120828
		CCAnimation * standAnimation = 0;
		char path[128] = {0};
		int frame_cnt = 5;
		std::string szFilePath("");
		//sprintf(path,"assets/res/%d/model-%d.plist",pResVo->id,pResVo->id);
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
		standAnimation = g_pKKAnimationFactory->registModelAnimation( szFilePath.c_str(), szFrameName.c_str(), frame_cnt, /*interval*3*/0.3 );	
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
	}
}

void FigureCreate::setMercInfo(int role_id,int page)
{
	if (!g_pFigureScrollView)
	{
		return;
	}
	CCLayer * figureLayer = g_pFigureScrollView->getLayerByTag(page);
	if (!figureLayer)
	{
		return;
	}
	//figureLayer->removeAllChildrenWithCleanup(true);
	for (int i = 0;i<100;i++)
	{
		if (figureLayer->getChildByTag(i))
		{
			figureLayer->removeChildByTag(i,true);
		}		
	}

	showModel(role_id,page);
	

	// merch properties
	CCLabelTTF * s_lev			= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("lev").c_str(),
		CCSizeMake(POSX(60), POSX(30)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(g_RoleFontSize+4));
	CCLabelTTF * s_threat		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("threat").c_str(),
		CCSizeMake(POSX(80), POSX(14)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(14));
		
	s_lev->setColor(ccc3(255,240,0));
	s_threat->setColor(ccc3(255,240,0));

	s_lev->setPosition(ccp(POSX(252), POSX(178)));
	s_threat->setPosition(ccp(POSX(182), POSX(40)));

	//figureLayer->addChild(s_lev,0,4);
	//figureLayer->addChild(s_threat,0,7);

	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<int ,PlayerInfoVo>::iterator it = list->find(role_id);
	if (it == list->end())
	{
		return;
	}
	
	char career[8];
	char lev[24];
	char force[8];
	std::string szforce = ValuesUtil::Instance()->getString("force");
	char threat[8];	

	bool isReborn = false;
	if (_isRebornDic.find(role_id) == _isRebornDic.end())
	{
		isReborn = false;
	}
	else
	{
		isReborn = _isRebornDic.find(role_id)->second;
	}

	sprintf(career,"CAR%d",it->second.playerBaseInfo.career);
	std::string levText = isReborn ? ValuesUtil::Instance()->getString("levad") : ("%d");
	sprintf(lev,levText.c_str(),it->second.playerBaseInfo._lev);
	sprintf(force," %d",it->second.figureBaseInfo.attPoint);
	szforce.append(force);
	sprintf(threat,"%d",it->second.playerBaseInfo.threat);
	
	// value
	CCLabelTTF * v_name		= CCLabelTTF::labelWithString(it->second.playerBaseInfo.name.c_str(),
		CCSizeMake(POSX(200), POSX(24)),
		CCTextAlignmentCenter,
		g_sSimHeiFont,
		POSX(24));
	CCLabelTTF * v_career		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(career).c_str(),
		CCSizeMake(POSX(72), POSX(24)),
		CCTextAlignmentCenter,
		g_sSimHeiFont,
		POSX(24));
	CCLabelTTF * v_lev			= CCLabelTTF::labelWithString(lev,
		CCSizeMake(POSX(160), POSX(24)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(24));
	CCLabelTTF * v_force		= CCLabelTTF::labelWithString(szforce.c_str(),
		CCSizeMake(POSX(200), POSX(18)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(18));
	CCLabelTTF * v_threat		= CCLabelTTF::labelWithString(threat,
		CCSizeMake(POSX(80), POSX(18)),
		CCTextAlignmentCenter,
		g_sSimHeiFont,
		POSX(18));
	
	v_name->setColor(ColorUtil::getMerchColor(it->second.playerBaseInfo.color)); // should depend
	v_career->setColor(ccc3(240,240,240));
	v_lev->setColor(ccc3(240,240,240));
	v_force->setColor(ccc3(12,233,25));
	v_threat->setColor(ccc3(240,240,240));

	v_name->setPosition(ccp(POSX(205), POSX(520)));
	v_career->setPosition(ccp(POSX(150), POSX(180)));
	v_lev->setPosition(ccp(POSX(230), POSX(180)));
	v_force->setPosition(ccp(POSX(152+10),POSX(252+15)));
	v_threat->setPosition(ccp(POSX(180), POSX(458)));

	//v_name->setAnchorPoint(CCPointZero);
	v_career->setAnchorPoint(CCPointZero);
	v_lev->setAnchorPoint(CCPointZero);
	v_force->setAnchorPoint(CCPointZero);
	v_threat->setAnchorPoint(CCPointZero);

	figureLayer->addChild(v_name,0,22);
	figureLayer->addChild(v_career,0,23);
	figureLayer->addChild(v_lev,0,TAG_ROLE_LEV);
	//figureLayer->addChild(v_threat);
	if (figureLayer->getChildByTag(29))
	{
		figureLayer->removeChildByTag(29,true);
	}
	figureLayer->addChild(v_force,0,29);
	//figureLayer->addChild(v_threat,0,30);
	v_force->setIsVisible(false);

	updateEXPInfo(role_id);

}

void FigureCreate::updateRoleLevel(int figureID)
{
	if (!g_pFigureScrollView)
	{
		return;
	}
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<int ,PlayerInfoVo>::iterator it = list->begin();
	int page = 0;
	while (it != list->end())
	{
		if (it->first == figureID)
		{
			break;
		}
		++page;
		++it;
	}
	CCLayer * figureLayer = g_pFigureScrollView->getLayerByTag(page);
	if (!figureLayer)
	{
		return;
	}
	int lev = it->second.playerBaseInfo._lev;
	CCLabelTTF * pLevLab = (CCLabelTTF *)figureLayer->getChildByTag(TAG_ROLE_LEV);
	if (pLevLab)
	{
		char buf[8] = {0};
        sprintf(buf, "%d", lev);
		pLevLab->setString(buf);
	}	
}

void FigureCreate::updateEXPInfo(int32 figureID)
{
	if (!g_pFigureScrollView)
	{
		return;
	}

//	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
//	std::map<int ,PlayerInfoVo>::iterator it = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = list->begin();
	int page = 0;
	while (it != list->end())
	{
		if (it->first.id == figureID)
		{
			break;
		}
		++page;
		++it;
	}
	CCLayer * figureLayer = g_pFigureScrollView->getLayerByTag(page);
	if (!figureLayer)
	{
		return;
	}

	bool isReborn = false;

	if (_isRebornDic.find(figureID) == _isRebornDic.end())
	{
		isReborn = false;
	}
	else
	{
		isReborn = _isRebornDic.find(figureID)->second;
	}

	char expExpMax[32];
	std::string szExp = isReborn ? ValuesUtil::Instance()->getString("adexp") : ValuesUtil::Instance()->getString("exp");
	int nlev = isReborn ? it->second.playerBaseInfo.adLv : it->second.playerBaseInfo._lev; 
	nlev = nlev == 0 ? 1 : nlev;
	int totalExp = isReborn ? it->second.playerBaseInfo.adExp : it->second.playerBaseInfo._exp;
	int nNeedExp = LevelExpManage::Instance()->getLevelExp(nlev)->needExp;
	int nCountExp = LevelExpManage::Instance()->getLevelExp(nlev)->countExp;
	sprintf(expExpMax," %d/%d",totalExp-nCountExp,nNeedExp); // max exp should depends on the merch level
	szExp.append(expExpMax);

	//CCLabelTTF * v_expExpMax	= CCLabelTTF::labelWithString(
	LHLabelTTF * v_expExpMax = new LHLabelTTF();
	v_expExpMax->initWithString(
		(char *)szExp.c_str(),
		CCSizeMake(POSX(480), POSX(30)),
		CCTextAlignmentCenter,
		g_sSimHeiFont,
		POSX(g_RoleFontSize+4) , POSX(0.5));

	v_expExpMax->setColor(ccc3(240,240,240));

	v_expExpMax->setPosition(ccp(POSX(210), POSX(151)));

	if (figureLayer->getChildByTag(31))
	{
		figureLayer->removeChildByTag(31,true);
	}
	figureLayer->addChild(v_expExpMax,4,31);
	v_expExpMax->release();

	// exp show
	float rate = (float)(totalExp-nCountExp)/(float)nNeedExp;
	CCSprite * sExpBg = CCSprite::spriteWithSpriteFrameName("figure/exp_bg.png");
	sExpBg->setAnchorPoint(CCPointZero);
	sExpBg->setPosition(ccp(POSX(12), POSX(140)));

	std::string sPath = isReborn ? ("assets/ui/figure/exp_ad.png") : ("assets/ui/figure/exp.png");
	CCProgressTimer * pEXPBarProgressTimer = CCProgressTimer::progressWithFile(sPath.c_str());
	if (pEXPBarProgressTimer)
	{
		//pEXPBarProgressTimer->setPercentage(0.0f);
		pEXPBarProgressTimer->setPosition(ccp(POSX(15), POSX(144)));
		pEXPBarProgressTimer->setType(CCProgressTimerType(2));
		pEXPBarProgressTimer->setAnchorPoint(CCPointZero);
		ccColor3B color = isReborn ? ccc3(0,0,255) : ccc3(0,255,0);
		pEXPBarProgressTimer->getSprite()->setColor(color);
		rate = rate >=100.0f ? 99.0f : rate;
		rate = rate <=0.0f ? 1.0f : rate;

		pEXPBarProgressTimer->setPercentage((float)(1.0f-rate) * 100.0f);
		/*
		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.1f, (float)(1.0f-rate) * 100.0f); 
		pEXPBarProgressTimer->runAction(pProgressTo);
		*/
	}

	/*
	CCSprite * sExp = CCSprite::spriteWithFile(sPath.c_str());
	sExp->setAnchorPoint(CCPointZero);
	sExp->setPosition(ccp(POSX(15), POSX(144)));
	sExp->setScaleX(rate);
	*/

	LayerNode * pLayer = new LayerNode();
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setIsRelativeAnchorPoint(true);
	pLayer->setContentSize(sExpBg->getTexture()->getContentSize());
	if (pLayer->getChildByTag(0))
	{
		pLayer->removeChildByTag(0,true);
	}
	pLayer->addChild(sExpBg,0,0);
	if (pLayer->getChildByTag(1))
	{
		pLayer->removeChildByTag(1,true);
	}
	pLayer->addChild(pEXPBarProgressTimer,1,1);
	if (figureLayer->getChildByTag(50))
	{
		figureLayer->removeChildByTag(50,true);
	}
	figureLayer->addChild(pLayer,0,50);
    //Doyang 20120708
    pLayer->release();
}

void FigureCreate::setIsReborn(int figureID,bool isReborn)
{
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	if (list->find(figureID) == list->end())
	{
		if (_isRebornDic.find(figureID) != _isRebornDic.end())
		{
			_isRebornDic.erase(figureID);
		}
		return;
	}
	
	std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	for (;iter!=list->end();iter++)
	{
		if (_isRebornDic.find(figureID) == _isRebornDic.end())
		{
			_isRebornDic.insert(make_pair(figureID,isReborn));
		}
		else
		{
			_isRebornDic.find(figureID)->second = isReborn;
		}
	}
}

void FigureCreate::showSkillInfo()
{
	if (!g_pFigureScrollView)
	{
		return;
	}
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");

	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	int nCount = 0;
	for (;iter!=list->end();iter++)
	{
		CCLayer * scrollLayer = (CCLayer *)g_pFigureScrollView->getLayerByTag(nCount);
		if (!scrollLayer)
		{
			return;
		}
		for (int i = TAG_SKILL;i<=TAG_SKILL+3;i++)
		{
			if (scrollLayer->getChildByTag(i))
			{
				scrollLayer->removeChildByTag(i,true);
			}
		}

		char path[64];
		// icon
		SpriteNode * icon = new SpriteNode();
		icon->initWithSpriteFrameName("new/skill_icon.png");
		icon->setAnchorPoint(CCPointZero);
		icon->setIsRelativeAnchorPoint(true);
		icon->setPosition(ccp(POSX(10), POSX(48)));
		scrollLayer->addChild(icon,0,TAG_SKILL);
		icon->release(); // LH0711LEAK

		{
			// grid1
			UpGradeInfo info;
			info.active = false;
			info.lev = 1;
			info.rank = SkillType::SKILL;
			info.id = iter->second.playerBaseInfo.skill2;

			SkillItem * si = new SkillItem(0, &info, 1);

			si->setAnchorPoint(CCPointZero);
			si->setPosition(ccp(POSX(84), POSX(28)));
			scrollLayer->addChild(si,0,TAG_SKILL+1);

			char path[128] = {0};
			SkillVo * pSkillVo = SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill2);
			sprintf(path,ValuesUtil::Instance()->getString("NAM12").c_str(),pSkillVo ? pSkillVo->name.c_str() : "?");
			//CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(
			LHLabelTTF * _nameTextEx = new LHLabelTTF();
			_nameTextEx->initWithString(
				path,
				CCSizeMake(POSX(100), POSX(46)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20) , POSX(0.5));
			
			_nameTextEx->setPosition(ccp(POSX(0), POSX(10)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			si->addChild(_nameTextEx,1,2);
			_nameTextEx->release();
			si->release();
			
		}

		
		{
			// grid2
			UpGradeInfo info;
			info.active = false;
			info.lev = 1;
			info.rank = SkillType::AOYI;
			info.id = iter->second.playerBaseInfo.skill1;

			SkillItem * si = new SkillItem(0, &info, 1);

			si->setPosition(ccp(POSX(194),POSX(28)));
			scrollLayer->addChild(si,0,TAG_SKILL+2);
			si->setAnchorPoint(CCPointZero);
			si->setIsRelativeAnchorPoint(true);

			char path[128] = {0};
			SkillVo * pSkillVo = SkillManager::Instance()->getSkill(iter->second.playerBaseInfo.skill1);
			sprintf(path,ValuesUtil::Instance()->getString("NAM11").c_str(),pSkillVo ? pSkillVo->name.c_str() : "?");
			//CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(
			LHLabelTTF * _nameTextEx = new LHLabelTTF();
			_nameTextEx->initWithString(
				path,
				CCSizeMake(POSX(100), POSX(46)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20) , POSX(0.5));
			_nameTextEx->setPosition(ccp(POSX(0),POSX(10)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			si->addChild(_nameTextEx,1,2);
			_nameTextEx->release();
			si->release();
		}

		// grid3
		SpriteNode * cell = 0;// = new SpriteNode();
		int skill;
		SpriteNode * item = 0;// = new SpriteNode();
		//CCLabelTTF *_nameTextEx = 0;
		LHLabelTTF *_nameTextEx = 0;

		cell = new SpriteNode();
		cell->initWithSpriteFrameName("pack/unlock.png");
		cell->setAnchorPoint(CCPointZero);
		cell->setIsRelativeAnchorPoint(true);
		cell->setPosition(ccp(POSX(300),POSX(28)));
		scrollLayer->addChild(cell,0,TAG_SKILL+3);
		//skill3
		skill = iter->second.playerBaseInfo.skill3;
		if (skill)
		{
			memset(path,0,sizeof(path));
			item = new SpriteNode();
			//sprintf(path,"skill/%d.png",skill);
			//item->initWithSpriteFrameName(path);
			//LH20130110
			sprintf(path,"assets/icon/skill/%d.png",skill);
			item->initWithFile(path);

			item->setAnchorPoint(ccp(0.5,0.5));
			CCSize size = cell->getContentSize();
			item->setPosition(ccp(size.width/2,size.height/2));
			item->setIsRelativeAnchorPoint(true);
			cell->addChild(item,0,1);
			cell->setContentSize(item->getTexture()->getContentSize());
			item->release();
		}
		std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
		std::map<int, std::map<int, SkillNode> >::iterator it = rankDic->find(SkillType::PASSVIE);
		if(it != rankDic->end())
		{
			std::map<int, SkillNode> * skillNode = &it->second;
			if (!skillNode->empty())
			{
				std::string strSkill3name("");
				int skill3 = iter->second.playerBaseInfo.skill3;
				strSkill3name = skill3	? SkillManager::Instance()->getSkill(skill3)->name : "";
				sprintf(path,ValuesUtil::Instance()->getString("NAM13").c_str(),strSkill3name.c_str());
			}
			else
			{
				sprintf(path,ValuesUtil::Instance()->getString("NAM3").c_str());
			}
		}
		
		//_nameTextEx = CCLabelTTF::labelWithString(
		_nameTextEx = new LHLabelTTF();
		_nameTextEx->initWithString(
			path,
			CCSizeMake(POSX(100), POSX(46)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20) , POSX(0.5));
		_nameTextEx->setPosition(ccp(POSX(2), POSX(10)));
		_nameTextEx->setColor(skill ? ccc3(12,233,25) : ccc3(100,100,100));
		_nameTextEx->setAnchorPoint(CCPointZero);
		_nameTextEx->setIsRelativeAnchorPoint(true);
		cell->addChild(_nameTextEx,1,2);
		_nameTextEx->release();
		//_nameTextEx->release();
		cell->release();
		
		++nCount;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
}

void FigureCreate::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

// bool FigureCreate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
// {
// 	setTouchState(TouchState_0);
// 	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
//	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
// 	for (int i = 0;i<6;i++)
// 	{
// 		EquiptmentItem * ei = (EquiptmentItem *)g_pFigureScrollView->getLayerByTag(g_pFigureScrollView->currentScreen-1)->getChildByTag(i);
// 		if (!ei)
// 		{
// 			continue;
// 		}
// 		CCPoint eqPos = getScreenPos(ei);
// 		CCSize sz = ei->getContentSize();
// 		if (CCRect::CCRectContainsPoint(CCRectMake(eqPos.x,eqPos.y,sz.width,sz.height),touchPoint))
// 		{
// 			ei->onMouseDownHandler(touchPoint);
// 		}
// 	}
// 	g_pFigureScrollView->ccTouchBegan(pTouch,pEvent);
// 	
// 
// 	return TRUE;
// }

// void FigureCreate::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
// {
// 	g_pFigureScrollView->ccTouchMoved(pTouch,pEvent);
// }

void FigureCreate::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	if ((touchPoint.x - preTouchPoint.x) > 2.0f)
	{
		// train board
		TrainView * pTrainView = ViewManager::getInstance()->trainView;
		if ( pTrainView && pTrainView->getisPop() )
		{
			if (currentScreen<=2)
			{
				this->moveToPage(currentScreen);
				return;
			}
		}
	}

	int newX = (int)touchPoint.x;

	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
		SkillView * sv = ViewManager::getInstance()->_skillView;
		if (sv)
		{
			sv->addSkillCellAndItem();
		}
		PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
		if (pv)
		{
			pv->loadItems(false);
		}
		FigureMainView * fmv = ViewManager::getInstance()->figureView;
		if (fmv)
		{
			if (fmv->_figureV)
			{
				if (	fmv->_figureV->_attrLayer)
				{
					fmv->_figureV->_attrLayer->loadItems();
				}
			}
		}

		// train board
		TrainView * pTrainView = ViewManager::getInstance()->trainView;
		if ( pTrainView && pTrainView->getisPop() )
		{
			pTrainView->roleItemClickHandler( currentScreen-1 );
		}
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		// train board
		TrainView * pTrainView = ViewManager::getInstance()->trainView;
		if ( pTrainView && pTrainView->getisPop() )
		{
			if (currentScreen>2)
			{
				this->moveToPreviousPage();
				pTrainView->roleItemClickHandler( currentScreen-1 );
			}
			else
			{
				this->moveToPage(currentScreen);
			}
		}
		else
		{
			this->moveToPreviousPage();
		}
		// refresh peiyang and skill panel
		SkillView * sv = ViewManager::getInstance()->_skillView;
		if (sv)
		{
			sv->addSkillCellAndItem();
		}
		PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
		if (pv)
		{
			pv->loadItems(false);
		}
		FigureMainView * fmv = ViewManager::getInstance()->figureView;
		if (fmv)
		{
			if (fmv->_figureV)
			{
				if (	fmv->_figureV->_attrLayer)
				{
					fmv->_figureV->_attrLayer->loadItems();
				}
			}
		}
	}
	else
	{
		this->moveToPage(currentScreen);	
	}	
}

void FigureCreate::setSkillHightLight(int index)
{
	CCSize size;

	CCSprite * pHightLight = (CCSprite *)this->getChildByTag(TAG_Skill_HightLight);
	if (!pHightLight)
	{
		pHightLight = new CCSprite();
		bool var = pHightLight->initWithSpriteFrameName("figure/select.png");
		if (var)
		{
			size = pHightLight->getContentSize();
			pHightLight->setTag(TAG_Skill_HightLight);
			pHightLight->setIsVisible(!!index);
			this->addChild(pHightLight , 5);
			pHightLight->release();
		}
	}
	else
	{
		size = pHightLight->getContentSize();
		pHightLight->setIsVisible(!!index);
	}	

	if (!pHightLight)	{		return;	}

	if (!index)	{		return;	}

	CCLayer * pScrollLayer = (CCLayer *)g_pFigureScrollView->getLayerByTag(0);
	if (!pScrollLayer)	{		return;	}
	CCSprite * pSkillNode = (CCSprite *)pScrollLayer->getChildByTag(TAG_SKILL + index);
	if (!pSkillNode)	{		return;	}	

	CCPoint pos = pSkillNode->getPosition();
	pHightLight->setPosition(ccp(pos.x + size.width/2 - POSX(5), pos.y + size.height/2 - POSX(5)));
	
}

FigureCreate::~FigureCreate()
{
	
    std::map<int, EquiptmentItem*>::iterator equipIt;
    for(equipIt = _equipDic.begin();
         equipIt != _equipDic.end();
        ++ equipIt)
    {
        //CC_SAFE_DELETE((*equipIt).second);
		if (equipIt->second)
		{
			equipIt->second->removeFromParentAndCleanup(true);
		}
    }
    _equipDic.clear();
  

	if (g_pSkillScrollView)
	{
		g_pSkillScrollView->removeFromParentAndCleanup(true);
		g_pSkillScrollView = 0;
	}

}

void FigureCreate::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	if ((touchPoint.x - preTouchPoint.x) > 2.0f)
	{
		// train board
		TrainView * pTrainView = ViewManager::getInstance()->trainView;
		if ( pTrainView && pTrainView->getisPop() )
		{
			if (currentScreen<=2)
			{
				//this->moveToPage(currentScreen);
				return;
			}
		}
	}

	CCUIPartialScrollView::ccTouchMoved(pTouch, pEvent);
}

bool FigureCreate::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	return CCUIPartialScrollView::ccTouchBegan(pTouch, pEvent);
}
