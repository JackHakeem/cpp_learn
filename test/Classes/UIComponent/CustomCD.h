#ifndef _CustomCD_H__
#define _CustomCD_H__

#include "cocos2d.h"
#include "BaseType.h"
#include "utils/Timer.h"
using namespace cocos2d;

class SCMD19F;

class CustomCD : public CCLayer
{
public:
	CustomCD( int type );
	virtual ~CustomCD();
	bool init();
	void reqMoney( CCObject* pSender );
	void layout( ccTime dt = 1.0f );
	void clearCD( SCMD19F* cmd );
	void okFunction( CCObject* pObject );
	void cancelFunction( CCObject* pObject );
	void cdChangedHandler( CCNode* n, void* data );
	string formatData( Number serTimer );
	string formatTime( string s );
	void stopTips();
	void dispose();
	void setTips();
	int getType();
	void reinit();
	int getIsLock();
	void setPreLabString(std::string str);
	virtual void CDCallback();
public:

	CCMenu* _tf;
	CCPoint m_cpBtOffset;
private:
	int _type;		// type
	int m_needGolds;
	string _preLabel;
	Number _timer;
	int _lock;
	CCMenu* _btnClear;
	bool _hasStep;
};



#endif