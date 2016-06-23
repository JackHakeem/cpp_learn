#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


class CDownloadDelegateBase
{
public:
    virtual void Fire(const char* pURL, bool bOK) = 0;
};

template<typename O, typename T>
class CDownloadDelegate: public CDownloadDelegateBase
{
    typedef void (T::*Fun)(const char*, bool);
public:
    CDownloadDelegate(O* pObj = NULL, Fun pFun = NULL)
        :m_pFun(pFun), m_pObj(pObj)
    {
    }
    
    virtual void Fire(const char* pURL, bool bOK)
    {
        if(m_pFun != NULL
            && m_pObj != NULL)
        {
            (m_pObj->*m_pFun)(pURL, bOK);
        }
    }

private:
    Fun m_pFun;
    O* m_pObj;
};

template<typename O, typename T>
CDownloadDelegate<O,T>* MakeDelegate(O* pObject, void (T::*pFun)(const char* pURL, bool))
{
    return new CDownloadDelegate<O, T>(pObject, pFun);
}

class CDownloadEvent
{
public:
    ~CDownloadEvent()
    {
        vector<CDownloadDelegateBase*>::iterator itr = m_arDelegates.begin();
        while (itr != m_arDelegates.end())
        {
            delete *itr;
            ++itr;
        }
        m_arDelegates.clear();
    }

    void operator += (CDownloadDelegateBase* p)
    {
        m_arDelegates.push_back(p);
    }

    void operator -= (CDownloadDelegateBase* p)
    {
        ITR itr = remove(m_arDelegates.begin(), m_arDelegates.end(), p);

        ITR itrTemp = itr;
        while (itrTemp != m_arDelegates.end())
        {
            delete *itr;
            ++itr;
        }
        m_arDelegates.erase(itr, m_arDelegates.end());
    }

    void operator()(const char* pURL, bool bOK)
    {
        ITR itrTemp = m_arDelegates.begin();
        while (itrTemp != m_arDelegates.end())
        {
            (*itrTemp)->Fire(pURL, bOK);
            ++itrTemp;
        }
    }

private:
    vector<CDownloadDelegateBase*> m_arDelegates;
    typedef vector<CDownloadDelegateBase* >::iterator ITR;
};


class CMyDownloaderEx
{
public:
    void DownloadFile(const char* pURL)
    {
        cout << "downloading: " << pURL << "" << endl;
        downloadEvent(pURL, true);
    }

    CDownloadEvent downloadEvent;
};

class CMyFileEx
{
public:
    void download()
    {
        CMyDownloaderEx downloader;
        downloader.downloadEvent += MakeDelegate(this, &CMyFileEx::OnDownloadFinished);
        downloader.DownloadFile("www.baidu.com");
    }

    virtual void OnDownloadFinished(const char* pURL, bool bOK)
    {
        cout << "OnDownloadFinished, URL:" << pURL << "    status:" << bOK << endl;
    }
};




int main(int argc, char** argv)
{
    DownloadFile("www.baidu.com", OnDownloadFinished);
    CMyFile f1;
    f1.download();

    CMyFileEx ff;
    ff.download();


    return 0;

}
