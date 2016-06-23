#ifndef _HonorProxy_H_
#define _HonorProxy_H_

#include "mvc/Proxy.h"
#include "socket/command/s14/SCMD140.h"
#include "socket/command/s14/SCMD142.h"
#include "vo/HonorScheduleManage.h"

class HonorProxy: public Proxy
{
public:
	HonorProxy();
	~HonorProxy();
	void updateHonorList(SCMD140* cmd);
	void handleHonorList(SCMD142* arr);
	void createList(SCMD142* arr);

public:
	bool _isCreated;
	map<int, HonorObject*> _honorList;
};

#endif