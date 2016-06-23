#include "BaseThread.h"

int BaseThread::run()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	int result = 0;
	if (_func)
	{
		result = pthread_create(&pid, &attr, (void *( *)(void *))_func ,(void *)_arg);
	}
	else
	{
		result = pthread_create(&pid, &attr,my_thread,(void *)_arg);
	}
	pthread_attr_destroy(&attr);

   if(result != 0)
   {   
        return -1;
    }
    return result;
}
 
void * BaseThread::my_thread(void *arg) // security thread function
{
	pthread_mutex_t attr;
	pthread_mutex_lock(&attr);
	// add code here
	//(*_func)();

	pthread_mutex_unlock(&attr);

	return 0;
}

void BaseThread::stop()
{
	int ret = pthread_join(pid , &_ret);
	
	pthread_exit((void *)&ret);
}

pthread_t BaseThread::getPID()
{
	return pid;
}

bool BaseThread::isRunning()
{
	int ret = pthread_kill(pid , 0);
	if (ret != ESRCH && ret != EINVAL)
	{
		return true;
	}
	return false;
}
