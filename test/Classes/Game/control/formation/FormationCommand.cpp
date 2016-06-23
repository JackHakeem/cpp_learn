#include "FormationCommand.h"
#include "socket/command/s31/SCMD318.h"
#include "model/formation/vo/FormationInfo.h"
#include "model/player/RoleManage.h"
#include "manager/ViewManager.h"
#include "model/skill/SkillProxy.h"
#include "mvc/Facade.h"
#include "../AppFacade.h"

FormationCommand::FormationCommand()
{

}

FormationCommand::~FormationCommand()
{
}

void FormationCommand::execute( int32 command, char* data )
{
	switch(command)
	{
	case FORMATION_ACTIVATE:
		formationActivate(data);
		break;
	case MEMBER_CHANGE:
		memChange(data);
		break;
	case  INIT_FORMATION:
		initFormationDic(data);
		break;
	case INIT_TEAM_MEMBERS:
		break;
	case UPDATE_TEAM_MEMBER:
		break;
	case CHANGE_TEAM_MEMBER_SIT:
		break;
	case DISMISS_FIGURE:
		break;
	default:
		break;
	}
}


        /**
		 *Delivery to the client formation information list
		 * @param param
		 * 
		 */	
void FormationCommand::initFormationDic(char* data )

{
	//Data of compulsory type conversion
	std::list<SCMD318::SCMD318Node> *  tmpdata = (std::list<SCMD318::SCMD318Node> *)data;
	std::list<FormationInfo*>  formationInfoList;
	std::list<SCMD318::SCMD318Node>::iterator it;

	for(it=tmpdata->begin();it!=tmpdata->end();it++)
	{
		  SCMD318::SCMD318Node*  onedata = &*it;
		  FormationInfo* formationInfo = new FormationInfo();

		  formationInfo->setId(onedata->a_formationId);
		  formationInfo->lev=onedata->b_formationLel;
		  formationInfo->active=onedata->c_active;
		 
		  if(onedata->c_active ==1)
		  {
			  if(formationInfo->getId() < 17)
				 
			  RoleManage::Instance()->accountInfo()->currFormation=formationInfo->getId();
		  }

		      std::list<SCMD318::SCMD318Node2>::iterator it2;
		      for(it2=onedata->d_figures.begin(); it2!=onedata->d_figures.end(); it2++)
			  {
				  SCMD318::SCMD318Node2*  onedata2 = &*it2;
				  formationInfo->figuresMap[onedata2->a_sitGrid]=onedata2->b_figureId;
			  }


			  formationInfoList.push_back(formationInfo);
	}
	 
	 
	//Here will be formationInfoList to SkillProxy use
	SkillProxy* _skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	_skillProxy->initFormationDic(formationInfoList); 
}


void FormationCommand::memChange( char* data )
{
	SkillProxy * pSkillProxy = (SkillProxy *)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	pSkillProxy->formationMemberChange(data);
}

void FormationCommand::formationActivate(char* data)
{
	SkillProxy * pSkillProxy = (SkillProxy *)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	pSkillProxy->formationActivateChange(data);
}
 




