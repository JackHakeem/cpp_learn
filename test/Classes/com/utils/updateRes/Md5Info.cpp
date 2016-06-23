#include "Md5Info.h"
#include <vector>
#include "utils/Utils.h"

using namespace std;
Md5Info::Md5Info()
{
}


Md5Info::~Md5Info()
{
	for (std::tr1::unordered_map<string, Md5Info *>::iterator iter = m_childInfos.begin();
		iter != m_childInfos.end(); iter++)
	{
		delete iter->second;
	}
}

void Md5Info::setIsFile(bool isFile)
{
	m_isFile = isFile;
}

bool Md5Info::getIsFile()
{
	return m_isFile;
}

void Md5Info::setFilePathName(const string &name)
{
	m_filePathName = name;
}

const string &Md5Info::getFilePathName()
{
	return m_filePathName;
}

void Md5Info::setFileMd5Value(const string &value)
{
	m_fileMd5Value = value;
}

const string &Md5Info::getFileMd5Value()
{
	return m_fileMd5Value;
}

void Md5Info::setFileUri(const string &uri)
{    
	m_fileUri = uri;
}

const string &Md5Info::getFileUri()
{
	return m_fileUri;
}

const std::tr1::unordered_map<string, Md5Info *> &Md5Info::getChildren()
{
	return m_childInfos;
}

void Md5Info::addChild(Md5Info *parent, Md5Info *info)
{
	std::vector<string> paths = split(info->getFilePathName(), "/");
	string parentKey = info->getFilePathName().substr(
		0, info->getFilePathName().length() - paths[paths.size() - 1].length() - 1);

	if (paths.size() == 2)
	{
		parent->m_childInfos.insert(std::make_pair(info->getFilePathName(), info));
		return;
	}

	string key = paths[0] + "/" + paths[1];
	Md5Info *tem;
	if (parent->m_childInfos.find(key) != parent->m_childInfos.end())
		tem = parent->m_childInfos.find(key)->second;

	for (int i = 2; i < paths.size(); i++)
	{
		key += "/" + paths[i];
		if (tem->m_childInfos.find(key) == tem->m_childInfos.end() || tem->m_childInfos.size() == 0)
		{
			tem->m_childInfos.insert(std::make_pair(info->getFilePathName(), info));
			return;
		} else
		{
			tem = tem->m_childInfos.find(key)->second;
		}
	}
}

Md5Info *Md5Info::getChild(Md5Info *info, const string &key)
{
	Md5Info *md5Info = NULL;
	vector<string> paths1 = split(info->getFilePathName(), "/");
	vector<string> paths2 = split(key, "/");
	string temkey = info->getFilePathName();

	temkey += "/" + paths2[paths1.size()];

	if (info->m_childInfos.find(temkey) != info->m_childInfos.end())
		md5Info = info->m_childInfos.find(temkey)->second;

	for (int i = paths1.size() + 1; i < paths2.size(); i++)
	{
		temkey += "/" + paths2[i];
		md5Info = md5Info->m_childInfos.find(temkey)->second;
	}

	return md5Info;
}

