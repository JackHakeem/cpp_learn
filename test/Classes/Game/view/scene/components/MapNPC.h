#ifndef _MAPNPC_H
#define _MAPNPC_H

#include "model/scene/vo/NPCVo.h"
#include "utils/Timer.h"
#include "utils/BitmapMovieClip.h"
#include "LiveThing.h"
#include "model/scene/vo/GMProgessVo.h"

class MapNPC : public LiveThing
{
public:
	MapNPC();
	MapNPC( NPCVo* pNPCVo );
	~MapNPC();
	
	CCSprite * loadNpc();
	CCSprite * getNpcSprite();
	void playAnimation();
	void stopAnimation();

	void npcMove(char** map_desc, int &h, int &w);

	// NPC Talk
	bool addNPCTalk();
	bool getTalkVisible();
	void setTalkVisible( bool bVar );
	bool canTalk();
	int action();

	Timer* m_TalkVisibleTimer;

	void icon( int ico );
	virtual void layout();

	ccColor3B color();
	void color(ccColor3B value);
	void name(const char* name);
	virtual void poseChange();
	void movePath(std::vector<CCPoint> path, int delay = 0);
	void moveTo(CCPoint point, int delay = 0);
	virtual void moveComplete();
	void completeHandler();
	void init();
	void showRes();
	virtual void updateAction(bool repeat = true);
	virtual bool toAttack();
	virtual bool toHited(bool iscrit = false);
	virtual void updateInfo();
	virtual void dispose();

	//Begin Kenfly 20121106 : load model async
public:
	void loadModel();
	//End Kenfly 20121106
public:
	int m_direction;

	vector<CCPoint> m_path; // for tmp;
	vector<CCPoint> _path;
	NPCVo* _npcVo;
	bool m_bCanTalk;

	CCTexture2D* m_pTexureCanRecvTask;
	CCTexture2D* m_pTexureCanFinishTask;
	CCTexture2D* m_pTexureNoFinishTask;
	std::string _assetURL;
	virtual bool isHit(CCPoint point);
	ccColor3B _ccNameTextColor;
	CCLabelTTF* _label;
	int timer;
};
#endif