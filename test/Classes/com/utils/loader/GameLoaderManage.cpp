#include "utils/loader/GameLoaderManage.h"
#include "utils/loader/LoadLevel.h"

GameLoaderManage::GameLoaderManage()
:MAX_LOADER(0),_bytesLoaded(0),_bytesTotal(0),
_curLoader(0),_firstLoading(false),_waitHigh(0)
{
}

void GameLoaderManage::load(LoaderItem &loaderItem)
{
	/*if(loaderItem._level == 0)
	{ 
		firstLoad(loaderItem);
	}
	else
	{
		commonLoad(loaderItem);
	}*/

	//SecurityLoader loader = SecurityLoader();
	//loader.load(loaderItem);
}

int GameLoaderManage::getProgress()
{
	return _bytesLoaded / _bytesTotal;
}



/**
* Priority loading
* @param loaderItem
*
*/

void GameLoaderManage::firstLoad(LoaderItem &loaderItem)
{
	_needLoad.push_back(loaderItem);
	
	if( !_firstLoading )
	{
		//SecurityLoader loader = SecurityLoader();
		_firstLoading = true;
		//loader.addEventListener(Event.COMPLETE, completeHandler);
		//loader.addEventListener(ProgressEvent.PROGRESS, progressHandler);
		//loader.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler);
		//loader.load(loaderItem);
	}
	else
	{
		_loadFirstQueue.push_back(loaderItem);
	}
}


void GameLoaderManage::commonLoad(LoaderItem &loaderItem)
{
	_needLoad.push_back(loaderItem);
	if(_curLoader < MAX_LOADER)
	{ //Directly loading
		//SecurityLoader loader = SecurityLoader();
		//loader.addEventListener(Event.COMPLETE, completeHandler);
		//loader.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler);
		//loader.load(loaderItem);
		_curLoader++;
	}
	else
	{
		if(loaderItem._level == LoadLevel::HIGH)
		{
			//_loadQueue.unshift(loaderItem.url);
			//Temporarily to insert, not inserted into a beginning
			//_loadQueue.insert(0, loaderItem);
			_waitHigh++;
		}
		else if(loaderItem._level == LoadLevel::LOW)
		{
			_loadQueue.push_back(loaderItem);
		}
		else if(loaderItem._level == LoadLevel::MIDDILE)
		{
			//_loadQueue.splice(waitHigh, 0, loaderItem.url);
			//_loadQueue.insert(_waitHigh, loaderItem);
		}
  	}
}