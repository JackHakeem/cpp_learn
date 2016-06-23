#ifndef _COLORURIL_H_
#define _COLORURIL_H_

#include "BaseType.h"



class ColorUtil
{
public:


	static cocos2d::ccColor3B getGoodColor(int quality)
	{
		cocos2d::ccColor3B m_array[8] = {{153,153,153},{255,255,255},{0,255,0},{0,153,255},{204,0,204},{255,102,0},{255,0,0},{255,238,0}};
		if (quality >= 8 || quality <0)
			return cocos2d::ccc3(153,153,153);
		return m_array[quality];

	}

	static cocos2d::ccColor3B getMerchColor(int merColor)
	{
		ccColor3B Ccc3;
		switch (merColor)
		{
		case 0:
			Ccc3 = ccc3(255,211,6);
			break;
		case 1:
			Ccc3 = ccc3(240,240,240);
			break;
		case 2:
			Ccc3 = ccc3(0,236,0);
			break;
		case 3:
			Ccc3 = ccc3(0,114,227);
			break;
		case 4:
			Ccc3 = ccc3(255,0,255);
			break;
		case 5:
			Ccc3 = ccc3(247,80,0);
			break;
		case 6:
			Ccc3 = ccc3(255,45,45);
			break;
		default:
			Ccc3 = ccc3(240,240,240);
			break;
		}
		return Ccc3;
	}
};

#endif