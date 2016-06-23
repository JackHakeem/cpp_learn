#include "GuildChangeCommand.h"
#include "socket/command/s1b/SCMD1B2.h"
#include "view/guild/GuildMediator.h"
#include "model/guild/vo/MemberVo.h"
#include "socket/command/s1c/SCMD1C3.h"
#include "manager/LangManager.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "socket/command/s1c/SCMD1C1.h"
#include "socket/command/s1b/SCMD1BF.h"
#include "model/player/RoleManage.h"
#include "socket/command/s1c/SCMD1C6.h"
#include "model/guild/vo/TechVo.h"
#include "model/skill/SkillManager.h"
#include "model/guild/vo/ApplyVo.h"
#include "socket/command/s1b/SCMD1BC.h"
#include "socket/command/s1b/SCMD1B8.h"
#include "view/chat/ChatMediator.h"

GuildChangeCommand::GuildChangeCommand()
{
}

void GuildChangeCommand::execute( int32 command, char* data )
{
	switch( command )
	{
	case CREATE_GUILD_LIST:
		updateGuildList(data);
		break;

	case GET_MY_GUILD_INFO:
		setDefaultVO(data);
		break;
	case GET_GUILD_INIT_INFO:
		setInitGuildText(data);
		break;
	case GET_MEMBER_LIST:
		updateMemberList(data);
		break;
	case GET_TECH_LIST:
		updateTechList(data);
		break;
	case GET_CHECK_LIST:
		updateCheckList(data);
		break;
	case GET_SEARCH_MEMBER_LIST:
		updateSearMemList(data);
		break;
	case GUILD_TIPS:
		//showGuildTip(data);
		break;
	}
}

GuildChangeCommand::~GuildChangeCommand()
{

}

void GuildChangeCommand::updateGuildList( char* data )
{
	SCMD1B2* param = (SCMD1B2*)data;
	struct Node
	{
		int page;
		int max;
	} head;
	head.page = param->b_page;
	head.max = param->a_total;
	
	std::list<GuildInfoVo*> nodeArr;
	std::list<SCMD1B2::SCMD1B2Node>::iterator it = param->e_guildArr.begin();
	for ( ; it!= param->e_guildArr.end(); it++ )
	{
		SCMD1B2::SCMD1B2Node node = *it;

		GuildInfoVo* info = new GuildInfoVo;
		info->rank = node.a_rank;
		info->name = node.b_guildName;
		info->leaderName = node.c_leadName;
		info->emblemGrade = node.d_emblemLevel;
		info->members = node.e_memberNum;
		info->memberLimit = node.f_memberLimit;
		info->intr = node.g_guildIntr;
		info->flag = node.h_flag;
		nodeArr.push_back(info);
	}

	struct NodeStruct
	{
		Node headNode;
		std::list<GuildInfoVo*> nodeArray;
	} nodeStruct;
	nodeStruct.headNode = head;
	nodeStruct.nodeArray = nodeArr;
	//this.sendNotification(GuildMediator.SET_GUILD_LIST, {head: head, nodeArr: nodeArr});
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&nodeStruct, GuildMediator::SET_GUILD_LIST );
}

void GuildChangeCommand::setDefaultVO( char* data )
{
	SCMD1C3* param = (SCMD1C3*)data; 

	MemberVo* info = new MemberVo;
	std::list<SCMD1C3::SCMD1C3Node> arr = param->c_nodeArr;

	if ( arr.size() > 0 )
	{
		std::list<SCMD1C3::SCMD1C3Node>::iterator it = arr.begin();
		SCMD1C3::SCMD1C3Node node = *it;

		if ( node.c_pName == RoleManage::Instance()->accountInfo()->name )
		{
			info->name = node.c_pName;
			info->duty = getDutyString(node.a_position);
			info->id = node.b_pID;
			info->level = node.d_pLevel;
			info->fame = node.e_emblem;
			info->state = node.g_pState;
		}		
	}

	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)info, GuildMediator::GUILD_MY_INFO );
	
	if (info)
		delete info;
}

string GuildChangeCommand::getDutyString( int duty )
{
	string str = "";
	switch(duty)
	{
	case 0:		//自由人
		str = LangManager::getText("GLD071");
		break;
	case 1:		//会员
		str = LangManager::getText("GLD059");
		break;
	case 2:		//官员
		str = LangManager::getText("GLD058");
		break;
	case 3:		//副会长
		str = LangManager::getText("GLD039");
		break;
	case 4:		//会长
		str = LangManager::getText("GLD038");
		break;
	}
	return str;
}

/**
* 处理查找好友的返回包 
* @param param
*/	
void GuildChangeCommand::updateSearMemList( char* data )
{
	SCMD1C3* param = (SCMD1C3*)data;
	struct Node
	{
		int page;
		int max;
	} head;
	head.page = param->b_page;
	head.max = param->a_total;

	std::list<GuildVoBase*> nodeArr;
	std::list<SCMD1C3::SCMD1C3Node>::iterator it = param->c_nodeArr.begin();
	for ( ; it!= param->c_nodeArr.end(); it++ )
	{
		SCMD1C3::SCMD1C3Node node = *it;

		MemberVo* info = new MemberVo;
		info->name = node.c_pName;
		info->duty = getDutyString(node.a_position);
		info->id = node.b_pID;
		info->level = node.d_pLevel;
		info->fame = node.e_emblem;
		info->state = node.g_pState;
		nodeArr.push_back(info);
	}

	struct NodeStruct
	{
		Node headNode;
		//std::list<MemberVo*> nodeArray;
		std::list<GuildVoBase*> nodeArray;
		int panelIndex;
	} nodeStruct;
	nodeStruct.headNode = head;
	nodeStruct.nodeArray = nodeArr;
	nodeStruct.panelIndex = 0;
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&nodeStruct, GuildMediator::SET_PANEL_LIST );
	//this.sendNotification(GuildMediator.SET_PANEL_LIST, {head: head, nodeArr: nodeArr, panelIndex: 0});
}

void GuildChangeCommand::updateMemberList( char* data )
{
	SCMD1C1* param = (SCMD1C1*)data;
	struct Node
	{
		int page;
		int max;
	} head;
	head.page = param->b_page;
	head.max = param->a_total;


	//std::list<MemberVo*> nodeArr;
	std::list<GuildVoBase*> nodeArr;
	std::list<SCMD1C1::SCMD1C1Node>::iterator it = param->c_pArr.begin();
	for ( ; it!= param->c_pArr.end(); it++ )
	{
		SCMD1C1::SCMD1C1Node node = *it;

		MemberVo* info = new MemberVo();
		info->name = node.c_pName;
		info->duty = getDutyString(node.a_position);
		info->id = node.b_pID;
		info->level = node.d_pLevel;
		info->fame = node.e_emblem;
		info->state = node.g_pState;
		info->contribution = node.h_con;
		nodeArr.push_back(info);

	}

	struct NodeStruct
	{
		Node headNode;
		std::list<GuildVoBase*> nodeArray;
		int panelIndex;
	} nodeStruct;
	nodeStruct.headNode = head;
	nodeStruct.nodeArray = nodeArr;
	//panelIndex为面板索引，0成员，1科技，2申请
	nodeStruct.panelIndex = 0;
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&nodeStruct, GuildMediator::SET_PANEL_LIST );
}

void GuildChangeCommand::updateTechList( char* data )
{
	SCMD1C6* param = (SCMD1C6*)data;
	struct Node
	{
		int page;
		int max;
	} head;
	head.page = param->b_page;
	head.max = param->a_total;


	std::list<GuildVoBase*> nodeArr;
	std::list<SCMD1C6::SCMD1C6Node>::iterator it = param->d_scienceArr.begin();
	for ( ; it!= param->d_scienceArr.end(); it++ )
	{
		SCMD1C6::SCMD1C6Node node = *it;

		TechVo* info = new TechVo;
		info->id = node.a_scienceId;
		info->level = node.b_scienceLevel;
		SkillVo* pSkillVo = SkillManager::Instance()->getSkill(info->id);
		char tmp[10] = {0};
		if (pSkillVo)
		{
			info->name = pSkillVo->name;
			info->des = pSkillVo->des;
			sprintf( tmp, "%d", pSkillVo->icon );
		}
		info->moneyHave = node.d_hasYB;
		info->moneyNeed = node.c_requrieYB;
		info->icon = string("guild/")+ tmp + ".png";
		info->progress = (info->moneyNeed!=0)?(info->moneyHave / info->moneyNeed):0;
		info->isDefault = (node.a_scienceId == param->c_defaultId);
		if(info->progress>1) info->progress = 1;
		nodeArr.push_back(info);
	}

	struct NodeStruct
	{
		Node headNode;
		std::list<GuildVoBase*> nodeArray;
		int panelIndex;
	} nodeStruct;
	nodeStruct.headNode = head;
	nodeStruct.nodeArray = nodeArr;
	//panelIndex为面板索引，0成员，1科技，2申请
	nodeStruct.panelIndex = 1;
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&nodeStruct, GuildMediator::SET_PANEL_LIST );
}

void GuildChangeCommand::setInitGuildText( char* data )
{
	SCMD1BF* param = (SCMD1BF*)data;
	GuildInfoVo* info = new GuildInfoVo();
	info->name = param->a_guildName;
	RoleManage::Instance()->roleInfo()->playerBaseInfo.guildName(info->name);
	info->leaderName = param->b_leaderName;
	info->emblemGrade = param->c_emblemLevel;
	info->guildGrade = param->d_guildLevel;
	info->rank  = param->e_guildRank;
	info->members   = param->f_memberNum;
	info->memberLimit = param->g_memberLimit;
	info->ctime = param->h_createDate;
	info->qq = param->i_qqGN;
	info->notice = param->j_notice;
	info->intr = param->l_intro;
	info->state = param->m_state ? param->m_state : 0;
	info->abortTime = param->n_abortTime ? param->n_abortTime : 0;
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)info, GuildMediator::GUILD_INIT_INFO );
	if (info)
		delete info;
}

void GuildChangeCommand::updateCheckList( char* data )
{
	SCMD1BC* param = (SCMD1BC*)data;
	struct Node
	{
		int page;
		int max;
	} head;
	head.page = param->b_page;
	head.max = param->a_total;


	std::list<GuildVoBase*> nodeArr;
	std::list<SCMD1BC::SCMD1BCNode>::iterator it = param->c_applyArr.begin();
	for ( ; it!= param->c_applyArr.end(); it++ )
	{
		SCMD1BC::SCMD1BCNode node = *it;

		ApplyVo* info = new ApplyVo;
		info->ctime = node.d_applyDate;
		info->fame = node.c_prestige;
		info->grade = node.b_pLevel;
		info->name = node.a_pName;
		nodeArr.push_back(info);
	}

	struct NodeStruct
	{
		Node headNode;
		std::list<GuildVoBase*> nodeArray;
		int panelIndex;
	} nodeStruct;
	nodeStruct.headNode = head;
	nodeStruct.nodeArray = nodeArr;
	//panelIndex为面板索引，0成员，1科技，2申请
	nodeStruct.panelIndex = 2;
	sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&nodeStruct, GuildMediator::SET_PANEL_LIST );
}

void GuildChangeCommand::showGuildTip( char* data )
{
	SCMD1B8* cmd = (SCMD1B8*)data;
	string tip = "";
	string _operator = cmd->b_operator;
	string target = cmd->c_target;
	int param1 = cmd->d_param1;
	int param2 = cmd->e_param2;
	char txt[128];
	switch(cmd->a_type)
	{
	case 1:
		// 1 – 职务变更
		if(param2 == 4)
		{
			//转移会长
			sprintf( txt, ValuesUtil::Instance()->getString( "GLD072" ).c_str(), target.c_str() );
			tip = txt;
		}
		else if(param2 == 0)
		{
			//开除会员
			tip = LangManager::getText("GLD073", target.c_str());
		}
		else if(param2 > param1)
		{
			//提升职务
			sprintf( txt, ValuesUtil::Instance()->getString( "GLD074" ).c_str(), _operator.c_str(), 
				target.c_str(), getDutyString(param1).c_str(), getDutyString(param2).c_str() );
			tip = txt;
		}
		else if(param2 < param1)
		{
			//降低职务
			sprintf( txt, ValuesUtil::Instance()->getString( "GLD075" ).c_str(), _operator.c_str(), 
				target.c_str(), getDutyString(param1).c_str(), getDutyString(param2).c_str() );
			tip = txt;
		}
		break;
	case 2:		// 2 – 捐献
		{
			string techName = SkillManager::Instance()->getSkill(param1)->name;
			if (param2 > 20000)
			{
				sprintf( txt, LangManager::getText("GLD077").c_str(), _operator.c_str(), techName.c_str(), param2 );
				tip = txt;
			}			
		}
		break;
	case 3:		// 3 – 新人入会
		tip = LangManager::getText("GLD078", target.c_str());
		break;
	case 4:		// 4 – 修改公告
		{
			sprintf( txt, ValuesUtil::Instance()->getString( "GLD079" ).c_str(),
				_operator.c_str(), target.c_str() );
			tip = txt;
		}
		break;
	case 5:		// 5 - 科技升级
		{
			string techName = SkillManager::Instance()->getSkill(param1)->name;
			sprintf( txt, ValuesUtil::Instance()->getString( "GLD080" ).c_str(),
				techName.c_str(), param2 );
			tip = txt;
		}
		break;
	}
	if(tip == "") return;
	//sendNotification( Facade_Mediator, AppFacade_GUILD_CHANGE, (char*)&tip, ChatMediator::GUILD_TIPS );
}
