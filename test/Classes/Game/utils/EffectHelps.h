#ifndef _EffectHelps_H_
#define _EffectHelps_H_

#include "BaseType.h"

#include "cocos2d.h"
#include "BitmapMovieClip.h"
#include "effect/TweenLiteObject.h"
#include "model/skill/vo/SkillVo.h"

USING_NS_CC;
class BitmapMovieClip;
class LiveThing;
class EffectHelps
{
public:
	EffectHelps()
	{
	}
	static const int DIZZY  = 1;  /**晕眩*/
	static const int MP_FULL = 2; /**奥义满之后*/
	static const int GM_EFFECT = 5;  /**共鸣*/	

public:
	static BitmapMovieClip* getSkillEffectMC( int resId, float interval = 0.1f );
	static TweenLiteObject* addBuffEffect( CCNode* hiter, int buffType, float delay = 0.2 );
	static BitmapMovieClip* getBuffEffect( int type );

	static TweenLiteObject* getSkillName(CCNode* sp, SkillVo& skill,float vx, float vy, float delay=0.2, float duration=1.2);
	static TweenLiteObject* getMCNameEffect(CCNode* sp, int mcName, float x, float y,/*startFun:Function,*/float delay=1.2f);
	

	static void getSkillNameEx(LiveThing* sp, SkillVo& skill, float vx, float vy, float delay, float duration);
	static void getMCNameEffectEx(LiveThing* sp, int mcName, float x, float y,/*startFun:Function,*/float delay=1.2f);
	static void getEffectEx(LiveThing* sp, bool iscrit, int damage, int value, float vx, float vy, float delay, float duration);
	static void getMPEffectEx(LiveThing* sp, int mp, float delay=0, float duration=0.2f, int diff=0);
	static void addBuffEffectEx(LiveThing* hiter, int buffType);
	static BitmapMovieClip* getBuffEffectEx(int type);
};
#endif