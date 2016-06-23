#include "ActionPlayer.h"
#include "events/GameDispatcher.h"
#include "SoundManager.h"

ActionPlayer::ActionPlayer()
{
	_szLoadUrl = "";
	_bToggle = false;
	_pDispatcher = GameDispatcher::getInstance();
	_pShareEngine = 0;
	_pShareEngine = SimpleAudioEngine::sharedEngine();
	//SimpleAudioEngine * _pShareEngine = SimpleAudioEngine::sharedEngine();
}

ActionPlayer::~ActionPlayer()
{
	_pShareEngine->stopEffect(_nSoundId);
	_pShareEngine->stopAllEffects();
	_pShareEngine->unloadEffect(_szLoadUrl.c_str());

	//CC_SAFE_DELETE(_pDispatcher);
	//CC_SAFE_DELETE(_pShareEngine);

	// LH0812
	std::vector<std::string>::iterator iter;
	for (iter = _effectPathDic.begin();iter != _effectPathDic.end();iter++)
	{
		_pShareEngine->unloadEffect(_effectPathDic.front().c_str());
		iter = _effectPathDic.erase(_effectPathDic.begin());
	}
	_effectPathDic.clear();
}

void ActionPlayer::load()
{
	_pShareEngine->preloadEffect(_szLoadUrl.c_str());
	//Doyang
	//_pShareEngine->preloadEffect("assets/sound/skill/33.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/28.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/3.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/26.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/39.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/63.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/45.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/17.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/2.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/27.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/67.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/79.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/42.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/11.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/6.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/4.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/61.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/24.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/49.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/65.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/106.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/75.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/104.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/55.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/5.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/105.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/53.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/1.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/13.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/81.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/10.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/56.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/74.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/103.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/101.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/69.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/83.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/52.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/15.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/66.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/16.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/37.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/77.mp3");
	//_pShareEngine->preloadEffect("assets/sound/skill/102.mp3");
}

void ActionPlayer::play(std::string path,bool bLoop)
{
	//_pShareEngine->unloadEffect(_szLoadUrl.c_str());

	if (_effectPathDic.size() > 1)	{
		std::vector<std::string>::iterator iter = _effectPathDic.begin();
		for (;iter != _effectPathDic.end();)
		{
			++iter;
			if (iter == _effectPathDic.end())
			{
				break;
			}
			else
			{
				--iter;
			}
			_pShareEngine->unloadEffect(_effectPathDic.front().c_str());
			iter = _effectPathDic.erase(_effectPathDic.begin());
		}
	}

	_effectPathDic.push_back(path);

    _szLoadUrl = path;

	load();
	_nSoundId = _pShareEngine->playEffect(_szLoadUrl.c_str(),bLoop);
	_pShareEngine->setEffectsVolume(SoundManager::Instance()->getEffectVolValue());
}

void ActionPlayer::pause()
{
	_pShareEngine->pauseEffect(_nSoundId);
}

void ActionPlayer::replay()
{

}

void ActionPlayer::resume()
{
	_pShareEngine->resumeEffect(_nSoundId);
}

void ActionPlayer::close()
{
	_pShareEngine->stopEffect(_nSoundId);
}

void ActionPlayer::dispose()
{
	close();

	_pShareEngine->stopAllEffects();

	if ( !_szLoadUrl.empty() )//jae not test yet
	{
		_pShareEngine->unloadEffect(_szLoadUrl.c_str());
	}

	std::vector<std::string>::iterator iter = _effectPathDic.begin();
	for (;iter != _effectPathDic.end();iter++)
	{
		_pShareEngine->unloadEffect(_effectPathDic.front().c_str());
	}
	_effectPathDic.clear();
}
