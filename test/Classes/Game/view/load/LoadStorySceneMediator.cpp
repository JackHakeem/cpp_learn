#include "LoadStorySceneMediator.h"

LoadStorySceneMediator::LoadStorySceneMediator()
{

}

LoadStorySceneMediator::~LoadStorySceneMediator()
{

}

void LoadStorySceneMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd) 
	{
	case SHOW_PROCESS:
		showLoadProgress();
		break;
	}
}

void LoadStorySceneMediator::showLoadProgress()
{
// 	var loadTransaction:ILoadTransaction = new StoryLoadTransaction();
// 	loadTransaction.execute();
}