#include "MessageFactoryManager.h"
#include "SocketCMDConst.h"

#include "socket/command/s10/SCMD102.h"
#include "socket/command/s10/SCMD107.h"
#include "socket/command/s13/SCMD131.h"
#include "socket/command/s13/SCMD132.h"
#include "socket/command/s13/SCMD133.h"
#include "socket/command/s13/SCMD135.h"
#include "socket/command/s16/SCMD161.h"
#include "socket/command/s16/SCMD163.h"
#include "socket/command/s16/SCMD165.h"
#include "socket/command/s16/SCMD167.h"
#include "../command/s31/SCMD310.h"
#include "../command/s31/SCMD312.h"
#include "../command/s31/SCMD318.h"
#include "../command/s31/SCMD31B.h"
#include "../command/s21/SCMD214.h"
 
#include "socket/command/s15/SCMD150.h"
#include "socket/command/s15/SCMD151.h"
#include "socket/command/s15/SCMD153.h"
#include "socket/command/s15/SCMD155.h"
#include "socket/command/s15/SCMD157.h"
#include "socket/command/s15/SCMD15A.h"
#include "socket/command/s15/SCMD15C.h"
#include "socket/command/s15/SCMD15E.h"
 
#include "socket/command/s35/SCMD352.h"
#include "socket/command/s35/SCMD35A.h"
#include "../command/s35/SCMD358.h"
#include "../command/s35/SCMD35C.h"
#include "../command/s35/SCMD354.h"
#include "../command/s11/SCMD11D.h"
#include "../command/s12/SCMD123.h"
#include "../command/s30/SCMD309.h"
#include "../command/s30/SCMD30A.h"
#include "../command/s11/SCMD11C.h"
#include "../command/s35/SCMD350.h"
#include "../command/s18/SCMD18A.h"
#include "../command/s18/SCMD185.h"
#include "../command/s18/SCMD186.h"
#include "../command/s19/SCMD19D.h"
#include "../command/s18/SCMD181.h"
#include "../command/s30/SCMD300.h"
#include "../command/s30/SCMD301.h"
#include "../command/s30/SCMD303.h"
#include "../command/s30/SCMD305.h"
#include "../command/s30/SCMD30C.h"
#include "../command/s30/SCMD30E.h"
#include "../command/s18/SCMD187.h"
#include "../command/s19/SCMD19F.h"
#include "../command/s18/SCMD183.h"
#include "../command/s32/SCMD323.h"
#include "../command/s2d/SCMD2D3.h"
#include "../command/s11/SCMD11A.h"
#include "../command/s11/SCMD118.h"
#include "../command/s31/SCMD31D.h"
#include "../command/s31/SCMD31F.h"
#include "../command/s17/SCMD172.h"
#include "../command/s31/SCMD319.h"
#include "../command/s35/SCMD35E.h"
#include "../command/s35/SCMD35F.h"
#include "../command/s2f/SCMD2FF.h"
#include "../command/s28/SCMD287.h"
#include "../command/s28/SCMD285.h"
#include "../command/s36/SCMD361.h"
#include "../command/s39/SCMD39D.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
#include "../command/s31/SCMD316.h"
#include "../command/s15/SCMD158.h"
#include "../command/s11/SCMD112.h"
#include "../command/s11/SCMD113.h"
#include "../command/s10/SCMD109.h"
#include "../command/s31/SCMD31A.h"
#include "../command/s31/SCMD314.h"
#include "../command/s29/SCMD295.h"
#include "../command/s29/SCMD29E.h"
#include "../command/s3c/SCMD3C8.h"
#include "../command/s1e/SCMD1EF.h"

#include "socket/command/s20/SCMD201.h"
#include "socket/command/s20/SCMD205.h"
#include "socket/command/s20/SCMD207.h"
#include "socket/command/s20/SCMD209.h"
#include "socket/command/s20/SCMD20b.h"
#include "socket/command/s20/SCMD20d.h"
#include "socket/command/s20/SCMD20F.h"
#include "socket/command/s21/SCMD211.h"
#include "socket/command/s21/SCMD213.h"
#include "socket/command/s21/SCMD216.h"

#include "../command/s2d/SCMD2D7.h"
#include "../command/s18/SCMD18B.h"
#include "../command/s2e/SCMD2E1.h"
#include "../command/s21/SCMD21F.h"
#include "../command/s18/SCMD188.h"

#include "../command/s18/SCMD18C.h"
#include "../command/s18/SCMD18D.h"
#include "../command/s18/SCMD18E.h"
#include "../command/s18/SCMD18F.h"
#include "../command/s17/SCMD17F.h"

#include "../command/s32/SCMD321.h"
#include "../command/s32/SCMD324.h"
#include "../command/s3d/SCMD3DB.h"
#include "../command/s11/SCMD11F.h"

#include "../command/s37/SCMD376.h"
#include "../command/s14/SCMD140.h"
#include "../command/s14/SCMD144.h"
#include "../command/s12/SCMD124.h"
#include "../command/s11/SCMD11B.h"
#include "../command/s12/SCMD120.h"
#include "../command/s24/SCMD24B.h"
#include "../command/s16/SCMD16F.h"
#include "../command/s17/SCMD17D.h"


#include "../command/s28/SCMD285.h"
#include "../command/s28/SCMD287.h"

#include "../command/s36/SCMD361.h"
#include "../command/s36/SCMD363.h"
#include "../command/s36/SCMD36C.h"
#include "../command/s36/SCMD36E.h"
#include "../command/s38/SCMD38C.h"
#include "../command/s13/SCMD13C.h"

#include "socket/command/s16/SCMD16D.h"
#include "../command/s1d/SCMD1DF.h"
#include "../command/s10/SCMD105.h"
#include "../command/s35/SCMD35D.h"

#include "socket/command/s19/SCMD191.h"
#include "socket/command/s19/SCMD193.h"
#include "socket/command/s19/SCMD197.h"
#include "socket/command/s19/SCMD199.h"
#include "../command/s1e/SCMD1E1.h"
#include "../command/s1e/SCMD1E3.h"
#include "../command/s1e/SCMD1E6.h"
#include "../command/s1d/SCMD1DD.h"
#include "../command/s1d/SCMD1DB.h"

#include "../command/s1a/SCMD1A1.h"
#include "../command/s1a/SCMD1A3.h"
#include "../command/s1a/SCMD1A5.h"
#include "../command/s1a/SCMD1A7.h"
#include "../command/s1a/SCMD1A9.h"
#include "../command/s1a/SCMD1AB.h"
#include "../command/s1a/SCMD1AE.h"

#include "../command/s2d/SCMD2D5.h"

#include "../command/s19/SCMD19A.h"
#include "../command/s19/SCMD19B.h"
#include "../command/s28/SCMD28B.h"

#include "../command/s1e/SCMD1EE.h"
#include "../command/s10/SCMD108.h"
#include "../command/s1b/SCMD1B2.h"
#include "../command/s1c/SCMD1C3.h"
#include "../command/s1c/SCMD1C1.h"
#include "../command/s1b/SCMD1B7.h"
#include "../command/s1c/SCMD1C6.h"
#include "../command/s1c/SCMD1C7.h"
#include "../command/s1b/SCMD1BF.h"
#include "../command/s1b/SCMD1BC.h"
#include "../command/s1c/SCMD1CB.h"
#include "../command/s1c/SCMD1CD.h"
#include "../command/s1d/SCMD1D6.h"
#include "../command/s1b/SCMD1B8.h"

#include "../command/s3b/SCMD3B3.h"
#include "../command/s3b/SCMD3B5.h"
#include "../command/s3c/SCMD3CF.h"
#include "../command/s3b/SCMD3B7.h"
#include "../command/s3c/SCMD3CB.h"
#include "../command/s3a/SCMD3AE.h"

#include "../command/s2c/SCMD2C7.h"
#include "../command/s2c/SCMD2C8.h"
#include "../command/s2c/SCMD2C9.h"
#include "../command/s2c/SCMD2CC.h"
#include "../command/s2c/SCMD2CE.h"


#include "socket/command/s2e/SCMD2E3.h"
#include "socket/command/s2e/SCMD2E6.h"
#include "socket/command/s2e/SCMD2E8.h"
#include "socket/command/s2e/SCMD2E9.h"
#include "socket/command/s2e/SCMD2EB.h"
#include "socket/command/s2e/SCMD2ED.h"
#include "socket/command/s2e/SCMD2EF.h"
#include "socket/command/s36/SCMD367.h"
#include "socket/command/s36/SCMD369.h"
#include "../command/s38/SCMD38F.h"
#include "../command/s14/SCMD142.h"
#include "../command/s2a/SCMD2A1.h"
#include "../command/s2a/SCMD2A3.h"
#include "../command/s2a/SCMD2A5.h"
#include "../command/s29/SCMD29A.h"



#include "socket/command/s40/SCMD401.h"
#include "socket/command/s40/SCMD403.h"
#include "socket/command/s40/SCMD405.h"
#include "socket/command/s40/SCMD407.h"
#include "socket/command/s40/SCMD409.h"
#include "socket/command/s40/SCMD40B.h"
#include "socket/command/s40/SCMD40D.h"

#include "socket/command/s41/SCMD411.h"
#include "socket/command/s41/SCMD414.h"
#include "socket/command/s41/SCMD416.h"

#include "socket/command/s13/SCMD137.h"
//#include "../command/s37/SCMD37C.h"
#include "../command/s2d/SCMD2DF.h"
#include "../command/s42/SCMD421.h"
#include "../command/s42/SCMD429.h"
#include "../command/s42/SCMD423.h"
#include "../command/s42/SCMD425.h"
#include "../command/s42/SCMD427.h"
#include "../command/s42/SCMD429.h"
#include "../command/s42/SCMD42B.h"
#include "../command/s2b/SCMD2B2.h"
#include "../command/s3d/SCMD3DF.h"
#include "../command/s32/SCMD3C2.h"
#include "../command/s37/SCMD373.h"
#include "../command/s37/SCMD375.h"
#include "../command/s1e/SCMD1ED.h"

#include "socket/command/s43/SCMD431.h"
#include "socket/command/s43/SCMD433.h"
#include "socket/command/s43/SCMD435.h"
#include "../command/s2b/SCMD2B6.h"
#include "../command/s2b/SCMD2B9.h"
#include "../command/s27/SCMD271.h"
#include "../command/s27/SCMD273.h"
#include "../command/s27/SCMD275.h"
#include "../command/s27/SCMD277.h"
#include "../command/s27/SCMD279.h"
#include "../command/s27/SCMD27B.h"
#include "../command/s27/SCMD27D.h"
#include "../command/s27/SCMD27E.h"
#include "../command/s27/SCMD27F.h"
#include "../command/s28/SCMD281.h"
#include "../command/s25/SCMD25C.h"
#include "../command/s25/SCMD25E.h"


#include "socket/command/s44/SCMD440.h"
#include "socket/command/s44/SCMD442.h"
#include "socket/command/s44/SCMD443.h"
#include "socket/command/s44/SCMD444.h"
#include "socket/command/s44/SCMD446.h"
#include "socket/command/s44/SCMD447.h"
#include "socket/command/s44/SCMD44A.h"
#include "socket/command/s44/SCMD44B.h"


#include "../command/s2b/SCMD2B3.h"
#include "../command/s2b/SCMD2BB.h"
#include "../command/s2b/SCMD2BF.h"
#include "../command/s12/SCMD12F.h"
#include "../command/s24/SCMD24F.h"
#include "../command/s2c/SCMD2C5.h"
#include "../command/s12/SCMD12D.h"
#include "../command/s0f/SCMD0F1.h"
#include "../command/s0f/SCMD0F2.h"
#include "../command/s28/SCMD28F.h"

//camp fight
#include "../command/s45/SCMD451.h"
#include "../command/s45/SCMD453.h"
#include "../command/s45/SCMD45B.h"

MessageFactoryManager* g_pMessageFactoryManager = NULL ;

MessageFactoryManager::MessageFactoryManager( ) 
{
	m_Factories = NULL ;
	m_Size = MESSAGE_MAX ;

	//Assert( m_Size>0 ) ;
	
	m_Factories = new MessageFactory*[ /*10000*/MESSAGE_MAX ];
	//Assert( m_Factories ) ;
	//m_pPacketAllocCount = new UINT[m_Size] ;
	//Assert( m_pPacketAllocCount ) ;
	
	for( int32 i=0; i</*10000*/MESSAGE_MAX; i++ ) 
	{
		m_Factories[i] = NULL ;
		//m_pPacketAllocCount[i] = 0 ;
	}

}

MessageFactoryManager::~MessageFactoryManager( )  
{
		
//	Assert( m_Factories!=NULL ) ;

	for( int32 i=0; i<m_Size; i++ ) 
	{
		SAFE_DELETE(m_Factories[i]) ;
	}
	
	SAFE_DELETE_ARRAY(m_Factories) ;
	//SAFE_DELETE_ARRAY(m_pPacketAllocCount) ;
			
}

bool MessageFactoryManager::Init( )
{

	AddFactory( new SCMD1EEFactory() );
	AddFactory( new SCMD105Factory() ) ;
	AddFactory( new SCMD24BFactory() ) ;

	//AddFactory( new SCMD13DFactory() ) ;
	AddFactory( new SCMD3B1Factory() ) ;

	AddFactory( new SCMD102Factory() ) ;
	AddFactory( new SCMD108Factory() ) ;
	AddFactory( new SCMD107Factory() ) ;
	AddFactory( new SCMD131Factory() ) ;
	AddFactory( new SCMD132Factory() ) ;
	AddFactory( new SCMD133Factory() ) ;
	AddFactory( new SCMD135Factory() ) ;

	AddFactory( new SCMD140Factory() );
	AddFactory( new SCMD142Factory() );
	AddFactory( new SCMD144Factory() );

	AddFactory( new SCMD161Factory() ) ;
	AddFactory( new SCMD163Factory() ) ;
	AddFactory( new SCMD165Factory() ) ;
 	AddFactory( new SCMD167Factory() ) ;
	AddFactory( new SCMD16DFactory() );
	AddFactory( new SCMD16FFactory() );

	AddFactory( new SCMD172Factory() ) ;
	AddFactory( new SCMD17DFactory() );
	AddFactory( new SCMD17FFactory() ) ;
	AddFactory( new SCMD109Factory() ) ;
	
	AddFactory( new SCMD181Factory() ) ;
	AddFactory( new SCMD183Factory() ) ;
	AddFactory( new SCMD187Factory() ) ;
	AddFactory( new SCMD188Factory() ) ;
	AddFactory( new SCMD18BFactory() ) ;
	AddFactory( new SCMD18CFactory() ) ;

	AddFactory( new SCMD191Factory() ) ;
	AddFactory( new SCMD193Factory() ) ;
	AddFactory( new SCMD197Factory() ) ;
	AddFactory( new SCMD199Factory() ) ;
	
	AddFactory( new SCMD18EFactory() ) ;
	AddFactory( new SCMD18FFactory() ) ;
	AddFactory( new SCMD19FFactory() ) ;
	AddFactory( new SCMD285Factory() ) ;
	AddFactory( new SCMD287Factory() ) ;
	AddFactory( new SCMD295Factory() ) ;

	//AddFactory( new SCMDInfoFactory() ); 	//0x18C,396 update silver
	AddFactory( new SCMD18DFactory() ); 	//0x18D,397update gold

	AddFactory( new SCMD2D3Factory() ) ;	// inherit
	AddFactory( new SCMD2D5Factory() );
	AddFactory( new SCMD2D7Factory() ) ;

	AddFactory( new SCMD2E1Factory() );

	AddFactory( new SCMD300Factory() ) ;
	AddFactory( new SCMD301Factory() ) ;
	AddFactory( new SCMD303Factory() ) ;
	AddFactory( new SCMD305Factory() ) ;
	AddFactory( new SCMD309Factory() ) ;
	AddFactory( new SCMD30AFactory() ) ;
	AddFactory( new SCMD30CFactory() ) ;
	AddFactory( new SCMD30EFactory() ) ;
	AddFactory( new SCMD310Factory() ) ;
	AddFactory( new SCMD312Factory() ) ;
	AddFactory( new SCMD314Factory() ) ;
	AddFactory( new SCMD316Factory() ) ;
	AddFactory( new SCMD318Factory() ) ;
	AddFactory( new SCMD319Factory() ) ;
	AddFactory( new SCMD31AFactory() ) ;
	AddFactory( new SCMD31BFactory() ) ;
	AddFactory( new SCMD31DFactory() ) ;
	AddFactory( new SCMD31FFactory() ) ;

	AddFactory( new SCMD39DFactory() ) ;

	AddFactory( new SCMD376Factory() );
 
	AddFactory( new SCMD150Factory() ) ;
	AddFactory( new SCMD151Factory() ) ;
	AddFactory( new SCMD153Factory() ) ;
	AddFactory( new SCMD155Factory() ) ;
	AddFactory( new SCMD157Factory() ) ;
	AddFactory( new SCMD158Factory() ) ;
	AddFactory( new SCMD15AFactory() ) ;
	AddFactory( new SCMD15CFactory() ) ;
	AddFactory( new SCMD15EFactory() ) ;

	AddFactory( new SCMD1A1Factory() ) ;
	AddFactory( new SCMD1A3Factory() ) ;
	AddFactory( new SCMD1A5Factory() ) ;
	AddFactory( new SCMD1A7Factory() ) ;
	AddFactory( new SCMD1A9Factory() ) ;
	AddFactory( new SCMD1ABFactory() ) ;
	AddFactory( new SCMD1AEFactory() ) ;

	AddFactory( new SCMD2FFFactory() ) ;

	AddFactory( new SCMD321Factory() ) ;
	AddFactory( new SCMD323Factory() ) ;
	AddFactory( new SCMD324Factory() ) ; // levy

	AddFactory( new SCMD350Factory() ) ;
	AddFactory( new SCMD35DFactory() ) ;
	AddFactory( new SCMD352Factory() ) ;
	AddFactory( new SCMD354Factory() ) ;
	AddFactory( new SCMD358Factory() ) ;
	AddFactory( new SCMD35AFactory() ) ;
	AddFactory( new SCMD35CFactory() ) ;
	AddFactory( new SCMD35EFactory() ) ; 
	AddFactory( new SCMD35FFactory() ) ; 
	AddFactory( new SCMD11DFactory() );
	AddFactory( new SCMD123Factory() );
	AddFactory( new SCMD124Factory() );
	AddFactory( new SCMD11CFactory() );

	AddFactory( new SCMD185Factory() ) ;
	AddFactory( new SCMD186Factory() ) ;
	AddFactory( new SCMD18AFactory() ) ;
	AddFactory( new SCMD19DFactory() ) ;

	AddFactory( new SCMD1DFFactory() ) ;


	AddFactory( new SCMD111Factory() ) ;
	AddFactory( new SCMD112Factory() ) ;
	AddFactory( new SCMD113Factory() ) ;
	AddFactory( new SCMD11AFactory() ) ;
	AddFactory( new SCMD11BFactory() ) ;
	AddFactory( new SCMD118Factory() ) ;
	AddFactory( new SCMD11FFactory() ) ;
	AddFactory( new SCMD120Factory() ) ;
	AddFactory( new SCMD13CFactory() ) ;
	AddFactory( new SCMD13DFactory() ) ;

	// vip
	AddFactory( new SCMD29EFactory() );
	AddFactory( new SCMD3C8Factory() );
	AddFactory( new SCMD1EFFactory() );
	
	
	AddFactory( new SCMD201Factory() ) ;
	AddFactory( new SCMD205Factory() ) ;
	AddFactory( new SCMD207Factory() ) ;
	AddFactory( new SCMD209Factory() ) ;
	AddFactory( new SCMD20bFactory() ) ;
	AddFactory( new SCMD20dFactory() ) ;
	AddFactory( new SCMD20FFactory() ) ;
	AddFactory( new SCMD211Factory() ) ;
	AddFactory( new SCMD213Factory() ) ;
	AddFactory( new SCMD214Factory() ) ;
	AddFactory( new SCMD216Factory() ) ;
	AddFactory( new SCMD21FFactory() ) ;


	AddFactory( new SCMD3DBFactory() );


	AddFactory( new SCMD361Factory() ) ;
	AddFactory( new SCMD363Factory() ) ;
	AddFactory( new SCMD36CFactory() ) ;
	AddFactory( new SCMD36EFactory() ) ;
	AddFactory( new SCMD38CFactory() ) ;

	AddFactory( new SCMD1E1Factory() ) ;
	AddFactory( new SCMD1E3Factory() ) ;
	AddFactory( new SCMD1E6Factory() ) ;
	AddFactory( new SCMD1DDFactory() ) ;
	AddFactory( new SCMD1DBFactory() ) ;

	AddFactory( new SCMD19AFactory() ) ;
	AddFactory( new SCMD19BFactory() ) ;
	AddFactory( new SCMD28BFactory() ) ;

	// guild
	AddFactory( new SCMD1B2Factory() );
	AddFactory( new SCMD1C3Factory() );
	AddFactory( new SCMD1C1Factory() );
	AddFactory( new SCMD1B7Factory() );
	AddFactory( new SCMD1BFFactory() );
	AddFactory( new SCMD1C6Factory() );
	AddFactory( new SCMD1C7Factory() );
	AddFactory( new SCMD1BCFactory() );
	AddFactory( new SCMD1CBFactory() );
	AddFactory( new SCMD1CDFactory() );
	AddFactory( new SCMD1D6Factory() );
	AddFactory( new SCMD1B8Factory() );
	
	
	//Tower
	AddFactory( new SCMD3B3Factory() );
	AddFactory( new SCMD3CFFactory() );
	AddFactory( new SCMD3B5Factory() );
	AddFactory( new SCMD3B7Factory() );
	AddFactory( new SCMD3CBFactory() );
	AddFactory( new SCMD3AEFactory() );
	AddFactory( new SCMD3DFFactory() );
	AddFactory( new SCMD3C2Factory() );

	AddFactory( new SCMD2C7Factory() );
	AddFactory( new SCMD2C8Factory() );
	AddFactory( new SCMD2C9Factory() );
	AddFactory( new SCMD2CCFactory() );
	AddFactory( new SCMD2CEFactory() );
	
	AddFactory( new SCMD2E3Factory() );
	AddFactory( new SCMD2E6Factory() );
	AddFactory( new SCMD2E8Factory() );
	AddFactory( new SCMD2E9Factory() );
	AddFactory( new SCMD2EBFactory() );
	AddFactory( new SCMD2EDFactory() );
	AddFactory( new SCMD2EFFactory() );
	AddFactory( new SCMD367Factory() );
	AddFactory( new SCMD369Factory() );

	AddFactory( new SCMD38FFactory() );
	AddFactory( new SCMD29AFactory() );

	AddFactory( new SCMD401Factory() );
	AddFactory( new SCMD403Factory() );
	AddFactory( new SCMD405Factory() );
	AddFactory( new SCMD407Factory() );
	AddFactory( new SCMD409Factory() );
	AddFactory( new SCMD40BFactory() );
	AddFactory( new SCMD40DFactory() );

	AddFactory( new SCMD2A1Factory() );
	AddFactory( new SCMD2A3Factory() );
	AddFactory( new SCMD2A5Factory() );

	AddFactory( new SCMD3C8Factory() );
	AddFactory( new SCMD2DFFactory() );
	//Begin chenjian 20121015
	AddFactory( new SCMD137Factory());
	//End chenjian 20121015
	AddFactory( new SCMD411Factory());
	AddFactory( new SCMD414Factory());
	AddFactory( new SCMD416Factory());
	//AddFactory( new SCMD37CFactory());
	AddFactory( new SCMD421Factory());
	AddFactory( new SCMD423Factory());
	AddFactory( new SCMD425Factory());
	AddFactory( new SCMD427Factory());
	AddFactory( new SCMD429Factory());
	AddFactory( new SCMD42BFactory());

	// trader
	AddFactory( new SCMD24FFactory() );

	AddFactory( new SCMD28FFactory() );
	AddFactory( new SCMD12DFactory() );
	AddFactory( new SCMD2B2Factory() );
	AddFactory( new SCMD2B3Factory() );
	AddFactory( new SCMD2B6Factory() );
	AddFactory( new SCMD2B9Factory() );
	AddFactory( new SCMD2BBFactory() );
	AddFactory( new SCMD2BFFactory() );
	AddFactory( new SCMD2C5Factory() );

	AddFactory( new SCMD12FFactory() );
	AddFactory( new SCMD0F1Factory() );
	AddFactory( new SCMD0F2Factory() );

	AddFactory( new SCMD373Factory() );
	AddFactory( new SCMD375Factory() );

	AddFactory( new SCMD431Factory() );
	AddFactory( new SCMD433Factory() ); 
	AddFactory( new SCMD435Factory() );


	AddFactory( new SCMD1EDFactory() );


	AddFactory( new SCMD440Factory() );
	AddFactory( new SCMD442Factory() );
	AddFactory( new SCMD443Factory() );
	AddFactory( new SCMD444Factory() );
	AddFactory( new SCMD446Factory() );
	AddFactory( new SCMD447Factory() );
	AddFactory( new SCMD44AFactory() );
	AddFactory( new SCMD44BFactory() );

	AddFactory( new SCMD271Factory() );
	AddFactory( new SCMD273Factory() );
	AddFactory( new SCMD275Factory() );
	AddFactory( new SCMD277Factory() );
	AddFactory( new SCMD279Factory() );
	AddFactory( new SCMD27BFactory() );
	AddFactory( new SCMD27DFactory() );
	AddFactory( new SCMD27EFactory() );
	AddFactory( new SCMD27FFactory() );
	AddFactory( new SCMD281Factory() );

	//ranking
	AddFactory( new SCMD25CFactory() );
	AddFactory( new SCMD25EFactory() );
	//camp fight
	AddFactory( new SCMD451Factory() );
	AddFactory( new SCMD453Factory() );
	AddFactory( new SCMD45BFactory() );

	return true ;
}

void MessageFactoryManager::AddFactory( MessageFactory* pFactory ) 
{

		
	if( m_Factories[pFactory->GetPacketID()]==NULL ) 
	{//重复设定
		
		m_Factories[pFactory->GetPacketID()] = pFactory ;
	}
	
	
			
}

Packet* MessageFactoryManager::CreateMessage( PacketID_t messageID ) 
{
	if( m_Factories[messageID] == NULL ) //有待处理 messageID >= m_Size ||
	{
		return NULL ;
	}
	if (messageID>m_Size)
	{
		return NULL;
	}

	Packet* pPacket = NULL ;

	_MY_TRY
	{
		pPacket = m_Factories[messageID]->CreateMessage();
	//	m_pPacketAllocCount[messageID]++ ;
	}
	_MY_CATCH
	{
		pPacket = NULL ;

	}


	return pPacket ;
}

uint32 MessageFactoryManager::GetMessageMaxSize( PacketID_t messageID ) 
{
	if( messageID>=m_Size || m_Factories[messageID]==NULL ) 
	{
		char buff[256] = {0};
		sprintf(buff,"PacketID= %d not found PacketFactoryManager",messageID);
		return 0 ;
	}


	uint32 iRet = m_Factories[messageID]->GetMessageMaxSize( ) ;

	return iRet ;
}

void MessageFactoryManager::RemoveMessage( Packet* pPacket )
{
	if( pPacket==NULL )
	{
		return ;
	}

	PacketID_t messageID = pPacket->getPacketID() ;
	if( messageID>=m_Size ) 
	{
		return ;
	}


	_MY_TRY
	{
		SAFE_DELETE( pPacket ) ;
	//	m_pPacketAllocCount[messageID] -- ;
	}
	_MY_CATCH
	{
	}

	return ;

}



