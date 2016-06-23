#ifndef _ACTION_PLAYER_H_
#define _ACTION_PLAYER_H_

#include "cocos2d.h"
#include "events/GameDispatcher.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

//class SimpleAudioEngine;
class ActionPlayer : public CCIEventDispatcher
{
public:
	ActionPlayer();
	virtual ~ActionPlayer();

	void load();
	void play(std::string path,bool bLoop);
	void replay();
	void pause();
	void resume();
	void close();
	void dispose();

public:
	SimpleAudioEngine * _pShareEngine;     
	GameDispatcher * _pDispatcher;
	std::string _szLoadUrl;

	bool _bToggle;
	int _nActionPosition;

	unsigned int _nSoundId;

	std::vector<std::string> _effectPathDic;

protected:
private:
};

#endif