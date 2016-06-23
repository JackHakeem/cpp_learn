#ifndef HLQS_Player_Animate_Type_h
#define HLQS_Player_Animate_Type_h

class PlayerAniType
{
public:
	PlayerAniType(){}
	virtual ~PlayerAniType(){}

public:
	enum _AniType
	{
		TYPE_LevelUp,
		TYPE_AutoFind,
		TYPE_RunBusiness,
	};
};

#endif