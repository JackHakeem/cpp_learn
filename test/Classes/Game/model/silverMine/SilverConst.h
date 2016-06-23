#pragma once
#include "BaseType.h"
class SilverConst
{		
public:
	/// ���峣�� 
	static const int NON_CAMP       = -1;  // ����Ӫ 
	static const int CAMP_ZERO 		= 0;  // ��Ӫ1
	static const int CAMP_ONE  		= 1;  // ��Ӫ2
	static const int CAMP_TWO  		= 2;  // ��Ӫ3
		
	/// ��������ID �����Ƶ�����type   0��Ϯ��1���ţ�2���ۣ�3���飻 
	static const int TOKEN_RAID     = 0;   // Ϯ
	static const int TOKEN_HARASS   = 1;    // ��
	static const int TOKEN_SPEED    = 2;    // ��
	static const int TOKEN_SEARCH   = 3;    // ��

 	enum
	{
		/// �����¼� 
		
		EXIT_MINE_VIEW,//:String = "EXIT_MINE_VIEW";  // �뿪����ս 
	
		CLICK_MINE_ITEM,//:String = "CLICK_MINE_ITEM";  // �����
	
		CLICK_DIG_BTN,//:String = "CLICK_DIG_BTN";  // ����ڿ�ť 
	
		DIG_MINE,//:String = "DIG_MINE";   // �ڿ�
	
		MOVE_MINE,//:String = "MOVE_MINE";  // �ƶ�
	
		LOOK_REPORT,//:String = "LOOK_REPORT";  // �鿴ս�� 
	
		PVP_REPROT,//:String = "PVP_REPROT";  // �鿴PVPս�� 
	
		DO_INSPIRE,//:String = "DO_INSPIRE";	// ʹ�ù��� 
	
		CLICK_TOKEN,//:String = "CLICK_TOKEN";  // ������� ������ʹ������ 
	
		USE_TOKEN,//:String = "USE_TOKEN";   // ʹ������ 
	};

};