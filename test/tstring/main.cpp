#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

typedef struct __GameMsgIndex
{
    uint32_t nUserID;
    uint8_t nMsgType;
    uint8_t nFrom;
    uint32_t nTimestamp;
    string strUserName;
    string strMsgKey;

    string Serialize()
    {
        string strDst;
        strDst.append((char*)&nUserID,sizeof(nUserID));
        strDst.append((char*)&nMsgType,sizeof(nMsgType));
        strDst.append((char*)&nFrom,sizeof(nFrom));
        strDst.append((char*)&nTimestamp,sizeof(nTimestamp));
        uint8_t nNameLen = strUserName.size();
        strDst.append((char*)&nNameLen,sizeof(nNameLen));
        strDst.append(strUserName);
        uint16_t nKeyLen = strMsgKey.size();
        strDst.append((char*)&nKeyLen,sizeof(nKeyLen));
        strDst.append(strMsgKey);
        return strDst;
    }
    void DeSerialize(string& strSrc)
    {
        const char* p = strSrc.data();
        nUserID = *((uint32_t*)p);
        p += sizeof(nUserID);
        nMsgType = *((uint8_t*)p);
        p += sizeof(nMsgType);
        nFrom = *((uint8_t*)p);
        p += sizeof(nFrom);
        nTimestamp = *((uint32_t*)p);
        p += sizeof(nTimestamp);
        uint8_t nNameLen = *((uint8_t*)p);
        p += sizeof(nNameLen);
        strUserName.insert(0,p,nNameLen);
        p += nNameLen;
        uint16_t nKeyLen = *((uint16_t*)p);
        p += sizeof(nKeyLen);
        strMsgKey.insert(0,p,nKeyLen);
        return ;
    }

    void Print()
    {
        //ACE_DEBUG((LM_ERROR, ACE_TEXT("id:%d,type:%d,from:%d,time:%d,name:%s,keysize:%d\n"),nUserID,nMsgType, nFrom, nTimestamp, strUserName,strMsgKey.size()));
        printf("id:%u,type:%u,from:%u,time:%u,name:%s,keysize:%u,key:%s,intkey:%x\n",nUserID,nMsgType, nFrom, nTimestamp, strUserName.c_str(),(unsigned int)strMsgKey.size(), strMsgKey.c_str(), strMsgKey.c_str());
        return ;
    }

    static string Serialize(std::vector<struct __GameMsgIndex>& vctIndex)
    {
        string strDst;
        for(std::vector<struct __GameMsgIndex>::iterator vit=vctIndex.begin(); vit!=vctIndex.end(); vit++)
        {
            string strTmp = vit->Serialize();
            uint16_t nLen = strTmp.size();
            //ACE_DEBUG((LM_ERROR,ACE_TEXT("index len:%d, %s,%d\n"),nLen,__FILE__,__LINE__));
            strDst.append((char*)&nLen, sizeof(nLen));
            strDst.append(strTmp);
        }
        return strDst;
    }
    static void DeSerialize(std::vector<struct __GameMsgIndex>& vctIndex,string& strSrc)
    {
        const char* p = strSrc.data();
        while(p < (strSrc.data()+strSrc.size()))
        {
            uint16_t nLen = *((uint16_t*)p);
            //ACE_DEBUG((LM_ERROR,ACE_TEXT("index len:%d, %s,%d\n"),nLen,__FILE__,__LINE__));
            string strTmp;
            p += sizeof(nLen);
            strTmp.insert(0,p,nLen);
            p += nLen;
            struct __GameMsgIndex stIndex;
            stIndex.DeSerialize(strTmp);
            vctIndex.push_back(stIndex);
        }
        return;
    }
} GameMsgIndex;

typedef std::vector<GameMsgIndex> GameMsgIndexVector;

class CGameMsg
{
public:
    enum MSG_SEG_STATE
    {
        SEG_STATE_BEGIN=0,
        SEG_STATE_TRANS=1,
        SEG_STATE_END=2,
    };
    enum MSG_FROM_TYPE
    {
        MSG_FROM_FRIEND=1,
        MSG_FROM_ROOM=2,
        MSG_FROM_SYSTEM=3,
    };
    enum MSG_TYPE
    {
        MSG_TYPE_VOICE=0,
        MSG_TYPE_TEXT=1,
        MSG_TYPE_PIC=2,
    };
    enum MSG_BLOCK_SETTING
    {
        MSG_BLOCK_SETTING_ROOM		=0x01,
        MSG_BLOCK_SETTING_FRIEND	=0x02,
    };

public:
    CGameMsg(uint16_t nGameID, uint32_t nUserID)
    {
        m_nGameID = nGameID;
        m_nUserID = nUserID;
        m_nSequence=1;
        m_nLastModifiedTime=time(NULL);
        m_nState=SEG_STATE_BEGIN;
        m_strContent="";
        int nTimestamp = time(NULL);
        uint8_t byRand = rand()%255;
        m_strKey.append((char*)&nGameID,sizeof(nGameID));
        m_strKey.append((char*)&nUserID,sizeof(nUserID));
        m_strKey.append((char*)&nTimestamp,sizeof(nTimestamp));
        m_strKey.append((char*)&byRand,sizeof(byRand));

        m_stIndex.nTimestamp = nTimestamp;
        m_stIndex.strMsgKey = m_strKey;

    };
    CGameMsg() {};
    ~CGameMsg() {};
public:
    uint16_t m_nGameID;
    uint32_t m_nUserID;
    string m_strKey;
    GameMsgIndex m_stIndex;
    std::vector<uint32_t> m_vOnLineUserID;
    std::vector<uint32_t> m_vOffLineUserID;
    std::map<uint32_t,int32_t> m_mOnLineUserProxy;

    uint32_t m_nSequence;			/*分段传输记录用,最新序列号*/
    uint32_t m_nLastModifiedTime;	/*分段传输记录用,最后一次修改时间*/
    uint8_t m_nState;
    string m_strContent;

    void SetIndex(GameMsgIndex& stIndex)
    {
        m_stIndex.nFrom = stIndex.nFrom;
        m_stIndex.nUserID = stIndex.nUserID;
        m_stIndex.strUserName = stIndex.strUserName;
        m_stIndex.strMsgKey = stIndex.strMsgKey;
        m_stIndex.nTimestamp = stIndex.nTimestamp;
    }
    void GetIndex(GameMsgIndex& stIndex)
    {
        stIndex.nFrom = m_stIndex.nFrom;
        stIndex.nUserID = m_stIndex.nUserID;
        stIndex.strUserName = m_stIndex.strUserName;
        stIndex.strMsgKey = m_stIndex.strMsgKey;
        stIndex.nTimestamp = m_stIndex.nTimestamp;
    }


    void SetOnLineUser(uint32_t nUserID,int32_t nProxyID=-1)
    {
        m_vOnLineUserID.push_back(nUserID);
        m_mOnLineUserProxy[nUserID] = nProxyID;
    }
    int32_t GetOnlineProxy(uint32_t nUserID)
    {
        std::map<uint32_t,int32_t>::iterator mit = m_mOnLineUserProxy.find(nUserID);
        return mit == m_mOnLineUserProxy.end() ? -1 : mit->second;
    }
    void SetOffLineUser(uint32_t nUserID)
    {
        m_vOffLineUserID.push_back(nUserID);
    }


    string GetKey()
    {
        return m_strKey;
    }
    void SetKey(string& strKey)
    {
        m_strKey = strKey;
        m_stIndex.strMsgKey = strKey;
    }
    void SetContent(string& strContent)
    {
        m_strContent = strContent;
    }

    string Serialize()
    {
        string strIndex = m_stIndex.Serialize();
        m_strContent.insert(0,strIndex);
        uint32_t nLen = strIndex.size();
        m_strContent.insert(0,(char*)&nLen,sizeof(nLen));
        return m_strContent;
    }

    void DeSerialize(string& strContent)
    {
        const char* p = strContent.data();
        uint32_t nLen = *((uint32_t*)p);
        p += sizeof(nLen);
        string strIndex;
        strIndex.insert(0,p,nLen);
        m_stIndex.DeSerialize(strIndex);
        p += nLen;
        m_strContent.assign(p,strContent.size()-sizeof(nLen)-nLen);
        return;
    }

    uint32_t GetSequence()
    {
        return m_nSequence;
    }
    uint32_t GetLastModifiedTime()
    {
        return m_nLastModifiedTime;
    }
    uint8_t GetState()
    {
        return m_nState;
    }
    void Begin()
    {
        m_nState = SEG_STATE_BEGIN;
        m_nSequence++;
    }
    int Segment(uint32_t nSeq,std::string& strContent)
    {
        if(m_nState != SEG_STATE_TRANS && m_nState != SEG_STATE_BEGIN)
        {
            printf("seg status error:%d\n",m_nState);
            return -1;
        }
        if(nSeq != m_nSequence++)
        {
            printf("seg seq error:%d,%d\n",nSeq, m_nSequence-1);
            return -2;
        }
        m_strContent += strContent;
        //m_nSequence++;
        m_nLastModifiedTime = time(NULL);
        m_nState = SEG_STATE_TRANS;
        return 0;
    }
    void End()
    {
        m_nState = SEG_STATE_END;
    };
    void GetContent(string& strContent)
    {
        strContent = m_nState == SEG_STATE_END ? m_strContent : "";
    };
};

#if 1
int main()
{
    GameMsgIndex stIndex;
    stIndex.nUserID = 21598725;
    stIndex.nFrom = 9;
    stIndex.nMsgType = 8;
    stIndex.nTimestamp = time(NULL);
    stIndex.strUserName = "lander";
    int nKey = 21233;
    printf("keyaddr:%p\n", &nKey);
    
    string s;
    s.assign((char*)&nKey,sizeof(nKey));
    stIndex.strMsgKey = s;
    stIndex.Print();

    string sDst = stIndex.Serialize();
    GameMsgIndex stNewIndex;
    stNewIndex.DeSerialize(sDst);
    stNewIndex.Print();

    std::vector<GameMsgIndex> vctIndex;
    vctIndex.push_back(stIndex);
    stIndex.strUserName = "rocker lala";
    vctIndex.push_back(stIndex);

    string vctDst =  GameMsgIndex::Serialize(vctIndex);

    std::vector<GameMsgIndex> vctNewIndex;
    GameMsgIndex::DeSerialize(vctNewIndex,vctDst);
    for(std::vector<GameMsgIndex>::iterator vit=vctNewIndex.begin(); vit!= vctNewIndex.end(); vit++)
    {
        vit->Print();
    }

    return 0;
}
#endif


