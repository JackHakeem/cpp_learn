#ifndef _CAMPFIGHTMEDIATOR_H_
#define _CAMPFIGHTMEDIATOR_H_
#include "view/BaseMediator.h"
#include "components/CampFightView.h"
#include "socket/command/s45/SCMD45B.h"
#include "socket/command/s45/SCMD459.h"

class CampFightMediator : public BaseMediator
{
public:
	enum
	{
		UPDATE_CAMPFIGHT,
		UPDATE_MY_INFO_VIEW,

	};
	CampFightMediator();
	~CampFightMediator();
	virtual void handleNotification(int M2Vcmd, char* data);
	//ApplyRes申请打开阵营战服务端返回值
	void OpenCampFightView(int32 ApplyRes);
	void CloseCampFightView(int32 ApplyRes);
	void UpdateCampFightSceneInfo(SCMD45B* pPacket);
	void UpdateMyInfo(SCMD459* pPacket);
private:
	void UpdateCamp();
	void UpdateMyInfo();

	CampFightView* m_pCampFightView;
};
#endif