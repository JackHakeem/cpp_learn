#include "Utils.h"
#include <math.h>
#include "model/scene/SentenceManager.h"
#include "util/TileUtil.h"
#include "ScaleUtil.h"

Utils::Utils()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	_scaleW = screenSize.width / 1024.0f;
	_scaleH = screenSize.height / 768.0f;
	speed = 300;
	generateFormationPos();
}

float Utils::scaleW()
{
	return _scaleW;
}
float Utils::scaleH()
{
	return _scaleH;
}

int Utils::getDir(float px, float py, float tx, float ty)
{
	int dir = 0;

	float angle = - atan2(ty - py,tx - px) * (180 / 3.14159);
	if(angle>-157.5 && angle<-112.5)
	{
		dir=1;
	}
	else if(angle>-112.5 && angle<-67.5)
	{
		dir=2;
	}
	else if(angle>-67.5 && angle<-22.5)
	{
		dir=3;
	}
	else if(angle>-22.5 && angle<22.5)
	{
		dir=6;
	}
	else if(angle>22.5 && angle<67.5)
	{
		dir=9;
	}
	else if(angle>67.5 && angle<112.5)
	{
		dir=8;
	}
	else if(angle>112.5 && angle<157.5)
	{
		dir=7;
	}
	else
	{
		dir=4;
	}
	return dir;
}



float Utils::changeSpeedToPixs(float pixs, int fps)
{
	return pixs / fps;
}


int Utils::getDirByName(std::string name)
{
	/*var array:Array = name.split("_");
	var dir:int;

	if(array.length>1){
	switch(array[0]){
	case "2":
	dir = DOWN_DIR;
	break;
	case "4":
	dir = LEFT_DIR;
	break;
	case "6":
	dir = RIGHT_DIR;
	break;
	case "8":
	dir = UP_DIR;
	break;
	}
	}
	return dir; */
	return 0;
}

void Utils::applyButtonEnable( CCMenu* button, bool enable )
{
	//if(button is SimpleButton || button is MovieClip){
	//	button.mouseEnabled = enable;
	//	if(enable){
	//		button.filters = [];
	//	}
	//	else{
	//		applyBlackAndWhiteFilter(button as DisplayObject);
	//	}
	//}
	button->setIsVisible( enable );
}


std::vector<CCPoint> Utils::randPoints(CCPoint centerPoint, int ranger)
{
	int c = rand() % 360;
	int rd = rand() % 2;	
	int c1 = rd == 0 ? ( c - 60 ) : (c + 60);
	float angle = (float)c * 3.14159 / 180.0f;

	float angle1 = (float)c1 * 3.14159 / 180.0f;
	CCPoint point = ccp(int(ranger * cos(angle)) + centerPoint.x, int(ranger * sin(angle)) + centerPoint.y);
	CCPoint point1 =  ccp(int(ranger * cos(angle1))+centerPoint.x, int(ranger * sin(angle1)) + centerPoint.y);
	std::vector<CCPoint> path;
	path.push_back(point);
	path.push_back(point1);
	path.push_back(centerPoint);
	return path;
}

std::string Utils::getSentence(int mapId, int gmId, bool isBoss)
{
	std::string content = SentenceManager::Instance()->getSentence(mapId, gmId);
	if(isBoss)
	{
		/*GMProgessVo* gmProgressVo = MonsterManager::Instance()->getGroupMonsterById(gmId);
		int monsterGroupId = (gmProgressVo == NULL) ? gmProgressVo->mgId :0;
		NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup(monsterGroupId);	
		if(npcVo && g_pGoodsManager)
		{
			GoodsBasic* goodsBasic = g_pGoodsManager->getBasicGood(npcVo->DropGoods);
			if(goodsBasic)
			{
				std::string color = ColorUtil.getGoodColor(goodsBasic.quality).toString(16);
				var name:String = "<font size='14' color='#" + color + "'><b>" + goodsBasic.goodName + "</b></font>";
				content = content.replace(/##/g, name);	
			}
		}*/
	}
	return content;
}

CCPoint Utils::getStationPoint(int pos)
{
	if(pos >= 0)
	{
		return formationPos[pos];
	}
    return ccp(100, 100);//kevinchange
}

void Utils::generateFormationPos()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center;
	float w = screenSize.width;
	float h = screenSize.height;
	center.x = w / 2;
	center.y = h / 2;
	float length = sqrt(screenSize.width*screenSize.width + screenSize.height * screenSize.height);
	float rateSin = ((float)screenSize.height)/length;
	float rateCos = ((float)screenSize.width)/length;

	int spx = 5;
	int spy = 6;
	formationPos[1].x = center.x + ((float)center.x) / spx;
	formationPos[1].y = center.y + ((float)center.y) / spy;
	formationPos[4].x = center.x + 2 * ((float)center.x) / spx;
	formationPos[4].y = center.y + 2 * ((float)center.y) / spy;
	formationPos[7].x = center.x + 3 * ((float)center.x) / spx;
	formationPos[7].y = center.y + 3 * ((float)center.y) / spy;

	formationPos[2].x = formationPos[1].x - rateSin * length / (spx * 2);
	formationPos[2].y = formationPos[1].y + rateCos * length / (spy * 2);
	formationPos[5].x = formationPos[2].x + ((float)center.x) / spx;
	formationPos[5].y = formationPos[2].y + ((float)center.y) / spy;
	formationPos[8].x = formationPos[5].x + ((float)center.x) / spx;
	formationPos[8].y = formationPos[5].y + ((float)center.y) / spy;

	formationPos[0].x = formationPos[1].x + rateSin * length / (spx * 2);
	formationPos[0].y = formationPos[1].y - rateCos * length / (spy * 2);
	formationPos[3].x = formationPos[0].x + ((float)center.x) / spx;
	formationPos[3].y = formationPos[0].y + ((float)center.y) / spy;
	formationPos[6].x = formationPos[3].x + ((float)center.x) / spx;
	formationPos[6].y = formationPos[3].y + ((float)center.y) / spy;

	formationPos[10].x = w - formationPos[1].x;
	formationPos[10].y = h - formationPos[1].y;
	formationPos[13].x = w - formationPos[4].x;
	formationPos[13].y = h - formationPos[4].y;
	formationPos[16].x = w - formationPos[7].x;
	formationPos[16].y = h - formationPos[7].y;

	formationPos[9].x = w - formationPos[2].x;
	formationPos[9].y = h - formationPos[2].y;
	formationPos[12].x = w - formationPos[5].x;
	formationPos[12].y = h - formationPos[5].y;
	formationPos[15].x = w - formationPos[8].x;
	formationPos[15].y = h - formationPos[8].y;

	formationPos[11].x = w - formationPos[0].x;
	formationPos[11].y = h - formationPos[0].y;
	formationPos[14].x = w - formationPos[3].x;
	formationPos[14].y = h - formationPos[3].y;
	formationPos[17].x = w - formationPos[6].x;
	formationPos[17].y = h - formationPos[6].y;

		
	
	float yoffset = POSX(0.0f);
	
	/*formationPos[0] = ccp(POSX(660),  POSX(640-423));
	formationPos[1] = ccp(POSX(586),  POSX(640-466));
	formationPos[2] = ccp(POSX(514),  POSX(640-509));
	formationPos[3] = ccp(POSX(753),  POSX(640-466));
	formationPos[4] = ccp(POSX(680),  POSX(640-509));
	formationPos[5] = ccp(POSX(607),  POSX(640-552));
	formationPos[6] = ccp(POSX(846),  POSX(640-509));
	formationPos[7] = ccp(POSX(773),  POSX(640-552));
	formationPos[8] = ccp(POSX(700),  POSX(640-595));

	formationPos[9]  = ccp(POSX(436), POSX(640-318));
	formationPos[10] = ccp(POSX(363), POSX(640-361));
	formationPos[11] = ccp(POSX(290), POSX(640-404));
	formationPos[12] = ccp(POSX(343), POSX(640-275));
	formationPos[13] = ccp(POSX(270), POSX(640-318));
	formationPos[14] = ccp(POSX(197), POSX(640-361));
	formationPos[15] = ccp(POSX(250), POSX(640-232));
	formationPos[16] = ccp(POSX(177), POSX(640-275));
	formationPos[17] = ccp(POSX(104), POSX(640-318));*/

	//Doyang
    formationPos[0] = POS(ccp(660, 640-423), ScaleUtil::CENTER);
    formationPos[1] = POS(ccp(586, 640-466), ScaleUtil::CENTER);
    formationPos[2] = POS(ccp(514, 640-509), ScaleUtil::CENTER);
    formationPos[3] = POS(ccp(753, 640-466), ScaleUtil::CENTER);
    formationPos[4] = POS(ccp(680, 640-509), ScaleUtil::CENTER);
    formationPos[5] = POS(ccp(607, 640-552), ScaleUtil::CENTER);
    formationPos[6] = POS(ccp(846, 640-509), ScaleUtil::CENTER);
    formationPos[7] = POS(ccp(773, 640-552), ScaleUtil::CENTER);
    formationPos[8] = POS(ccp(700, 640-595), ScaleUtil::CENTER);

    formationPos[9]  = POS(ccp(436, 640-318), ScaleUtil::CENTER);
    formationPos[10] = POS(ccp(363, 640-361), ScaleUtil::CENTER);
    formationPos[11] = POS(ccp(290, 640-404), ScaleUtil::CENTER);
    formationPos[12] = POS(ccp(343, 640-275), ScaleUtil::CENTER);
    formationPos[13] = POS(ccp(270, 640-318), ScaleUtil::CENTER);
    formationPos[14] = POS(ccp(197, 640-361), ScaleUtil::CENTER);
    formationPos[15] = POS(ccp(250, 640-232), ScaleUtil::CENTER);
    formationPos[16] = POS(ccp(177, 640-275), ScaleUtil::CENTER);
    formationPos[17] = POS(ccp(104, 640-318), ScaleUtil::CENTER);
	
	for (int i = 0; i < 18; i++)
	{
		formationPos[i] = ccpAdd(formationPos[i], ccp(0, yoffset));		
		//formationPos[i] = ccp(460, 300);
	}
}

std::vector<std::string> split(const std::string &str, const char *delimeters)
{
	std::vector<std::string> results;
	std::string::size_type pos = 0;
	while(pos != std::string::npos)
	{
		std::string::size_type next = str.find_first_of(delimeters, pos);
		if(next == std::string::npos)
		{
			std::string s = str.substr(pos);
			if(!s.empty())
				results.push_back(str.substr(pos));
			return results;
		}

		std::string s = str.substr(pos, next - pos);
		if(!s.empty())
			results.push_back(s);
		pos = next + 1;
	}

	return results;
}
