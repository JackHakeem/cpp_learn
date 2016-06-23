#include "StoryManager.h"
#include "../config/ConfigManager.h"
#include "vo/SceneConst.h"

StoryManager::StoryManager()
{
    
}

StoryManager::~StoryManager()
{
}

void StoryManager::setStorys(StoryVo * info)
{
	_storyDic.insert(make_pair(info->id,*info));
}

StoryVo * StoryManager::getStory(int id)
{
	std::map<int, StoryVo>::iterator iter = _storyDic.find(id);
	if(iter != _storyDic.end())
	{
		return &iter->second;
	}
	return 0;
}

void StoryManager::setStoryModel(StoryModelVo * info)
{
	_storyModelDic.insert(make_pair(info->id,*info));
}

StoryModelVo * StoryManager::getStoryModel(int id)
{
	std::map<int,StoryModelVo>::iterator iter = _storyModelDic.find(id);
	if (iter != _storyModelDic.end())
	{
		return &iter->second;
	}	
	return 0;
}

std::vector<StoryElement> StoryManager::createElemenet(std::string element)
{
	std::vector<StoryElement> vcStoryElement;
	std::vector<std::string> vcElements;// = ConfigManager::splitStringByCharacter(element,"#");
	 ConfigManager::splitStringByCharacterEx(element,"#", vcElements);
	std::vector<std::string>::iterator iter = vcElements.begin();
	for (; iter != vcElements.end(); iter++)
	{
		vector<std::string> vcElement;// = ConfigManager::splitStringByCharacter(*iter,"|");
		ConfigManager::splitStringByCharacterEx(*iter,"|", vcElement);
		int sz = vcElement.size();
		if(sz == 1)
		{
			continue;
		}
		StoryElement storyElement;
		storyElement.type = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		storyElement.id = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		storyElement.vis = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		storyElement.x = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		storyElement.y = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		storyElement.dir = atoi(vcElement.front().c_str());
		vcElement.erase(vcElement.begin());
		vcStoryElement.push_back(storyElement);
	}
	return vcStoryElement;
}

std::vector<StoryScript> StoryManager::createScript(std::string script)
{
	std::vector<StoryScript> vcStoryScript;
	std::vector<std::string> vcScripts;// = ConfigManager::splitStringByCharacter(script,"#");
	ConfigManager::splitStringByCharacterEx(script,"#", vcScripts);
	std::vector<std::string>::iterator iter = vcScripts.begin();
	for (;iter != vcScripts.end();iter++)
	{
		std::vector<std::string> vcScript;// = ConfigManager::splitStringByCharacter(*iter,"|");
		ConfigManager::splitStringByCharacterEx(*iter,"|", vcScript);
		int sz = vcScript.size();
		if(sz == 1)
		{
			continue;
		}

		StoryScript storyScript;
		storyScript.index = atoi(vcScript.front().c_str());
		vcScript.erase(vcScript.begin());
		storyScript.isNew = atoi(vcScript.front().c_str());
		vcScript.erase(vcScript.begin());
		storyScript.tox = atoi(vcScript.front().c_str());
		vcScript.erase(vcScript.begin());
		storyScript.toy = atoi(vcScript.front().c_str());
		vcScript.erase(vcScript.begin());
		if (!vcScript.empty())
		{
			storyScript.dialog = atoi(vcScript.front().c_str());
			vcScript.erase(vcScript.begin());
		}
		if (!vcScript.empty())
		{
			storyScript.dir = atoi(vcScript.front().c_str());
			vcScript.erase(vcScript.begin());
		}
		if (!vcScript.empty())
		{
			storyScript.duration = atoi(vcScript.front().c_str());
			vcScript.erase(vcScript.begin());
		}

		vcStoryScript.push_back(storyScript);		
	}
	return vcStoryScript;
}

void StoryManager::setStoryScriptType()
{
	std::map<int, StoryVo>::iterator iter = _storyDic.begin();
	for (iter;iter != _storyDic.end();iter++)
	{
		std::vector<StoryScript>::iterator itS = iter->second.script.begin();
		for (itS;itS != iter->second.script.end();itS++)
		{
			int type = iter->second.elemenet[itS->index].type;
			switch (type)
			{
			case 0:
				itS->type = PLAYER_TYPE;
				break;
			case 1:
				itS->type = NPC_TYPE;// or MONSTER_TYPE
				break;
			case 3:
				itS->type = ITEM_TYPE;
				break;
			default:
				itS->type = PLAYER_TYPE;
			}
		}
	}	
}