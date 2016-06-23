#ifndef _LEAD_ARROW_H_
#define _LEAD_ARROW_H_
#include "LayerNode.h"

class LeadArrow : public LayerNode
{
public:
	LeadArrow(int arrow_dir, int x, int y, string info);
	~LeadArrow() {}

	void createTipStyle(int arrow_dir, string info);
	void createGoStyle(int arrow_dir);
	void createSingleArrowStyle(int arrow_dir, string info);

	int getLineNum(std::string strText, float fontSize , float lineWidth);
};
#endif