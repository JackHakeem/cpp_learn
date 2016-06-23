#ifndef _LIVEThing_h
#define _LIVEThing_h
#include "view/scene/components/Element.h"
#include "BaseType.h"
#include "string.h"
#include "model/com/vo/ResourceVo.h"
#include "utils/BitmapMovieClip.h"

#define DELTA_TIME_BLOOD_CHANGE (0.6f)

using namespace std;

class NPCChat;

struct _VOICE_
{
	std::string content;
	std::string name;
	int id;
	int style;
	
};

struct LiveThing_Backcall
{
	CCPoint tarpos;
};



class LiveThing  : public Element
{
private:
	struct HitData
	{
		float vx;
		float vy;
		bool isDead;
		HitData()
		{
			isDead = false;
			vx = 0;
			vy = 0;
		}
	};
public:
	virtual int getThingType() {return 1;}
public:
	
	int arraySeat;
	bool  hasDead;   
	string deadURL;  
	int nameY;
	int _level;
	int _hp;
	int _maxHp;
	int _mp;
	int _maxMp;
	int _energy;
	int _range;
	int _showHP;
	int skill1;			 
	int skill2;			 
	int skill3;         
	ResourceVo _res;
	std::map<int, BitmapMovieClip> _buffList; 
	BitmapMovieClip* livingMovieClip;
	//CCSprite* _shadow;
	_VOICE_ *_voice;

	NPCChat * _npcChat;


	float _mPercentage;
// 	cocos2d::CCProgressTimer * _pHPBarProgressTimer;
// 	cocos2d::CCProgressTimer * _pHPBarProgressTimer1;
	//LayerNode * _pHPLayer;


	enum
	{
		COLOR_NAMETEXT = 10,
	};

	enum
	{
		TAG_Shadow = 50,
	};

	enum
	{
		TAG_BLOOD_BG = 20,
		TAG_BLOOD,
		TAG_BitMapMovie,
	};

	enum
	{
		TAG_BLOOD_BG_ICON = 0,
		TAG_BLOOD_ICON_1,
		TAG_BLOOD_ICON_2,
		TAG_MP_BG_ICON = 10,
		TAG_MP_ICON,
	};

	enum
	{
		StepState_idle = 0,
		StepState_beHited,
		StipState_beCritHited,
		StepState_beKill,
	};//keving

	enum FightingTar
	{
		FightingTar_AoyiSkillName = 5553,
		FightingTar_SkillName = 5554,
		FightingTar_ImageTxt = 5555,
		FightingTar_ImageTxt2 = 5556,
		FightingTar_SpecialFontField,
	};

public :

	LiveThing();
	LiveThing(int hp, int maxhp, int mp, int maxmp);
	~LiveThing();
	   

	void loadDeadRes();   
	virtual void updateAction(bool repeat = true); 
	void removeDead();
	void configMC();
	void setShadowPos(CCPoint pos);
	CCPoint getShadowPos();
	int level();
	void level(int lv);
	int hp();
	void hp(int hp);
	int maxHp();
	void maxHp(int mh);
	int mp();
	void mp(int value);
	int maxMp();
	void maxMp(int value);
	int energy();
	void endPoint(int velue);
	int range();
	void range(int value);
	int showHP();
	virtual void showHP(bool value);
	ResourceVo* resource();
	void resource(ResourceVo& value);
	virtual bool toAttack();
	virtual bool toHited(bool iscrit = false);
	bool has0hp();
	void addMC(int type, BitmapMovieClip* effectMC ,int vx, int vy);
	BitmapMovieClip* getMC(int type);
	void removeAllMC();
	void removeMC(int type, bool clean = false);
	bool isLeader();
	virtual void dispose();
	virtual void toShade(bool value);

	void speak(_VOICE_ *_voice);
	virtual void shutup();
	virtual void updateInfo();
	void onTweenComplete(CCNode* n, void* data);
	void beHitedActionAfter(HitData data);//kevine
	void beHitedActionBefore(CCNode* n, void* data);
	void toStand();

	void loadHPMPBar();
	void updateHPBar(float time,float percent);
	void updateHPBarColor(ccTime dt);
	void updateMPBar(float time,float percent);

	void step(ccTime dt);//´¥¿Ø¼ÆÊ±keving
	void changeStepState(int stepState);//keving

	//Begin Kenfly 20121025
	void playSelectedEffect();
	//End Kenfly 20121025
public:
	
	int m_iStepState;//keving
	float m_fStepCounter;//keving
	LiveThing_Backcall m_cBackcall;//keving
};


#endif