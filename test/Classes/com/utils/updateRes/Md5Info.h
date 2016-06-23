#ifndef MHXJ_MODEL_MD5_INFO_H__
#define MHXJ_MODEL_MD5_INFO_H__
#include <string>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif


class Md5Info
{ 
public:
	Md5Info();
	~Md5Info();

	void setIsFile(bool isFile);
	bool getIsFile();
	void setFilePathName(const std::string &name);
	const std::string &getFilePathName();
	void setFileMd5Value(const std::string &value);
	const std::string &getFileMd5Value();
	void setFileUri(const std::string &uri);
	const std::string &getFileUri();
	const std::tr1::unordered_map<std::string, Md5Info *> &getChildren();
	 
	void addChild(Md5Info *parent, Md5Info *info);
	Md5Info *getChild(Md5Info *info, const std::string &key);

	std::tr1::unordered_map<std::string, Md5Info *> m_childInfos;
private:
	bool m_isFile;
	std::string m_filePathName;
	std::string m_fileMd5Value;
	std::string m_fileUri;
	
};

#endif

