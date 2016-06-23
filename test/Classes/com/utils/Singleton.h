// Singleton.h: interface for the Singleton class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

//#include <vector>

//#include <assert.h>
//#include <windows.h>

//namespace util
//{
template <typename T>
class Singleton
{
public:
	~Singleton()
	{
	}

	static T * Instance()
	{
		if (0 == ms_pInstance)
		{
			ms_pInstance = new T;
			//m_instanceContainer.push_back( ms_pInstance );
			static CGarbo Garbo;
		}

		return ms_pInstance;
	}

	static void DestroyInstance()
	{
		if (ms_pInstance) {		
			delete ms_pInstance;
			ms_pInstance = 0;
		}
	}

private:
	//std::vector<T*>		m_instanceContainer;
	static T *		ms_pInstance;

	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (Singleton::ms_pInstance)
			{
				delete Singleton::ms_pInstance;
				Singleton::ms_pInstance = 0;
			}
		}  
	};
};

template< class T > T * Singleton<T>::ms_pInstance = 0;
//}

#endif // __SINGLETON_H__
