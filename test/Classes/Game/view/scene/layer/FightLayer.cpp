#include "FightLayer.h"
#include "model/scene/vo/SceneConst.h"
#include "view/scene/components/BattlePlay.h"
#include "model/com/vo/ResourceVo.h"
#include "model/com/ResourceManage.h"
#include "../components/fight/FightEnd.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"


static FightLayer * m_pInstance = 0;

FightLayer::FightLayer(){

	this->reset();
}


FightLayer * FightLayer::getInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new FightLayer();
		if(m_pInstance && m_pInstance->init())
		{
			m_pInstance->setIsTouchEnabled(true);
			return m_pInstance;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return m_pInstance;
	}
}

void FightLayer::initUI(){
	//这里先加载一张背景图，实际要做阴影效果
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//CCSprite* fightBg= CCSprite::spriteWithFile("scene/battle/world.jpg");
	//CCSprite* fightBg= new CCSprite();
	//fightBg->initWithSpriteFrame("ui2.png", ccp(0, 0), ccp(0, 0), CCSizeMake(screenSize.width, screenSize.height));
	CCUIBackground* fightBg = new CCUIBackground();

	fightBg->initWithSpriteFrame("ui.png", ccp(0, 0), ccp(POSX(20), POSX(20)), CCSizeMake(screenSize.width, screenSize.height));
	//layer->addChild(_container1);

	//fightBg->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	this->addChild(fightBg,-95);
	//Doyang 20120712
	fightBg->release();
	this->loadFormation();
	this->loadBtn();
	this->addListener();
}

void FightLayer::loadFormation(){

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite * zhenfa1 = CCSprite::spriteWithFile("scene/battle/zhenfa.png");

	this->addChild(zhenfa1,-95);

	zhenfa1->setPosition(ccp(formationPos[4].x, screenSize.height - formationPos[4].y));

	CCSprite * zhenfa2 = CCSprite::spriteWithFile("scene/battle/zhenfa.png");

	this->addChild(zhenfa2,-95);
	zhenfa2->setPosition(ccp(formationPos[13].x, screenSize.height - formationPos[13].y));

	//这里还在加载一个阵法发光的动画

}

void FightLayer::loadBtn(){
}

void FightLayer::addListener(){
}

//生成阵型坐标点
void FightLayer::generateFormationPos(){

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center;
	center.x = screenSize.width/2;
	center.y = screenSize.height/2;
	float length = sqrt(screenSize.width*screenSize.width + screenSize.height * screenSize.height);
	float rateSin = ((float)screenSize.height)/length;
	float rateCos = ((float)screenSize.width)/length;

	formationPos[1].x = center.x + ((float)center.x)/5;
	formationPos[1].y = center.y + ((float)center.y)/5;
	formationPos[4].x = center.x + 2 * ((float)center.x)/5;
	formationPos[4].y = center.y + 2 * ((float)center.y)/5;
	formationPos[7].x = center.x + 3 * ((float)center.x)/5;
	formationPos[7].y = center.y + 3 * ((float)center.y)/5;

	formationPos[2].x = formationPos[1].x - rateSin * length/10;
	formationPos[2].y = formationPos[1].y + rateCos * length/10;
	formationPos[5].x = formationPos[2].x + ((float)center.x)/5;
	formationPos[5].y = formationPos[2].y + ((float)center.y)/5;
	formationPos[8].x = formationPos[5].x + ((float)center.x)/5;
	formationPos[8].y = formationPos[5].y + ((float)center.y)/5;

	formationPos[0].x = formationPos[1].x + rateSin * length/10;
	formationPos[0].y = formationPos[1].y - rateCos * length/10;
	formationPos[3].x = formationPos[0].x + ((float)center.x)/5;
	formationPos[3].y = formationPos[0].y + ((float)center.y)/5;
	formationPos[6].x = formationPos[3].x + ((float)center.x)/5;
	formationPos[6].y = formationPos[3].y + ((float)center.y)/5;

	formationPos[10].x = screenSize.width - formationPos[1].x;
	formationPos[10].y = screenSize.height - formationPos[1].y;
	formationPos[13].x = screenSize.width - formationPos[4].x;
	formationPos[13].y = screenSize.height - formationPos[4].y;
	formationPos[16].x = screenSize.width - formationPos[7].x;
	formationPos[16].y = screenSize.height - formationPos[7].y;

	formationPos[9].x = screenSize.width - formationPos[2].x;
	formationPos[9].y = screenSize.height - formationPos[2].y;
	formationPos[12].x = screenSize.width - formationPos[5].x;
	formationPos[12].y = screenSize.height - formationPos[5].y;
	formationPos[15].x = screenSize.width - formationPos[8].x;
	formationPos[15].y = screenSize.height - formationPos[8].y;

	formationPos[11].x = screenSize.width - formationPos[0].x;
	formationPos[11].y = screenSize.height - formationPos[0].y;
	formationPos[14].x = screenSize.width - formationPos[3].x;
	formationPos[14].y = screenSize.height - formationPos[3].y;
	formationPos[17].x = screenSize.width - formationPos[6].x;
	formationPos[17].y = screenSize.height - formationPos[6].y;

}




LiveThing*  FightLayer::getLiveThing (int type,int id) {
	if(type == SceneConst::PVE && id>9){
		return getNPC(id);
	}
	return getPlayer(id);
}


void FightLayer::showRound(int32 r){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	char  roundChar[ 20 ];  
	sprintf( roundChar, ValuesUtil::Instance()->getString("fi_r").c_str(), r );
	if(!_roundLabel)
	{
		_roundLabel = CCLabelTTF::labelWithString( roundChar, "Arial", 20 );     
		_roundLabel->setPosition(ccp(screenSize.width/2 , screenSize.height-30));
		this->addChild(_roundLabel,-94);
	}
	_roundLabel->setString(roundChar);
}



 
/****************************玩家处理*********************************/

// PlayerVo未写，暂时用Sprite代替
//public function addPlayerHandler(obj:Object):Player {
//	var playerVo:PlayerBaseVo = PlayerBaseVo(obj);
//	var player:Player = addPlayer(playerVo);
//	if(playerVo.path) {		//移动玩家
//		GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.CREATE_PALYER_FINISH, playerVo.path));
//	}
//	return player;
//}
//
//protected function addPlayer(playerVo:PlayerBaseVo):Player{
//	if(_elementDic[SceneConst.PLAYER_TYPE + playerVo.accountId.toString()]){	//重生
//		if(_role && playerVo.accountId != _role.id){	//不是自己 
//			removePlayer(playerVo.accountId);
//		}
//	}
//
//	var player:Player = new Player();
//	player.setPlayerVo(playerVo);
//	player.addEventListener(SceneConst.DEAD_EVENT,playerDeadHandler);
//	player.addEventListener(SceneConst.REMOVE_PLAYER_DEADBODY_EVENT,removePlayerDeadbodyHandler);
//	player.addEventListener(SceneConst.CHANGE_POSITION,playerLayout);
//
//	_elementDic[SceneConst.PLAYER_TYPE + playerVo.accountId.toString()] = player;
//	setElemenetPosition(playerVo.x,playerVo.y,player);
//	addElement(player);
//
//	this.dispatchEvent(new ParamEvent(ELEMENT_LAYOUT,{first:true,value:player}));
//
//	if(_isHidePlayer) {
//		player.hide();
//	}
//
//	return player;
//}

cocos2d::CCSprite *FightLayer::addPlayer(cocos2d::CCSprite *playerSprite, int id)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize playerSize = playerSprite->getContentSize();
	playerSprite->setAnchorPoint(CCPointZero);
	playerSprite->setPosition(ccp(formationPos[id - 1].x-playerSize.width/2,  winSize.height - formationPos[id - 1].y)) ;
	this->addChild(playerSprite,-94);
	_elementDic->setObject(playerSprite, id);
	//_elementVector.push_back(playerSprite);

	return playerSprite;
}

cocos2d::CCSprite *FightLayer::addNPC(cocos2d::CCSprite *npcSprite, int id)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize npcSize = npcSprite->getContentSize();
	npcSprite->setAnchorPoint(CCPointZero);
	npcSprite->setPosition(ccp(formationPos[id].x-npcSize.width/2,  winSize.height - formationPos[id].y)) ;
	this->addChild(npcSprite,-94);
	_elementDic->setObject(npcSprite, id);
	//_elementVector.push_back(npcSprite);

	return npcSprite;
}

void FightLayer::stopActions()
{
	//uint size = _elementDic->count();
	std::vector<int> allKeys = _elementDic->allKeys();
	std::vector<int>::iterator it;
	for(it = allKeys.begin(); it != allKeys.end(); ++it)
	{
		_elementDic->objectForKey(*it)->stopAllActions();
	}
	/*for(int i=0; i<size; ++i)
	{
		_elementVector[i]->stopAllActions();
	}*/
}

cocos2d::CCSprite * FightLayer::addNPC2( NPCVo* monster, int id )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//ResourceVo* res = ResourceManage::Instance()->getRes( 1, monster->getResId() );
	//std::string _ImageContain = "";
	//if ( res )
	//{
	//	_ImageContain = res->bodyUrl();

	//}
	//CCSprite* monsterSprite=CCSprite::spriteWithFile(_ImageContain.c_str());
	CCSprite* monsterSprite=CCSprite::spriteWithFile("assets/res/211/body.png");
	CCSize monsterSize = monsterSprite->getContentSize();
	monsterSprite->setAnchorPoint(CCPointZero);
	monsterSprite->setPosition(ccp(formationPos[id].x-monsterSize.width/2,  winSize.height - formationPos[id].y)) ;
	this->addChild(monsterSprite,-94);
	_elementDic->setObject(monsterSprite, id + 1);
	//_elementVector.push_back(npcSprite);

	return monsterSprite;
}

void FightLayer::showResult( int result, int typeBattle, SCMD13D *pReward, SCMD3B1 *pReport )
{
	FightEnd *pResultLayer = new FightEnd(result, pReward, pReport, typeBattle);
	if(!pResultLayer || !pResultLayer->init())
		return;
	pResultLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	pResultLayer->setAnchorPoint(CCPointZero);
	pResultLayer->setPosition(CCPointZero);
	pResultLayer->setIsRelativeAnchorPoint(true);
// 	if (this->getChildByTag(100))
// 	{
// 		this->removeChildByTag(100,true);
// 	}
	this->addChild(pResultLayer,0,100);
	pResultLayer->release();
}

bool FightLayer::init()
{
	return true;
}

void FightLayer::reset()
{
	_roundLabel = 0;
	this->removeAllChildrenWithCleanup(true);
	this->generateFormationPos();
	CCSprite* sp1 = BattlePlay::getInstance()->getBattleSprite();
	this->addChild(sp1);
	_elementDic = new cocos2d::CCMutableDictionary<int, cocos2d::CCSprite*>();
}

void FightLayer::outOfFight()
{
	this->reset();
	
}

void FightLayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::FightLayer, true);
}

bool FightLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::FightLayer");
	return false;
}
//LiveThing*  FightLayer::getNPC(int32 id){
//
//	
//}

//LiveThing*  FightLayer::getPlayer(int32 id){
//
//
//}
