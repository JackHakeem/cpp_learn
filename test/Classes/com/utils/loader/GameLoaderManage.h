#ifndef HLQS_GameLoaderManage_h
#define HLQS_GameLoaderManage_h

#include "cocos2d.h"
#include "utils/Singleton.h"
#include "utils/loader/LoaderItem.h"

using namespace cocos2d;

class GameLoaderManage: public Singleton<GameLoaderManage>
{
public:
	std::string PROGRESS;
	/**
	* Loading channel cap
	*/
	int MAX_LOADER;

	int _bytesLoaded;
	int _bytesTotal;
	/**
	* The current number of loading
	*/
	int _curLoader;

	/**
	* Whether in priority loading opening
	*/		
	bool _firstLoading;
		
	int _waitHigh;
	/**
	* Priority queue loading
	*/
	std::vector<LoaderItem> _loadFirstQueue;

	/**
	* Loading queue
	*/
	 std::vector<LoaderItem> _loadQueue;

	/**
	* Loading queue
	*/
	std::vector<LoaderItem> _needLoad;

public:
	GameLoaderManage();
	void load(LoaderItem &loaderItem);
	int getProgress();
	void firstLoad(LoaderItem &loaderItem);
	void commonLoad(LoaderItem &loaderItem);
};

#endif