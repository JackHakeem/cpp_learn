#pragma once

/**
 * 公会触发器控制中心 
 */

#include "utils/flash/CCIEventDispatcher.h"

class GuildDispatcher
{
public:
	GuildDispatcher()
	{
	}

    /**
    * Protected reliably against detective with
    */
	void addEventListener(int flag, CCNode* tar, SEL_CallFuncND selector)
	{
		eventDispatcher.addEventListener(flag, tar, selector);
	}

    /**
    * Protected reliably against detective removed
    */
	void removeEventListener(int flag)
	{
		eventDispatcher.removeEventListener(flag);
	}

    /**
    * Distributed events
    */
	void dispatchEvent(int flag, void* data)
	{
		eventDispatcher.dispatchEvent(flag, data);
	}

	/**
    * Return whether have the protected reliably against detective
    */
	bool hasEventListener(int flag)
	{
		return eventDispatcher.hasEventListener(flag);
	}

	/**
    * This don't know why use
	public function willTrigger(type) : Boolean 
    {
        return eventDispatcher.willTrigger( type ),
    }
    */
      	

public:


	CCIEventDispatcher eventDispatcher;

public:
	//singleton part
  	/**
   	* Return examples
   	*/ 
	static GuildDispatcher * getInstance()
	{
		if (0 == instance)
		{
			instance = new GuildDispatcher();
			static CGarbo Garbo;
		}

		return instance;
	}

	static void DestroyInstance()
	{
		if (instance) {		
			delete instance;

			instance = 0;
		}
	}

	static GuildDispatcher *		instance;

private:
	class CGarbo // jae for aoto release
	{  
	public:  
		~CGarbo()  
		{  
			GuildDispatcher::DestroyInstance();
		}
	};
};