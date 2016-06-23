#include "SystemManage.h"
SystemManage::SystemManage()
{
	_soundOn = true;
	_showPlayers = true;
	//SoundManager::Instance()->toggleBgSound(_soundOn);
}

void SystemManage::soundOn(bool value)
{
	_soundOn = value;
}

void SystemManage::showPlayers(bool value)
{
	_showPlayers = value;
	dispatchEvent( SystemManage::SHOW_PLAYER_CHANGE, NULL);
}

bool SystemManage::soundOn()
{
	return _soundOn;
}

bool SystemManage::showPlayers()
{
	return _showPlayers;
}
