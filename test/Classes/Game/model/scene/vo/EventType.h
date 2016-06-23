#ifndef HLQS_EventType_H_
#define HLQS_EventType_H_

class EventType
{
public:
    enum 
    {
        NONE = 0,
        STORY,
        ANIMATION,
        PVE,
        PVP
    };
//	const static int NONE;
//	const static int STORY;
//	const static int ANIMATION;
//	const static int PVE;
//	const static int PVP;
//    

public:
	EventType();
};

//const int EventType::NONE = 0;
//const int EventType::STORY = 1;
//const int EventType::ANIMATION = 2;
//const int EventType::PVE = 3;
//const int EventType::PVP = 4;
#endif