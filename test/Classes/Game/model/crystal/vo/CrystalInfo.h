#ifndef HLQS_CrystalInfo_H_
#define HLQS_CrystalInfo_H_
#include "BaseType.h"



class CrystalInfo
{
public:
	CrystalInfo();
	virtual ~CrystalInfo();

public:
	int id;			
	std::string name;
	int level;		
	std::string tip;	
	std::string des;	
	int time;			
};

#endif