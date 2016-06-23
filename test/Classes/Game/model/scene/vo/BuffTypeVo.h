#ifndef HLQS_BuffTypeVo_H_
#define HLQS_BuffTypeVo_H_

class BuffTypeVo
{
public:
	enum BuffActionTag
	{
		XUAN_YUN = 8504,
		NUQI = 8604,
	};

	const static int BUFF_TYPE_NULL = 0; // no
	const static int BUFF_TYPE_DOWN_PHY_DEFENCE = 1; // lower defense
	const static int BUFF_TYPE_UP_PHY_DEFENCE = 2; // strengthen defense
	/* *  stun buff*/
	const static int BUFF_TYPE_DIZZY = 3;
	/* *  BUFF cast trap effect*/
	const static int BUFF_TYPE_TRAP = 4; //
	/* * permanent increased 10% physical damage */
	const static int BUFF_TYPE_PASSIV_SKILL_01 = 60; //
	const static int BUFF_TYPE_PASSIV_SKILL_02 = 61; // permanent increase 10% of maximum life
	const static int BUFF_TYPE_PASSIV_SKILL_03 = 62; // permanent increase 10% of maximum life
	const static int BUFF_TYPE_PASSIV_SKILL_04 = 63; // permanent improve 10% of physical defense force
	const static int BUFF_TYPE_PASSIV_SKILL_09 = 64; // improve hit 10%
	const static int BUFF_TYPE_PASSIV_SKILL_10 = 65; // improve 10% crit
	const static int BUFF_TYPE_PASSIV_SKILL_11 = 66; // improve 10% evasion
	const static int BUFF_TYPE_PASSIV_SKILL_12 = 67; // improve 10% block
	const static int BUFF_TYPE_PASSIV_SKILL_21 = 68; // own thing and the attack attack 10%, and the control technology dimension dropped by 10%
	const static int BUFF_TYPE_PASSIV_SKILL_33 = 69; // permanent improve the attack by 10%

	/*bleeding**/
	const static int DOT_TYPE_BLEED					= 100;						
	/**burning*/
	const static int DOT_TYPE_BURN					= 101;						
	/*poisoning*/
	const static int DOT_TYPE_POISONING				= 102;

public:
	BuffTypeVo();
};

#endif