#ifndef _STRENGREISE_H_
#define _STRENGREISE_H_

class StrengRise
{
public:
	StrengRise():gradeLevel(1),equipPos(0),growUp(0),maggrowUp(0),smallType(0){}
	~StrengRise(){}

	int gradeLevel;
	int equipPos;
	int growUp;
	int phygrowUp;
	int maggrowUp;
	int smallType;
};

#endif