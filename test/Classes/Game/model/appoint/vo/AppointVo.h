#ifndef _APPOINT_VO_H_
#define _APPOINT_VO_H_

class AppointVo
{
public:
	int id;					//商人的编号0~7
	int type;				//商人类型 0：戒指商人， 1：披风商人
	int level;				//商人等级 0~3
	std::string name;		//商人名字
	std::string info;		//商人信息
	int silver;				//委派需要的银币
	int gold;				//委派需要的金币
	std::string icon;		//商人头像

	/** =========以上信息从配置文件读取========== */

	bool isGoldAppoint;		//是否金币委派
	int freeNum;			//剩余免费委派次数
	int bitNum;				//用bit位表示的商人信息

};
#endif