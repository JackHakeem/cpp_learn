#ifndef _STRENGVO_H_
#define _STRENGVO_H_

class StrengVo
{
public:
	StrengVo():hp(0),att(0),magicAtt(0),def(0),magicDef(0){};
	~StrengVo(){};

	int hp;				//life
	int att;		//Content attack
	int magicAtt;	//The attack
	int def;		//Thing to
	int magicDef;	//imitate
};

#endif