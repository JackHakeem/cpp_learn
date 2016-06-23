#ifndef HLQS_SkillManager_H_
#define HLQS_SkillManager_H_
#include "model/skill/vo/SkillVo.h"
#include "model/skill/vo/LevSkillVo.h"
#include "utils/Singleton.h"
#include "model/formation/vo/FormationInfo.h"
#include "model/skill/vo/SkillInfo.h"
#include "model/skill/vo/LevSkillVo.h"
#include "model/crystal/vo/CrystalInfo.h"
#include "cocos2d.h"

class SkillNode
{
public:
	SkillNode()
	{
		type = 0;
		formationInfo = NULL;
		//skillInfo = NULL;
		crystalInfo = NULL;
	}
	~SkillNode()//jae change
	{
		//CC_SAFE_DELETE( formationInfo );
		//CC_SAFE_DELETE( skillInfo );
		//CC_SAFE_DELETE( crystalInfo );
	}

	int type; // 0: formationInfo; 1: skillInfo; 2:crystalInfo
	FormationInfo* formationInfo;
	SkillInfo skillInfo;
	CrystalInfo* crystalInfo;
};

class SkillManager: public Singleton<SkillManager>
{
public:
	std::map<int/*rank*/, std::map<int/*id*/, SkillNode> > _skillRankDic;
	std::map<int/*rank*/, std::map<int/*id*/, SkillNode> > _learnedSkillRankDic;
	std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> > _levSkillDic;
	std::map<int, SkillVo> _skillDic;
	std::map<int, SkillNode> _talentSkillDic;
	std::map<int, std::vector<int> > _offensiveSkillDic;

public:
	SkillManager();
	~SkillManager();
	void createSkill(std::vector<SkillVo>* skillVoList);
	void createLevSkill(LevSkillVo& levSkillVo);
	SkillVo* getSkill(int skillId);
	LevSkillVo* getLevSkill(int skillId, int lev);
	LevSkillVo* getLowLevSkill(int skillId, int lev = 0);
	std::map<int, SkillNode>* getSkillsByRank(int rankId);
	std::map<int, SkillNode>* getLearnedSkillsByRank(int rankId);
	std::vector<int>* getOffensiveSkill(int figure);
};

#endif