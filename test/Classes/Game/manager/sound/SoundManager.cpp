#include "SoundManager.h"
#include "events/GameDispatcher.h"
#include "model/player/RoleManage.h"
#include "model/scene/SceneManager.h"
#include "model/scene/vo/MusicVo.h"
#include "ActionPlayer.h"
#include "BaseType.h"
#include "model/config/ConfigManager.h"
#include "CCFileUtils.h"
#include "utils/Timer.h"

SoundManager::SoundManager()
{
	_pDispatcher = GameDispatcher::getInstance();
	_bNeedLoadBgMusic = false;
	_pShareEngine = SimpleAudioEngine::sharedEngine();
	_bBgToggle = true;
	_bEftToggle = true;
	_bActionToggle = true;
	_actionPlayer = 0;

    _szDefaultSoundURL = "assets/sound/background/1.mp3";
	_nCurBgMusicId = 226;
	setBackSoundvolume(0.7f);
	setEffectVolume(0.9f);
	setIsSoundOpen(false);
	setIsEffectOpen(false);
}

SoundManager::~SoundManager()
{
	if (_actionPlayer)
	{
		_actionPlayer->dispose();
	}
	CC_SAFE_DELETE(_actionPlayer);


	_pShareEngine->stopAllEffects();
	_pShareEngine->stopBackgroundMusic();
	_pShareEngine->stopBackgroundMusic(true);

	std::map< int, std::map<int,MusicVo*> >::iterator itMap;
	std::map<int,MusicVo*>::iterator itVo;
	for ( itMap = _typeDic.begin(); itMap != _typeDic.end(); itMap++ )
	{
		std::map<int,MusicVo*>& musicList = itMap->second;
		for ( itVo = musicList.begin(); itVo != musicList.end(); itVo++ )
		{
			CC_SAFE_DELETE( itVo->second );
		}
		musicList.clear();
	}
	_typeDic.clear();


	//CC_SAFE_DELETE(_pShareEngine); 
}

void SoundManager::roleMapChangeHandler(bool bLoop)
{
	int type = 1;
	int mapId = RoleManage::Instance()->roleInfo()->playerBaseInfo.GetmapId();
	//SceneVo * sceneVo = SceneManager::Instance()->getSceneDic(mapId);

	MusicVo * musicVo = getMusicVo(type, mapId);
	int musicId = 226;
	if(musicVo)
	{
		musicId = musicVo->musicId; 
	}
	_nCurBgMusicId = musicId;
	playBgMusic(musicId,bLoop);
}

void SoundManager::playBgMusic(int musicId,bool bLoop)
{
	_pShareEngine->stopBackgroundMusic();
	_pShareEngine->stopBackgroundMusic(true);
	_bNeedLoadBgMusic = true;
	if(_nCurBgMusicId == musicId)
	{
		_bNeedLoadBgMusic = false;
	}
	if(_bNeedLoadBgMusic)
	{ 
		closebgSound();
		_nCurBgMusicId = musicId;
		_nCount = 0;
		//LoadResManage.getInstance().start();
		char path[64] = {0};
		sprintf(path,"assets/sound/background/%d.%s",_nCurBgMusicId,AUDIO_FORMAT.c_str());

		std::string szPath(path);
        _szCurSoundURL = szPath;

		if (_pShareEngine)
		{
			_pShareEngine->preloadBackgroundMusic(path);
			_pShareEngine->playBackgroundMusic(path, bLoop);
			_pShareEngine->setBackgroundMusicVolume(getBackSoundVolValue());
		}
	}
	else
	{
		if(_bBgToggle)
		{
			char path[64] = {0};
			sprintf(path,"assets/sound/background/%d.%s",_nCurBgMusicId,AUDIO_FORMAT.c_str());
			std::string szPath(path);

			if (_pShareEngine)
			{
				_pShareEngine->preloadBackgroundMusic(path);
				_pShareEngine->playBackgroundMusic(path, bLoop);
				_pShareEngine->setBackgroundMusicVolume(getBackSoundVolValue());
			}
		}
		else
		{
			
		}
	}
}

void SoundManager::toggleBgSound(bool bToggle)
{
	_bBgToggle = bToggle;
	toggleActionMusic(bToggle); // close the action effect

	if (_bBgToggle)
	{
		_pShareEngine->setBackgroundMusicVolume(getBackSoundVolValue());
	}
	else
	{
		_pShareEngine->setBackgroundMusicVolume(0);
	}
}

void SoundManager::playAction(std::string path, bool loop)
{
	if(!_bActionToggle)return;

	if (!_actionPlayer)
	{
		_actionPlayer = new ActionPlayer();
	}

	if(_actionPlayer)
	{
		//_pShareEngine->stopAllEffects();
		//_actionPlayer->dispose();
		_actionPlayer->play(path,loop);
	}
}

void SoundManager::setBackSoundvolume(float fValue)
{
	setBackSoundVolValue(fValue);
	_pShareEngine->setBackgroundMusicVolume(fValue);
}

void SoundManager::setEffectVolume(float fValue)
{
	setEffectVolValue(fValue);
	_pShareEngine->setEffectsVolume(fValue);
}

void SoundManager::toggleActionMusic(bool bValue)
{
	_bActionToggle = bValue;
	if(_pShareEngine)
	{
		if(_bActionToggle)
		{
			if (_actionPlayer)
			{
				_actionPlayer->resume();
			}
		}
		else
		{
			if (_actionPlayer)
			{
				_actionPlayer->pause();
			}
		}
	}
}

void SoundManager::closebgSound()
{
	if (_pShareEngine)
	{
		_pShareEngine->stopBackgroundMusic();
	}
}


void SoundManager::setMusic(std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> > & typeDic)
{
	_typeDic = typeDic;
}

MusicVo * SoundManager::getMusicVo(int type,int mapId)
{
// 	if (_typeDic.empty())
// 	{
// 		g_pConfigManager->loadMusicXML(CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/music.xml"));
// 	}
	std::map<int/*type*/,std::map<int/*mapId*/,MusicVo*> >::iterator iter = _typeDic.find(type);
	if(iter != _typeDic.end())
	{
		int m_mapId = mapId;
		if(type == 2)
		{
			m_mapId = 1001;
		}
		std::map<int/*mapId*/,MusicVo*>::iterator it = iter->second.find(m_mapId);
		if (it != iter->second.end())
		{
			return it->second;
		}
	}
	return 0;
}

void SoundManager::playButtonEffectSound()
{
	if (getIsEffectOpen())
	{
		playAction("assets/sound/effect/btn1.wav");
	}
}

void SoundManager::playPopContainerEffectSound()
{
	if (getIsEffectOpen())
	{
		playAction("assets/sound/effect/pop.wav");
	}
}

void SoundManager::playBagItemEffectSound()
{
	if (getIsEffectOpen())
	{
		playAction("assets/sound/effect/equip3.wav");
	}
}

void SoundManager::playOpenBoxEffectSound()
{
	if (getIsEffectOpen())
	{
		playAction("assets/sound/effect/openbox.wav");
	}
}

void SoundManager::playBattleBgSound()
{
	srand(Timer::millisecondNow());
	int var = rand()%5;
	int musicId = var+300;
	_nCurBgMusicId = musicId;
	playBgMusic(musicId,true);
}

void SoundManager::stopBattleBgSound()
{
	if (getIsSoundOpen())
	{
		roleMapChangeHandler(false);
	}
}
