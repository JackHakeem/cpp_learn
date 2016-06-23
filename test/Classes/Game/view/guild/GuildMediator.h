#ifndef _GuildMediator_H_
#define _GuildMediator_H_

#include "mvc/Mediator.h"
#include "components/GuildView.h"
#include "socket/command/s1b/SCMD1B2.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "components/GuildPreView.h"
class MemberVo;

class GuildMediator:public Mediator
{
public:
	enum
	{
		GUILD_POP = 0,
		GUILD_PRE_POP,
		GUILD_MY_INFO,
		GUILD_INIT_INFO,
		OPEN_EDIT_VIEW,
		SET_GUILD_LIST,
		SET_PANEL_LIST,
		GUILD_INFO_EDIT,
		CLOSE_ALL_VIEW,
	};
public:
	GuildMediator();
	~GuildMediator();

	void handleNotification( int M2Vcmd, char* data );
	void setGuildList( char* data );
	void setDefaultVO( MemberVo* info );
	void pop( GuildView* view );

	void setPanelList(char* data);

	void setGuildInfo( char* data );
	void editMainPanelInfo( char* data );
	void editInit( char* arg );
	void prePop(char* data);
	void closeAllView();

public:
	GuildView* _view;				//����������
	GuildPreView* _preView;			//�����б����
	//_editView:GuildEditView;		//������Ϣ�༭����
	//_donateView:DonateView;		//����Ƽ����׽���.

	GuildInfoVo guildInfo;
};
 
extern GuildMediator* g_pGuildMediator;
#endif