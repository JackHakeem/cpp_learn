#include "SilverMineProxy.h"

SilverMineProxy::SilverMineProxy()
{
	isInMine = false;
	_campId = -1;  // ��ӪID ��Чֵ 0��1, 2 
	_moveCD = 0;	// �ж�CD ��λ��
	_inActionCD = false;
	 _digCD = 0;	// �ڿ�CD ��λ��
	_inDigCD = false;
	_mineID  = 0;		// ��ǰ���ڿ�ID
	_onMine  = 0;		// ��ǰ������������
	_winRow  = 0;		// ��ʤ����
	_attPlus = 0;		// ���蹥���ӳ�
	_defPlus = 0;		// ��������ӳ� 
	//	 _mineArr:Array = [];  // ��������
	_token0 = 0;   // ����0
	_token1 = 0;   // ����1 
}

SilverMineProxy::~SilverMineProxy()
{}