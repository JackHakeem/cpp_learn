#ifndef _Base_Thread_h_
#define _Base_Thread_h_

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma comment(lib , "pthreadVC2.lib")
#include "../pthread/pthread.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "pthread.h"
#include "errno.h"
#include <cstddef>
#endif

class BaseThread
{
public:
	BaseThread(){};
	BaseThread(void * func , void * arg) : _func(func) , _arg(arg),_ret(0)
	{
	}
	virtual int run(); 
	virtual void stop();

	pthread_t getPID();
	bool isRunning();
    
    
private:   
	pthread_t pid;
	void * _ret;
	void * _arg;   // argument needed for executed function if you wanted
	void * _func; // thread function to be executed, showed be a static member or global function.
	
private:   
	static void * my_thread(void * arg);
};

#endif