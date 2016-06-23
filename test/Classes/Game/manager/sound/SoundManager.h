#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_
#include "cocos2d.h"
#include "model/scene/vo/MusicVo.h"
#include "utils/Singleton.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

#define MAX_MUSIC_LOOP (65535)

class GameDispatcher;
class ActionPlayer;
class SoundManager : public Singleton<SoundManager>, public CCIEventDispatcher
{
public:
	SoundManager();
	virtual ~SoundManager();

	void roleMapChangeHandler(bool bLoop);
	void playBgMusic(int musicId = 226,bool nLoop = false);
	void toggleBgSound(bool bToggle);

	void playAction(std::string path,bool loop = false);
	void toggleActionMusic(bool bValue);
	void closebgSound();

	void setBackSoundvolume(float fValue);
	void setEffectVolume(float fValue);

	void playButtonEffectSound();
	void playPopContainerEffectSound();
	void playBagItemEffectSound();
	void playOpenBoxEffectSound();

	void playBattleBgSound();
	void stopBattleBgSound();

	void setMusic(std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > & typeDic);
	MusicVo * getMusicVo(int type,int mapId);

public:
	CC_SYNTHESIZE(bool,isSoundOpen,IsSoundOpen)
	CC_SYNTHESIZE(bool,isEffectOpen,IsEffectOpen)
	CC_SYNTHESIZE(float,backSoundVolValue,BackSoundVolValue)
	CC_SYNTHESIZE(float,effectVolValue,EffectVolValue)

	SimpleAudioEngine * _pShareEngine;     
	GameDispatcher * _pDispatcher;
	int _nPid;
	bool _bNeedLoadBgMusic;
	int _nCount;

	std::string _szDefaultSoundURL;
	std::string _szCurSoundURL;
	//private var _bgSound:Sound;
	//private var _bgSoundChannel:SoundChannel;
	int _nCurBgMusicId;
	int _nCurBattleBgMusicId;
	bool _bBgToggle;
	int _bBgPosition;
	//private var _effectSound:Sound;
	//private var _eftSoundChannel:SoundChannel;
	int _nEftMusicId;
	bool _bEftToggle;

	bool _bActionToggle;

	ActionPlayer * _actionPlayer;

	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > _typeDic;

	int _nCurMapID;
};

#endif