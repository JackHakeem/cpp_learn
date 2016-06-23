#ifndef HLQS_SkillProxy_H_
#define HLQS_SkillProxy_H_
#include "mvc/Proxy.h"
#include "../formation/vo/FormationInfo.h"
#include "vo/SkillInfo.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "SkillManager.h"

class SkillProxy: public Proxy
{
public:
	SkillProxy();

	void  initFormationDic(std::list<FormationInfo*>&  flist);

	void formationActivateChange(char * data);
	void formationMemberChange(char * data);
	void initSkillDic(std::vector<SkillInfo>* arr);
	void initTalentDic(std::vector<SkillInfo>* arr);
	void delelteFigureOnFormations(int figureId);
	void updateSkillState(int skillId, bool active);
	UpGradeInfo* transUpgradeInfo(int id, int level);
	UpGradeInfo* getUpGradeInfo(int skillId, int rank);
	void updateSkill(int skillId, int level);
	void updateFormation(int formationId, int level);
	void exchangeSkill(int figure, int rank, int eqId, int offId);
	void addSkill(SkillInfo* skillInfo);
	void addFormation(FormationInfo* formationInfo);
	void addTalent(SkillInfo* skillInfo);
	FormationInfo* getFormation(int formationId);
	SkillInfo* getTalent(int talentId);
	SkillInfo* getSkill(int skillId);
	FormationInfo* currFormationList();
	std::map<int, SkillNode> formatDic(std::map<int, SkillNode>* dic);
	std::map<int, UpGradeInfo> transDic(int rank);
	std::map<int, SkillNode>* passvieSkillList();
	std::map<int, SkillNode> formationList(bool lev_request = false);
	std::map<int, SkillNode> singleFormationList();
	std::map<int, SkillNode> teamFormationList();
	void updateTalent(int skillId, int level);

public:
	bool _isFormationInit;
	std::map<int, SkillNode>* _formationDic; //formation Dic
	std::map<int, SkillNode>* _skillDic; //passive skill dic
	std::map<int, SkillNode>* _talentDic;
	
	bool _isSkillInit;
	bool _isTalentInit;
};

#endif