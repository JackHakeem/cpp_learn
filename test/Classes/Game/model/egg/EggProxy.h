#pragma once

#include "BaseType.h"
#include "mvc/Proxy.h"
#include "./vo/EggInfo.h"
#include "./vo/EggVo.h"


class SCMD401;
class SCMD40B;

class EggProxy : public Proxy
{
public:
	
	/** ��Ը������ */
	int _currencyNum;
	/** �ҵ���ʷ��Ը���� */
	std::vector<EggInfo> _myRewards;
	/** ������ҵ���ʷ��Ը���� */
	std::vector<EggInfo> _otherRewards;
	/** ��Ը������ĵ������� */
	std::vector<EggInfo> _eggs;
	/** ��Ը������ĵ����ֵ� */
	std::map<int, std::vector<EggInfo> > _eggDic;
	/** ��Ը������ĵ�����*/
	std::vector<EggInfo> _prizeEggs;
	/** ��Ը������ĵ����� */
	int _eggNum;
	/** ��Ը�����ҳ�� */
	int depotPage;
	/** ��Ը����ÿҳ�ĸ����� */
	int depotGrid;

	EggProxy()
	{
		_currencyNum = 0;
		_eggNum = 0;
		depotPage = 10;
		depotGrid = 30;
	}
	~EggProxy()
	{}
		
	/**
		* ��ʼ����Ը����������ʷ������Ϣ�������Լ��ĺ���ҵģ�
		* @param param
		* 
		*/		
	void initReward(SCMD401* param);
		
	/**
		* ��ʼ����Ը�������ݣ��洢����������е���
		* @param param
		* 
		*/		
	void initDepot(SCMD40B* param);

	/**
		* ���ݱ����ҳ������ȡ��ҳ���������� 
		* @param page	ҳ��
		* @return 
		* 
		*/	
	std::vector<EggInfo>* getEggsByPage(int page);
		
	/* ------------------------------------- getter/setter ------------------------------------- */
		
	/** ��Ը������ */
	int getcurrencyNum()
	{
		return _currencyNum;
	}
		
	/** �ҵ���ʷ��Ը���� */
	std::vector<EggInfo>& getmyRewards()
	{
		return _myRewards;
	}

	/** ������ҵ���ʷ��Ը���� */
	std::vector<EggInfo>& getotherRewards()
	{
		return _otherRewards;
	}

	/** ��Ը������ĵ����� */
	int geteggNum()
	{
		return _eggNum;
	}

	/** ��Ը������ĵ������� */
	std::vector<EggInfo> geteggs()
	{
		return _eggs;
	}

	/** ��Ը������ĵ�����*/
	std::vector<EggInfo> getprizeEggs()
	{
		return _prizeEggs;
	}
};