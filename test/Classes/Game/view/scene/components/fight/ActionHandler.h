#ifndef _ACTIONHANDLER_H_
#define _ACTIONHANDLER_H_
#include "socket/command/s13/SCMD132.h"
#include "view/scene/layer/FightLayer.h"
#include "model/battle/FightProxy.h"
#include "model/skill/vo/SkillVo.h"
#include "utils/effect/FightEffect.h"
#include "utils/flash/CCIEventDispatcher.h"

class ActionHandler:public CCNode, public CCIEventDispatcher
{
protected:

	//static ActionHandler *_instance;
private:

	ActionHandler();

	SCMD132::SCMD132Node1 _action;

public:
	bool _permitRun;
	float _rate;
	FightProxy * _fightProxy;

	LiveThing* m_firstHiter;
	//LiveThing* gmAttacker;
	LiveThing* m_attacker;

	SkillVo* m_skill;
	int _type;

	void type(int value);
	static  ActionHandler *getInstance() ;
	static void Release();
	void playOneAction(SCMD132::SCMD132Node1);
	void dispose();
	bool canRun();

	void execute();
	//void onStart();
	//void endHandler();

	void onStartAttack();
	void completeHandler();

	void soundPlay(ccTime dt);
	void playSkillEffect(int effectid);
	void HPMPBarHandler(float curHP,float curMP,LiveThing*);

	int _count;
	std::string _soundUrl;

public:
	void update(float dt);
	void switchUpdate(bool value);
	CCPoint getMCPos(LiveThing* src, CCSprite* ani);
public:
	enum FightEffectGroupState
	{
		FEGS_idleStart,//时间到播放攻击动作
		FEGS_idle,//时间到播放攻击动作
		FEGS_shining,//
		FEGS_attacking,//到第N帧时间播放特效，特效所对应的音效
		FEGS_MCing,//到0.2秒时间播放收击信息以及动作
		FEGS_aboutBeHit,//全部播放完毕后判断 是否有连续攻击动作：是播放攻击动作  否则下一组
		FEGS_fightEndDelay,//战斗结束要延缓一下才弹出UI
	};

	CC_PROPERTY(int, _FEGS, FEGS)
	float intervalCounter;
};


#endif
