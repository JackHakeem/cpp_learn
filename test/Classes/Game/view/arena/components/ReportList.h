#pragma once

#include "BaseType.h"
#include "socket/command/s36/SCMD361Node2.h"

class ArenaUI;
class ReportList:public LayerNode
{
public:
	enum
	{
		ReportListZ_menu,
		ReportListZ_msg0,
		ReportListZ_msg1,
	};

	enum
	{
		ReportListTAG_menu,
		ReportListTAG_msg0,
		ReportListTAG_msg1,
	};

	ReportList();
	~ReportList();

	bool initWithParam(ArenaUI* pContainer);
	void update(std::vector<SCMD361Node2>& array);
	void createItem(SCMD361Node2 data, int sitNum);
public:
	ArenaUI* _pContainer;


//Begin chenjian 20121018 add list data
private:
	void onSelectReport(CCObject* pSender);
	std::vector<SCMD361Node2> _data;
//End chenjian 20121018
};