#ifndef _NAME_MANAGER_H_ 
#define _NAME_MANAGER_H_

#include "BaseType.h"
#include "utils/Singleton.h"

USING_NS_CC;

class Namemanager : public Singleton<Namemanager>
{
public:
	Namemanager();
	virtual ~Namemanager(){}

	std::string randomName(int sex);
	int getRandomPos(int size);

public:

	std::map<int,std::vector<std::string> > _firstMale;
	std::map<int,std::vector<std::string> > _secondNoThirdMale;
	std::map<int,std::vector<std::string> > _secondMale;
	std::map<int,std::vector<std::string> > _thirdMale;

	std::map<int,std::vector<std::string> > _firstFemale;
	std::map<int,std::vector<std::string> > _secondNoThirdFemale;
	std::map<int,std::vector<std::string> > _secondFemale;
	std::map<int,std::vector<std::string> > _thirdFemale;
};

#endif