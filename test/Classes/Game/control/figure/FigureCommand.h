#ifndef HLQS_FigureCommand_H_
#define HLQS_FigureCommand_H_
#include "mvc/SimpleCommand.h"
#include "model/figure/FigureProxy.h"
#include "socket/command/s30/SCMD309.h"
#include "socket/command/s34/SCMD349.h"

class FigureCommand: public SimpleCommand
{
public:

	enum{
		INIT_FIGURE_BASE_INFO = 0,		
		INIT_FIGURE_EQUIP_INFO,
		UPDATE_EQUIP_INFO,
		UPDATE_SKILL_INFO,
		FIGURE_SELECT,
		MERC_SKILL_EXCHANGE,
		REFRESH_WASH_VALUE,
		SAVE_WASH_VALUE,
		DELETE_WASH_VALUE,
		INIT_OTHER_BASE_INFO,
		INIT_SPIRIT_INFO,
	};

	FigureProxy* _figureProxy;

public:
	FigureCommand();
	~FigureCommand();
	virtual void execute(int32 command, char* data);
	void initFigureBaseInfo(SCMD309* scmd309);
	void initOtherBaseInfo(std::string playerName, SCMD309* scmd309);
	void sendChangeSkillRequest(int merID,int skillRank,int skillId);
	void initSpInfo(SCMD349* data);

};

#endif