#ifndef _RANKCOMMAND_H_
#define _RANKCOMMAND_H_

#include "mvc/SimpleCommand.h"
#include "model/ranking/RankingProxy.h"
#include "socket/command/s25/SCMD25C.h"
#include "socket/command/s25/SCMD25E.h"
#include "model/ranking/vo/RankItemVo.h"

class RankingCommand : public SimpleCommand
{
public:
    enum
    {
        REQUEST_RANKING_LIST = 0,
        UPDATE_RANKING_LIST,
        UPDATE_EQUIPS_INFO,
        REQUEST_SELECTED_EQUIP_INFO,
    };
public:
    RankingCommand();
    ~RankingCommand();
    virtual void execute(int32 command, char* data);
private:
    void updateRankingList(SCMD25C* packet);
    void updateEquipsInfo(SCMD25E* packet);
    void requestRankingList(int type);
    void requestSelectedEquipInfo(int position);

private:
    RankingProxy* _pRankProxy;
};

#endif
