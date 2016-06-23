#include "CheckRes.h"
#include <iostream>
#include <fstream>
#include "cocos2d.h"
#include "MetaConfigure.h"
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
#include "../platform/android/jni/SystemInfoJni.h"
#endif
using namespace std;
USING_NS_CC;

void checkRes()
{
	Md5Info *localMd5 = new Md5Info(); 
	Md5Info *remoteMd5 = new Md5Info();

	parseMd5("meta.xml", localMd5);
	parseMd5("remoteMeta.xml", remoteMd5);

	CCLog("begin to cmp res ...");
	cmpRes(localMd5, remoteMd5);
	CCLog("com res ended.");
	writeInfoToFile();

	delete localMd5;
	delete remoteMd5;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//extern void doCheckResFinish();
	//doCheckResFinish();
#endif
}

void cmpRes(Md5Info *local, Md5Info *remote)
{
	if (strcmp(local->getFileMd5Value().c_str(), remote->getFileMd5Value().c_str()) == 0)
	{
		CCLog("file %s remain same", local->getFilePathName().c_str());
		return;
	} else {
		for (std::tr1::unordered_map<string, Md5Info *>::iterator iter = remote->m_childInfos.begin();
			iter != remote->m_childInfos.end(); iter++)
		{
			//ÐÂÔö
			if (local->getChild(local, iter->first) == NULL)
			{
				CCLog("new file add %s", iter->second->getFilePathName().c_str());
				resAddNode(iter->second);
			}
			else if (strcmp(local->getChild(local, iter->first)->getFileMd5Value().c_str(), 
				iter->second->getFileMd5Value().c_str()) != 0)
			{
				CCLog("file %s update", iter->first.c_str());

				s_infos.push_back(new ResUpdateInfo(ResUpdateInfo::kUpdateState,
					iter->second->getFilePathName(), iter->second->getFileUri(), iter->second->getIsFile()));
				if (!local->getChild(local, iter->first)->getIsFile())
				{
					cmpRes(local->getChild(local, iter->first), iter->second);
				}
			}
			else
			{
				CCLog("remain same %s", iter->first.c_str());
			}
		}
		
		for (std::tr1::unordered_map<string, Md5Info *>::iterator iter = local->m_childInfos.begin();
			iter != local->m_childInfos.end(); iter++)
		{
			if (remote->getChild(remote, iter->first) == NULL)
			{
				CCLog("file %s removed", iter->first.c_str());
				resDeleteNode(iter->second);
			}
		}
	}
}

void resAddNode(Md5Info *node)
{
	CCLog("file %s added", node->getFilePathName().c_str());
	s_infos.push_back(new ResUpdateInfo(ResUpdateInfo::kNewState, 
		node->getFilePathName(), node->getFileUri(), node->getIsFile()));
	if (node->getIsFile())
		return;

	for(std::tr1::unordered_map<string , Md5Info *>::iterator iter = node->m_childInfos.begin();
		iter != node->m_childInfos.end(); iter++)
	{
		resAddNode(iter->second);
	}
}

void resDeleteNode(Md5Info *node)
{
	if (node->getIsFile())
	{
		s_infos.push_back(new ResUpdateInfo(
			ResUpdateInfo::kRemoteState, node->getFilePathName(), node->getFileUri(), node->getIsFile()));
		CCLog("file %s deleted", node->getFilePathName().c_str());
		return;
	}

	for (std::tr1::unordered_map<string , Md5Info *>::iterator iter = node->m_childInfos.begin();
		iter != node->m_childInfos.end(); iter++)
	{
		resDeleteNode(iter->second);
	}

	s_infos.push_back(new ResUpdateInfo(
		ResUpdateInfo::kRemoteState, node->getFilePathName(), node->getFileUri(), node->getIsFile()));
	CCLog("file %s deleted", node->getFilePathName().c_str());
}

void writeInfoToFile()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	ofstream in;
    char s[128];
    snprintf(s, sizeof(s), "%s/check_result.txt", getExternalStoragePath());    
	in.open(s, ios::trunc);

	for (int i = 0; i < s_infos.size(); i++)
	{
		in<<s_infos[i]->getState()<<",";
		in<<s_infos[i]->getPath().c_str()<<",";
		in<<s_infos[i]->getUri()<<",";
		in<<s_infos[i]->getIsFile()<<"\n";
	}
	in.close();
#endif
}
