#include "NPCChat.h"
#include "chat/WhisperContainer.h"
#include "chat/LeftChatContainer.h"
#include "chat/RightChatContainer.h"
#include "LiveThing.h"
#include "utils/ScaleUtil.h"

NPCChat::NPCChat(int disppearTime, int color)
{
	/*_whisperContainer = 0; 
	_leftChatContainer = 0;
	_rightChatContainer = 0;*/
	this->setAnchorPoint(ccp(0.5,0.0));
}

NPCChat::~NPCChat()
{
	//Doyang 20120713
	this->removeChildByTag(TAG_LEFTCONTAIN, true);
	this->removeChildByTag(TAG_RIGHTCONTAIN, true);
	this->removeChildByTag(TAG_WHISCONTAIN, true);
}

void NPCChat::hideDialog()
{
	//if(_whisperContainer)
	//{
	//	if(this->getChildByTag(TAG_WHISCONTAIN))
	//	{
	//		//this->removeChild(_whisperContainer,true);
	//		this->removeChildByTag(TAG_WHISCONTAIN,true);
	//	}
	//}
	//if(_leftChatContainer)
	//{
	//	if(this->getChildByTag(TAG_LEFTCONTAIN))
	//	{
	//		//this->removeChild(_leftChatContainer,true);
	//		this->removeChildByTag(TAG_LEFTCONTAIN,true);
	//	}
	//}
	//if(_rightChatContainer)
	//{
	//	if(this->getChildByTag(TAG_RIGHTCONTAIN))
	//	{
	//		//this->removeChild(_rightChatContainer,true);
	//		this->removeChildByTag(TAG_RIGHTCONTAIN,true);
	//	}
	//}

	this->removeChildByTag(TAG_LEFTCONTAIN, true);
	this->removeChildByTag(TAG_RIGHTCONTAIN, true);
	this->removeChildByTag(TAG_WHISCONTAIN, true);
	this->setIsVisible(false);

}

void NPCChat::showContent(struct _VOICE_ *vo)
{
	if (!vo)
	{
		return;
	}

	_VOICE_ * voice = (_VOICE_ *)vo;
	this->setIsVisible(true);
	switch(voice->style)
	{
	case 1:  // 
		//whisper(voice->content);
		talk(voice->content, voice->name, voice->id, voice->style);
		break;
	case 2:  // 
		talk(voice->content, voice->name, voice->id, voice->style);
		break;
	case 3:  //  
		talk(voice->content, voice->name, voice->id, voice->style);
		break;
	case 4: // 
		//whisper(voice->content);
		talk(voice->content, voice->name, voice->id, voice->style);
		break;
	}
}

void NPCChat::whisper(std::string content)
{

	//Doyang 20120712
	_VOICE_ *_voice = new _VOICE_();
	_voice->content = content;
	WhisperContainer *pWhisperContainer = (WhisperContainer *) this->getChildByTag(TAG_WHISCONTAIN);

	if(!pWhisperContainer)
	{
		pWhisperContainer = new WhisperContainer();
		pWhisperContainer->init();
		pWhisperContainer->setPosition(POSX(0),POSX(100));
		this->addChild(pWhisperContainer, Z_LEFTCONTAIN, TAG_WHISCONTAIN);
		pWhisperContainer->release();
	}
	if(pWhisperContainer)
		pWhisperContainer->showContent(_voice);

	CC_SAFE_DELETE(_voice);
}

void NPCChat::talk(std::string content,std::string name, int id, int style)
{
	//var rand:Number = Math.random();
	//			style = rand>0.8?2:3;
	_VOICE_ *_voice = new _VOICE_();
	_voice->content = content;
	_voice->name = name;
	_voice->id = id;
	_voice->style = style;

	switch(style)
	{
	case 2:
		{
			//Doyang 20120712
			LeftChatContainer *pLeftChatContainer = (LeftChatContainer *) this->getChildByTag(TAG_LEFTCONTAIN);

			if(!pLeftChatContainer)
			{
				pLeftChatContainer = new LeftChatContainer();
				pLeftChatContainer->init();
				pLeftChatContainer->setPosition(POSX(-20),POSX(100));
				this->addChild(pLeftChatContainer, Z_LEFTCONTAIN, TAG_LEFTCONTAIN);
				pLeftChatContainer->release();
			}
			if(pLeftChatContainer)
				pLeftChatContainer->showContent(_voice);
		}
		break;

	case 3:
	default:
		{
			//Doyang 20120712
			RightChatContainer *pRightChatContainer = (RightChatContainer *) this->getChildByTag(TAG_RIGHTCONTAIN);

			if(!pRightChatContainer)
			{
				pRightChatContainer = new RightChatContainer();
				pRightChatContainer->init();
				pRightChatContainer->setPosition(POSX(110),POSX(100));
				this->addChild(pRightChatContainer, Z_RIGHTCONTAIN, TAG_RIGHTCONTAIN);
				pRightChatContainer->release();
			}

			if(pRightChatContainer)
				pRightChatContainer->showContent(_voice);
		}
		break;
	}
    //Doyang 20120708
    CC_SAFE_DELETE(_voice);
}

void NPCChat::dispose()
{
	// Doyang 20120712
	LeftChatContainer *pLeftChatContainer = (LeftChatContainer *) this->getChildByTag(TAG_LEFTCONTAIN);
	if(pLeftChatContainer)
	{
		pLeftChatContainer->dispose();
		this->removeChildByTag(TAG_LEFTCONTAIN, true);
	}
	RightChatContainer *pRightChatContainer = (RightChatContainer *) this->getChildByTag(TAG_RIGHTCONTAIN);
	if(pRightChatContainer)
	{
		pRightChatContainer->dispose();
		this->removeChildByTag(TAG_RIGHTCONTAIN, true);
	}
	WhisperContainer *pWhisperContainer = (WhisperContainer *) this->getChildByTag(TAG_WHISCONTAIN);
	if(pWhisperContainer)
	{
		pWhisperContainer->dispose();
		this->removeChildByTag(TAG_WHISCONTAIN, true);
	}
	/*if(_whisperContainer)
	{
		_whisperContainer->dispose();
		if(this->getChildByTag(TAG_WHISCONTAIN))
		{
			this->removeChild(_whisperContainer,true);
		}
		_whisperContainer = 0;
	}

	if(_leftChatContainer)
	{
		_leftChatContainer->dispose();
		if(this->getChildByTag(TAG_LEFTCONTAIN))
		{
			this->removeChild(_leftChatContainer,true);
		}
		_leftChatContainer = 0;
	}

	if(_rightChatContainer)
	{
		_rightChatContainer->dispose();
		if(this->getChildByTag(TAG_RIGHTCONTAIN))
		{
			this->removeChild(_rightChatContainer,true);
		}
		_rightChatContainer = 0;
	}*/
}