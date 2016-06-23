#ifndef _GMPROGRESSVO_H 
#define _GMPROGRESSVO_H 

/*
  * The monster of portfolio management, content from gameprogress. Read the XML
*/

class GMProgressVo
{
public:
	GMProgressVo()
	{
		id = 0;
		x = 0;
		y = 0;
		mapId = 0;
		mgId = 0;
	}
	~GMProgressVo(){}


public:
	int id;         //Progress Numbers
	int x;           //Monster in the position of the map
	int y; 
	int mapId;
	int mgId;           //Monster combination Numbers
	 
};

#endif