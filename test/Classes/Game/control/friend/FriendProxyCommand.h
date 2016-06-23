#ifndef _FRIENDPROXYCOMMAND_H_
#define _FRIENDPROXYCOMMAND_H_

#include "mvc/SimpleCommand.h"

class FriendProxy;
class SCMD201;
class SCMD205;
class SCMD213;
class SCMD216;
class SCMD219;
class SCMD207;
class FriendProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		CREATE_FRIENDS_LIST,
		CREATE_LATER_LIST,
		CREATE_RECOMMEND_LIST,//��װ�Ƽ������б�
		CREATE_BLACK_LIST,//��װ�������б�
		ADD_LATER_LIST,//���췢��˽��ʱ����, ���������ϵ��
		CHANGE_LIST_INDEX,//�л��б�
		CHANGE_LIST_PAGE,//��ҳ
		PAGE_CHANGE_DERECT,//ָ��ĳ�б��´�����ҳ��
		REQUEST_FRIENDS_LIST,//��������б�
		REQUEST_RECOMMEND_LIST,//�����Ƽ������б�
		REQUEST_BLACK_LIST,//����������б�
		ADD_FRIEND,//��Ӻ�������
		DELETE_FRIEND,//ɾ����������
		MOVE_TO_BLACK,//�Ƶ�������
		UPDATE_CURRENT_LIST,//����ǰ�б�
		CHECK_REQUEST,//�����������
		RECEIVE_REQUEST,//���պ�������
		BLESS_INFO,
		QUICK_ADD_RECOMMEND_FRIENDS,
		MOVE_FRIEND_OUT,
		REQUEST_FOR_CHAT,//��������
		REQUEST_FOR_TROOP,//�������
	};

public:
	FriendProxyCommand();
	~FriendProxyCommand(){}
	virtual void execute(int32 command, char* data);


public:
	void updateFList(SCMD201* param);
	void updateLList(SCMD213* param);
	void updateRList(SCMD205* param);
	void updateBList(SCMD207* param);
	void changeListIndex(uint32 index);
	void requestForLater(uint32 page = 1);
	void requestForREList(uint32 page = 1);
	void requestForFList(uint32 page = 1);
	void requestForBList(uint32 page = 1);
	void requestForPlayInfo(std::string name);
	void requestForAddF(std::string name = "");
	void requestForMTB(std::string name = "");
	void moveOutOfCurrentList(char* obj);
	void requestForDELF(std::string name);
	void checkAddReqHandler(char* obj);
	void blessInfoHandler(SCMD219* params);
	void quickAddRecFriHandler();
	void requestForChat(int32 id);
	void setPageDerect(char* obj);
	void changeListPage(uint32 page);
	void requestForCurrentList();
	void receiveRequest(SCMD216* param);
public:
	FriendProxy* _friendProxy;
};

#endif