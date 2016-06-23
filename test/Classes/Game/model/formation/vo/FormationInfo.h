#ifndef _FORMATIONINFO_H_
#define _FORMATIONINFO_H_
#include "BaseType.h"

class FormationInfo
{
	/**Formation information
		 * 
		 * 
		 */	
private:
	uint32 id;    //formation id
public:
	FormationInfo();
	~FormationInfo();
	uint32 lev;   //Formation level
	bool active;   //Whether opening
	std::map<int, int>  figuresMap;   //The formation of characters has arrangement, key: grid (1 ~ 9), value: people Numbers
	
	uint32 getId() 
	{
		return this->id;
	}
	void setId(uint32 val) 
	{
		this->id = val;
	}


};


#endif