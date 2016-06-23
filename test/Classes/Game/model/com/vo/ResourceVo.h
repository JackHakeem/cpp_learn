#ifndef _RESOURCEVO_H 
#define _RESOURCEVO_H 

#include "BaseType.h"

struct ResVoPoint
{
	ResVoPoint()
	{
		x = 0; y = 0;
	}
	int8 x;
	int8 y;
};

class ResourceVo
{
public:
	 

	ResourceVo():type(0),id(0),timer(0),nameY(0),offsety(0),pose(0),actzhen(0),acttime(0)
	{
	}
	~ResourceVo(){}

	int type; // type 1 for model 2 for skills
	int id; // res_id
	int timer; // frequency-1 press frame frequency no in time
	int nameY; // name y-coordinate
	int offsety; // relative to nameY coordinate if for 0, then don't do calculation
	int actzhen;
	float acttime; 
	std::string blendMode;
	int pose;
	ResVoPoint offset[32];//4个动作

	std::string sBodyUrl;
	std::string sHalfBodyUrl;
	//std::string skillUrl;

	float getAttackingMCStartDelay()
	{
		return actzhen*acttime;
	}

	std::string modelUrl()
	{
		char tmp[64] = {0};
		std::string s = "assets/res/%d";
		sprintf(tmp, s.c_str(), id);
		std::string tmp_str(tmp);

		return tmp_str;
	}
	//	
	//std::string getswfUrl(){
	//	return "assets/res/"+id+"/model.swf";
	//}
	//	
	//
	//std::string geticonUrl(){ 
	//	return "assets/res/"+id+"/icon.png";
	//}

	void setUrl()
	{
		char str[128];
		sprintf( str, "assets/res/%d/body.png", id );
		sBodyUrl = str;
		sprintf( str, "assets/res/%d/halfbody.png", id );
		sHalfBodyUrl = str;
		//sprintf( str, "assets/mapassets/simpleskill", id );
		//skillUrl = "assets/mapassets/simpleskill";
	}
		
	/**
		* 全身
		* @return 
		* 
		*/		
	std::string bodyUrl(){
		return sBodyUrl;
	}
		
	/**
		* 半身 
		* @return 
		* 
		*/		
	std::string gethalfBodyUrl(){
		return sHalfBodyUrl;
	}

	//std::string  getSkillUrl()
	//{
	//	return skillUrl;
	//	//if(id==1 || id==5) return "assets/mapassets/simpleskill/"+id+".swf";
	//	//if(600<=id && id<=610) return "assets/mapassets/simpleskill/"+id+".swf"; 
	//	//return "assets/mapassets/simpleskill/"+id+".dg"; // 
	//}
			
		
};

#endif
