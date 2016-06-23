
#ifndef _FIGHTLAYER_H_
#define _FIGHTLAYER_H_
#include "cocos2d.h"
#include "BaseType.h"
#include "view/scene/components/LiveThing.h"
#include "model/scene/vo/NPCVo.h"
#include "FocusNode.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
using namespace cocos2d;

class FightLayer : public LayerNode{

public :
	    int32 _type  ;
		int32 _battleType ;	//战斗类型   0= pve 1 =排位赛 2= 擂台赛 3= 资源田 4= pk 5= 组队pve 
	    CCSprite * _peratingSP; 
		CCPoint formationPos[18]; //阵型坐标

		// PlayerVo，NPCVo未完成，暂用固定数组，完成之后用Dictionary实现
		//cocos2d::CCMutableDictionary<char*, cocos2d::CCSprite*> *_elementDic;
		//std::vector<cocos2d::CCSprite *> _elementVector;
		cocos2d::CCMutableDictionary<int, cocos2d::CCSprite *> *_elementDic;
public :

	FightLayer();
	~FightLayer(){
	};
	 static FightLayer* getInstance();
	 virtual bool init();
     void resize();
	 void  initUI();
	 void addListener();
	 void generateFormationPos();
	 void loadFormation();   
	 void loadBtn();
	 void showRound(int32 r);
	 LiveThing*	getLiveThing(int32 type,int32 id);
	 LiveThing*  getNPC(int32 id){return 0;}     
	 LiveThing*  getPlayer(int32 id){return 0;}       //这边需要佣兵系统的接口了
	 
	 // 暂定方法，待PlayerVo,NPCVo等完成之后重新更改
	 cocos2d::CCSprite *addPlayer(cocos2d::CCSprite *playerSprite, int id);
	 cocos2d::CCSprite *addNPC(cocos2d::CCSprite *npcSprite, int id);

	 cocos2d::CCSprite *addNPC2(NPCVo* monster, int id);

	 void stopActions(); // 停止所有sprite的动作

	 void showResult(int result, int typeBattle, SCMD13D *pReward, SCMD3B1 *pReport);



	 virtual void registerWithTouchDispatcher();

	 bool ccTouchBegan(CCTouch* touch, CCEvent* event);

	 LAYER_NODE_FUNC(FightLayer);
	 
	 void reset();
	 void outOfFight();
private:
	CCLabelTTF *_roundLabel;
};


#endif