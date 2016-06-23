#include "MetaConfigure.h"
#include "utils/xml/tinyxml.h"
#include "CCFileUtils.h"
#include "cocos2d.h"
#include "utils/Utils.h"

USING_NS_CC;

class MetaRepository
{
public:
	static MetaRepository &theRepository();
	void parse(const char *path, Md5Info *info);
};

MetaRepository &MetaRepository::theRepository()
{
	static MetaRepository theRepository;
	return theRepository;
}

void MetaRepository::parse(const char *file, Md5Info *out)
{
	cocos2d::CCFileData data(file, "rb");

	TiXmlDocument doc;
	CCLog("begin to parse time = %ld", time(NULL));
	doc.Parse((const char *)data.getBuffer());
	CCLog("end parse time = %ld", time(NULL));
	if (doc.Error())
	{
		CCLog("can't parse clam configure file: %s", file);
		assert(false);
		return;
	}

	CCLog("begin to set value time = %ld", time(NULL));
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* item = root->FirstChildElement();
	for (; item != NULL; item = item->NextSiblingElement())
	{
		Md5Info *temMd5 = new Md5Info();
		TiXmlElement* child = item->FirstChildElement();
		temMd5->setFilePathName(child->GetText());

		child = child->NextSiblingElement();
		temMd5->setFileMd5Value(child->GetText());

		child = child->NextSiblingElement();
		if (atoi(child->GetText()) == 1)
		{
			temMd5->setIsFile(true);
		} else
		{
			temMd5->setIsFile(false);
		}

		child = child->NextSiblingElement();
		temMd5->setFileUri(child->GetText());

		vector<string> paths = split(temMd5->getFilePathName(), "/");
		if (paths.size() == 1)
		{
			*out = *temMd5;
		} else
		{
			out->addChild(out, temMd5);
		}		
	}
	CCLog("end set value time = %ld", time(NULL));
}

void parseMd5(const char *file, Md5Info *out)
{
	MetaRepository::theRepository().parse(file, out);
}
