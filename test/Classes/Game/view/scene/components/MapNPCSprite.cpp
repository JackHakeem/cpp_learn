#include "MapNPCSprite.h"
#include "CCTouchDispatcher.h"
#include "CCTexture2D.h"
#include "view/dialog/DialogMediator.h"
#include "control/AppFacade.h"
#include "mvc/Facade.h"
#include "Player.h"
#include "model/scene/vo/SceneConst.h"
#include "manager/BattleManager.h"
#include "BaseScene.h"
#include "utils/ScaleUtil.h"

MapNPCSprite::MapNPCSprite( NPCVo* pNPCVo )
{
	_npcVo = pNPCVo;

	CCSprite::init();
	//setContentSize( CCSizeMake( POSX(50), POSX(150) ) );
}

MapNPCSprite::~MapNPCSprite(void)
{

}