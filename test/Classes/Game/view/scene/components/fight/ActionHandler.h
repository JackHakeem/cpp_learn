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
		FEGS_idleStart,//ʱ�䵽���Ź�������
		FEGS_idle,//ʱ�䵽���Ź�������
		FEGS_shining,//
		FEGS_attacking,//����N֡ʱ�䲥����Ч����Ч����Ӧ����Ч
		FEGS_MCing,//��0.2��ʱ�䲥���ջ���Ϣ�Լ�����
		FEGS_aboutBeHit,//ȫ��������Ϻ��ж� �Ƿ������������������ǲ��Ź�������  ������һ��
		FEGS_fightEndDelay,//ս������Ҫ�ӻ�һ�²ŵ���UI
	};

	CC_PROPERTY(int, _FEGS, FEGS)
	float intervalCounter;
};


#endif
