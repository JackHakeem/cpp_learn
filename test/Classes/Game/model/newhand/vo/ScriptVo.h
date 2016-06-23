#ifndef _SCRIPT_VO_H_
#define _SCRIPT_VO_H_

#include "BaseType.h"

class ScriptVo
{
public:
	ScriptVo() {}
	~ScriptVo() {}

	int id;
	int taskId;
	int clear;
	std::vector<string> trigger;

	string loc;
	int locId;
	int arrow;
	//		 arrow_x;
	//		 arrow_y;
	//		
	//		 rect_x;
	//		 rect_y;
	//		 rect_w;
	//		 rect_h; 
	int locType;
	int typeId;
	bool isFlyEffect;
	string info;
	int next_id;
};
#endif