#ifndef HLQS_EquipmentManager_H_
#define HLQS_EquipmentManager_H_
#include "utils/Singleton.h"
#include "model/figure/vo/EquipmentVo.h"
#include "socket/command/s17/SCMD172.h"

class EquipmentManager: public Singleton<EquipmentManager>
{
public:
	EquipmentManager();
	~EquipmentManager();
	void deleteEquipment(int figure_id);
	EquipmentVo* getEquipment(int figure_id);
	int getEquipmentNum(int id);
	GoodsInfo* getEquip(int id, int grid);
	void createEquipment(char* data);
	void createOtherEquipment(char* data);
	void updateEquipment(SCMD172* scmd172);
private:
	std::map<int/*role_id*/,  EquipmentVo> _playerEquipment;
};
#endif