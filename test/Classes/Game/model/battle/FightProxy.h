#ifndef _FIGHTPROXY_H_
#define _FIGHTPROXY_H_

#include "socket/command/s13/SCMD131.h"
#include "socket/command/s13/SCMD132.h"
#include "BaseType.h"
#include "mvc/Proxy.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
//#include "view/scene/components/DungeonAwardAction.h"
#include "socket/command/s13/SCMD133.h"
#include "model/scene/fight/vo/BattleData.h"

using namespace std;

class SCMD133;

class FightProxy : public Proxy{

public :
	                                                    	
		list<SCMD131Node> players;   //Participate in the combat role SCMD135Node
 
		//list<SCMD132*> fightPack ;    //132Combat process bag
		//GPHstd::vector<SCMD132*> fightPack ;    //132Combat process bag
		 std::vector<SCMD132> fightPack ; 
 
		 SCMD133 _fightRet ;         //Combat results
		 SCMD131 * _pveData;
	 
	    int32   playFactor; //Play factor for normal speed 1 
		
		int32 type ;		/* Combat type pvp, pve */
		int32 procid;		//Progress Numbers
		int32 id ;			//Monster combination Numbers
		//int32 count132; //132
		//int32 totalRound;
		int32 formation ;   // Their formation
		int32 oppositeFormation ;  //  Each other's formation
		
		bool playAgain;  // Whether playback
	 
		int32  battleId;  //The current fight ID

		bool _hasDungonAward;
		bool _fightSceneCreate;
		bool _hasTailStory;
		BattleData _bData;//KEVIN
		/*Create the battle layer*/
		bool fightLayerCreate ;
		/*Combat formation information is loaded*/
		bool fightDataCreate ;
		/*Resources is loaded*/
		bool fightResLoaded ;
		/*Packet is loaded*/
		bool fightPack133Loaded ;


		SCMD13D _fightReward;
		SCMD3B1 _battleReport;

		//bool _hasDungonAward;
		//DungeonAwardAction* dungeonAward;

		int _callCount;

		int _winMark;
public :
	FightProxy();
	virtual    ~FightProxy();
   	void setPVEData(char* data) ;
	SCMD131 * getPVEData();
    void addFightPack(SCMD132* scmd132) ;
	void setFightRet(SCMD133* scmd133);
	void setFightLayer();
	void showProcess() ;
	void beforeHandler();
	void afterHandler() ;
	bool getIsCanPlay();
	void removeElement() ;
	void fightReward(SCMD13D *pData);
	void battleReport(SCMD3B1 *pData);

	void fightStart();
	void fightExit();

	void setPVPData(char* data);
	void setPVEFight(int procId, int type);
	void setPVPFight(int type);
	void gotoFightScene();
	void clear();
};
#endif