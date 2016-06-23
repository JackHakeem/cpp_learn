#ifndef _SOUND_SET_LAYER_H_
#define _SOUND_SET_LAYER_H_

#include "cocos2d.h"
#include "LayerNode.h"
#include "SpriteNode.h"

USING_NS_CC;

class SpriteNode;
class CCUIBackground;

class SoundSetLayer : public LayerNode
{
public:
	SoundSetLayer();
	virtual bool init();
	void loadSlipItems();
	void loadButtonItems();

	void clickSoundButton(CCObject * pSender);
	void clickEffectButton(CCObject * pSender);

public:
	CCSize _winSize;
	CCSize _progressSize;
	SpriteNode * _pSoundVolumeProgressBack;
	CCProgressTimer * _pSoundVolumeProgress;
	SpriteNode * _pSoundVolumeSlipButton;

	SpriteNode * _pEffectVolumeProgressBack;
	CCProgressTimer * _pEffectVolumeProgress;
	SpriteNode * _pEffectVolumeSlipButton;

	float _fCurSoundVolume;
	float _fCurEffectVolume;

	CCPoint _spriteSoundPoint;
	CCPoint _spriteSoundBtnPoint;
	CCPoint _spriteEffectPoint;
	CCPoint _spriteEffectBtnPoint;
	CCPoint _preTouchPoint;

	int _nCurMapID;

	enum
	{
		TAG_SOUND_PROGRESS_BG = 0,
		TAG_EFFECT_PROGRESS_BG,
		TAG_SOUND_BTN,
		TAG_EFFECT_BTN,
	};

	enum
	{
		TAG_PROGRESS = 0,
		TAG_SLIP_BTN,
	};

	enum
	{
		STAT_SOUND_0 = 0,
		STAT_SOUND_1,
		STAT_SOUND_2,
		STAT_SOUND_3,
	};

	enum
	{
		STAT_EFFECT_0 = 0,
		STAT_EFFECT_1,
		STAT_EFFECT_2,
		STAT_EFFECT_3,
	};

	CC_SYNTHESIZE(int,touchSoundState,TouchSoundState)
	CC_SYNTHESIZE(int,touchEffectState,TouchEffectState)
	CC_SYNTHESIZE(bool,isSoundOpen,IsSoundOpen)
	CC_SYNTHESIZE(bool,isEffectOpen,IsEffectOpen)

public:
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

protected:
private:
};

#endif