#include "FigureItemView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "model/com/ResourceManage.h"
#include "model/com/vo/ResourceVo.h"
#include "model/player/FigureBaseManage.h"
#include "model/player/vo/FigureCfgBaseVo.h"
#include "utils/loader/KKAnimationFactory.h"
#include "utils/BitmapMovieClip.h"
#include "RankEqItem.h"

#define FONT_SIZE (25)
FigureItemView::FigureItemView()
{
	_pRoleData = 0;
	_pRoleEquip = 0;
	_pRoleModel = 0;
}

FigureItemView::~FigureItemView()
{

}

bool FigureItemView::init()
{
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		CCSize size = CCSizeMake(POSX(370), POSX(480));
		this->setContentSize(size);

		//add top background
		CCUIBackground* pTopBg = new CCUIBackground;
		pTopBg->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, CCSizeMake(size.width, POSX(320)));
		pTopBg->setAnchorPoint(CCPointZero);
		pTopBg->setPosition(ccp(POSX(0.0f), POSX(160)));
		this->addChild(pTopBg);
		pTopBg->release();

		//add down background
		CCUIBackground* pDownBg = new CCUIBackground;
		pDownBg->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, CCSizeMake(size.width, POSX(150)));
		pDownBg->setAnchorPoint(CCPointZero);
		pDownBg->setPosition(ccp(POSX(0.0f), POSX(0.0)));
		this->addChild(pDownBg);
		pDownBg->release();

		//init node
		_pRoleData = new CCNode();
		_pRoleData->setAnchorPoint(CCPointZero);
		_pRoleData->setPosition(CCPointZero);
		this->addChild(_pRoleData);
		_pRoleData->release();

		_pRoleEquip = new CCNode();
		_pRoleEquip->setAnchorPoint(CCPointZero);
		_pRoleEquip->setPosition(CCPointZero);
		this->addChild(_pRoleEquip);
		_pRoleEquip->release();

		_pRoleModel = new CCNode();
		_pRoleModel->setAnchorPoint(CCPointZero);
		_pRoleModel->setPosition(CCPointZero);
		this->addChild(_pRoleModel);
		_pRoleModel->release();

		return true;
	} while (0);
	return false;
}

void FigureItemView::updateFigureData(const RankItemVo& data)
{
	do 
	{
		updateRoleData(data);
		updateRoleModel(data);
	} while (0);
}

void FigureItemView::updateEquipments(const std::vector<EquipItemVo>& equips)
{
	const float leftPos = 70;
	const float rightPos = 310;
	const float topPos = 420;
	const float dist = 100;
	const int index[7] = {0, 5, 3, 4, 2, 6, 1};
	const int type[7] = {0, 6, 1, 2, 3, 4, 5};
	const CCPoint pos[7] = {
		CCPointZero,
		ccp(POSX(leftPos), POSX(topPos)),
		ccp(POSX(leftPos), POSX(topPos - 1 * dist)),
		ccp(POSX(leftPos), POSX(topPos - 2 * dist)),
		ccp(POSX(rightPos), POSX(topPos)),
		ccp(POSX(rightPos), POSX(topPos - 1 * dist)),
		ccp(POSX(rightPos), POSX(topPos - 2 * dist))
	};

	do 
	{
		CC_BREAK_IF(! _pRoleEquip);
		_pRoleEquip->removeAllChildrenWithCleanup(true);

		//add equipment background
		char path[64];
		for (int i = 1; i <= 6; ++i)
		{
			sprintf(path, "new/grid_%d.png", i);
			SpriteNode* pBack = new SpriteNode();
			if (pBack)
			{
				if (pBack->initWithSpriteFrameName(path))
				{
					pBack->setPosition(pos[index[i]]);
					_pRoleEquip->addChild(pBack, 0, i);
					pBack->release();
				}
				else
				{
					CC_SAFE_DELETE(pBack);
				}
			}
		}
		std::vector<EquipItemVo>::const_iterator ix;
		for (ix = equips.begin(); ix != equips.end(); ++ix)
		{
			if (ix->type < 1 || ix->type > 6)
				continue;
			RankEqItem* item = new RankEqItem();
			CCNode* layer = _pRoleEquip->getChildByTag(type[ix->type]);
			if (item->init(*ix) && layer)
			{
				layer->addChild(item);
				item->release();
			}
			else
			{
				CC_SAFE_DELETE(item);
			}
		}

	} while (0);
}

void FigureItemView::updateRoleModel(const RankItemVo& data)
{
	do 
	{
		CC_BREAK_IF(! _pRoleModel);
		_pRoleModel->removeAllChildrenWithCleanup(true);
		//add model
		CCSprite* pBaseSprite = new CCSprite();
		CC_BREAK_IF(! pBaseSprite);
		CCSize size = this->getContentSize();

		FigureCfgBaseVo* pRoleVo = FigureBaseManage::Instance()->getMercBase(data.roleId);
		CC_BREAK_IF(! pRoleVo);

		pBaseSprite->init();
		pBaseSprite->setContentSize(CCSizeMake(POSX(50), POSX(150)));
		pBaseSprite->setPosition(ccp(size.width / 2.0f, POSX(200 + 50 + 150 / 2.0f)));

		ResourceVo* pResVo = ResourceManage::Instance()->getRes(1, pRoleVo->cloth);
		CC_BREAK_IF(! pResVo);

		CCAnimation* pStandAnimation = 0;
		char path[128] = "\0";
		int frameCnt = 5;
		std::string szFilePath("");
		sprintf(path, "assets/res/%d/stand-2.plist", pResVo->id);
		CC_BREAK_IF(! BitmapMovieClip::isFileExist(path));

		szFilePath.assign(path);
		sprintf(path, "%d/stand-%d", pResVo->id, 2);

		std::string szFrameName = std::string(path) + "-000%d.png";
		pStandAnimation = g_pKKAnimationFactory->registModelAnimation(szFilePath.c_str(), szFrameName.c_str(), frameCnt, 0.2);
		CC_BREAK_IF(! pStandAnimation);

		pBaseSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(pStandAnimation)));

		_pRoleModel->addChild(pBaseSprite);
		pBaseSprite->release();

		//add name label;
		CCLabelTTF* pNameLabel = CCLabelTTF::labelWithString(data.name.c_str(), CCSizeMake(POSX(400), POSX(FONT_SIZE + 2)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(FONT_SIZE));
		pNameLabel->setPosition(ccp(size.width / 2.0f, POSX(420)));
		pNameLabel->setColor(ccYELLOW);
		_pRoleModel->addChild(pNameLabel);

	} while (0);
}

void FigureItemView::updateRoleData(const RankItemVo& data)
{
	do 
	{
		ValuesUtil *pVU = ValuesUtil::Instance();
		CC_BREAK_IF(! _pRoleData || ! pVU);

		_pRoleData->removeAllChildrenWithCleanup(true);
		char msg[50] = "\0";

		sprintf(msg, pVU->getString("RK009").c_str(), data.lev);
		CCLabelTTF* pLevLabel = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(400), POSX(FONT_SIZE + 2)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(FONT_SIZE));
		CC_BREAK_IF(! pLevLabel);
		pLevLabel->setAnchorPoint(CCPointZero);
		pLevLabel->setColor(ccORANGE);
		pLevLabel->setPosition(ccp(POSX(20), POSX(105)));
		_pRoleData->addChild(pLevLabel);

		sprintf(msg, pVU->getString("RK010").c_str(), data.guild.c_str());
		CCLabelTTF* pGuildLabel = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(400), POSX(FONT_SIZE + 2)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(FONT_SIZE));
		CC_BREAK_IF(! pGuildLabel);
		pGuildLabel->setAnchorPoint(CCPointZero);
		pGuildLabel->setColor(ccORANGE);
		pGuildLabel->setPosition(ccp(POSX(20), POSX(60)));
		_pRoleData->addChild(pGuildLabel);

		if (data.type == 2) //fight rank
			sprintf(msg, pVU->getString("RK011").c_str(), data.grade);
		else if (data.type == 1) //renown rank
			sprintf(msg, pVU->getString("RK012").c_str(), data.grade);
		CCLabelTTF* pGradeLabel = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(400), POSX(FONT_SIZE + 2)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(FONT_SIZE));
		CC_BREAK_IF(! pGradeLabel);
		pGradeLabel->setAnchorPoint(CCPointZero);
		pGradeLabel->setColor(ccORANGE);
		pGradeLabel->setPosition(ccp(POSX(20), POSX(15)));
		_pRoleData->addChild(pGradeLabel);

	} while (0);
}