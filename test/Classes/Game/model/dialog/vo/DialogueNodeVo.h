#ifndef _DIALOGUE_NODE_VO_H_
#define _DIALOGUE_NODE_VO_H_
#include "model/scene/vo/FindVo.h"

class DialogueNodeVo
{
public:
	DialogueNodeVo()
    {
        //_pText = 0;
        _type = 0;
        _findVo = 0;
    }
	~DialogueNodeVo()
	{
		_otherInfos.clear();
	}
	
public:
	//char *_pText;
	std::string _text;
	int _type;
	list<int> _otherInfos;
	FindVo *_findVo;
};

#endif