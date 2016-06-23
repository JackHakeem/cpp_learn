#include "FriendProxy.h"
#include "model/player/FigureBaseManage.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"


FriendProxy::FriendProxy()
{
	_listNum = 0;
	_currentPage = 1;
	_pageArr.clear();
	_currentList.clear();
	for (int i = 0; i < 4; i++)
		_pageArr.push_back(1);
}

FriendProxy::~FriendProxy()
{}


/**���浱ǰ�б�*/
void FriendProxy::_saveCurrentList()
{
	if(_listNum == 1)//������ϵ���б� �ͻ��˱���
		_relashipList = _currentList;

	_pageArr[_listNum] = _currentPage;//�����б�����ҳ��
}

/**���õ�ǰҪ�������б�*/
void FriendProxy::setlistNum(uint32 n)
{
	_saveCurrentList();//�л���ǰ�б�ʱ���ȱ��浱ǰ�б���Ϣ
	_listNum = n;
			
	if(_listNum == 1)
		_currentList = _relashipList;
	else
		_currentList.clear();//��������ϵ���б��ȴ����������
			
	_currentPage = _pageArr[_listNum];
}

/**�õ���ǰ�б����*/
uint32 FriendProxy::getlistNum()
{
	return _listNum;
}

/**�õ����������Ϣ*/
PlayerInfoVo* FriendProxy::getplayInfo()
{
	PlayerInfoVo* pInfo = RoleManage::Instance()->roleInfo();
	return pInfo;
}

/**�õ�������������Ϣ*/
FriendInfoVo FriendProxy::getmyInfo()
{
	AccountInfoVo accInfo =  RoleManage::Instance()->_accountInfo;
	FriendInfoVo friInfo;
	friInfo.id = accInfo.accountId;
	friInfo.level = RoleManage::Instance()->roleInfo()->playerBaseInfo.lev();
	friInfo.name = accInfo.name;
	friInfo.OF = 0;
	friInfo.cloth = getplayInfo()->playerBaseInfo.cloth;
	return friInfo;
}

/**
	* ��յ�ǰ�б� 
	* 
	*/		
void FriendProxy::resetCurrentList()
{
	_currentList.clear();
}

/**
	* �õ���ǰ�б���Ŀ��������Ҫ���ڿͻ��˱���������ϵ���б� 
	* @return 
	* 
	*/		
uint32 FriendProxy::totalNum()
{
	return _currentList.size();
}
	
/**���ӵ�ǰ�б�*/
void FriendProxy::addLinkHuman(FriendInfoVo& info)
{
	if (_currentList.size() < 10)
	{
		FigureCfgBaseVo* figureBaseVo = FigureBaseManage::Instance()->getMercBase(info.avatarID);
		info.sex = figureBaseVo?figureBaseVo->sex : 1;//�õ�����Ա�
		info.cloth = figureBaseVo?figureBaseVo->cloth : 1;//�õ����ͷ��
		_currentList.push_back(info);
	}
}

//CC_PROPERTY(uint32, _currentPage, page)
/**
	* ���õ�ǰҳ����ҳʱͬ�� 
	* @param num
	* 
	*/		
void FriendProxy::setpage(uint32 var)
{
	_currentPage = var;
}

/**
	* �õ���ǰҳ 
	* @return 
	* 
	*/		

uint32 FriendProxy::getpage()
{
	return _currentPage;
}

/**��������ϵ��*/
void FriendProxy::addLater(FriendInfoVo info)
{
	if(_currentList.size() < 10)
	{
		FigureCfgBaseVo* figureBaseVo = FigureBaseManage::Instance()->getMercBase(info.avatarID);
		info.sex = figureBaseVo?figureBaseVo->sex : 1;//�õ�����Ա�
		info.cloth = figureBaseVo?figureBaseVo->cloth : 1;//�õ����ͷ��
		info.OF = 0;
		info.blessDisable = 1;
		if(!hasOwnProperty(&info, &_relashipList))
			_relashipList.push_back(info);
	}
}

/**�Ƿ��ڶ�Ӧ�б���������Ϣ*/

bool FriendProxy::hasOwnProperty(FriendInfoVo* vo, std::list<FriendInfoVo>* list)
{
	if(!list)
		list = &_currentList;

	std::list<FriendInfoVo>::iterator info;
	for (info = list->begin(); info != list->end(); info++)
	{
		if(info->id == vo->id)
			return true;
	}
	return false;
}

/**ɾ����ϵ��*/
void FriendProxy::deleteLinkHuman(FriendInfoVo fInfo)
{//����ɾ���ͻ��˱����������ϵ���б�
	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		if (fInfo.id == vo->id)
		{
			_currentList.erase(vo);
			break;
		}
	}
//	var position:uint = _currentList.indexOf(fInfo);
//	var SPLICE:Array = _currentList.splice(position,1);		
}

void FriendProxy::deleteHumanByName(std::string name)
{
	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		if(vo->name == name)
			break;
	}

	deleteLinkHuman(*vo);
}

//CC_PROPERTY(uint32, _blessInfo, blessInfo)
/**�������ף����Ϣ*/
void FriendProxy::setblessInfo(BlessInfoVo var)
{
	_blessInfo = var;
}
		
/**�������ף����Ϣ*/
BlessInfoVo FriendProxy::getblessInfo()
{
	return _blessInfo;
}

/**
* ���ص�ǰ�б�������ҵ�ID 
* @return 
* 
*/		
std::list<int> FriendProxy::currentIds()
{
	std::list<int> ids;

	std::list<FriendInfoVo>::iterator vo;
	for (vo = _currentList.begin(); vo != _currentList.end(); vo++)
	{
		ids.push_back(vo->id);
	}
	return ids;
}
	
/**
* ֱ��ָ����Ӧ�б������page 
* @param index
* @param page
* 
*/		
void FriendProxy::setDerectPage(uint32 index, uint32 page)
{
	_pageArr[index] = page;
}

/*
		���ص�ǰҪ��ʾ��
		public function get currentList():Array{
			if(_currentList.length > 10)//�����ϵ���ɿͻ��˱��棬���ܲ�ֹһҳ����Ҫ�ͻ���ʵ�ַ�ҳ����
				return _currentList.slice((_currentPage - 1) * 10, (_currentPage - 1) * 10 + 10);
			else
				return _currentList;
		}
		*/
		