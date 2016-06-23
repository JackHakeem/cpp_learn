#ifndef HLQS_Utils_H_
#define HLQS_Utils_H_
#include "cocos2d.h"
#include "utils/Singleton.h"

USING_NS_CC;

class Utils: public Singleton<Utils>
{
private:
	float _scaleW;
	float _scaleH;

	const static int UP_DIR = 8;
	const static int LEFT_DIR = 4;
	const static int RIGHT_DIR = 6;
	const static int DOWN_DIR = 2;

	int speed;

	CCPoint formationPos[18];
public:
	Utils();
	float scaleW();
	float scaleH();
	int getDir(float px, float py, float tx, float ty);
	float changeSpeedToPixs(float pixs, int fps = 60);
	int getDirByName(std::string name);
	static void applyButtonEnable( CCMenu* button, bool enable );
	std::vector<CCPoint> randPoints(CCPoint ccpocenterPoint, int ranger);
	std::string getSentence(int mapId, int gmId, bool isBoss = false);
	CCPoint getStationPoint(int pos);
	void generateFormationPos();
};

std::vector<std::string> split(const std::string &str, const char *delimeters);

#endif