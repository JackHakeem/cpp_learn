#include "model/figure/vo/EquipmentVo.h"

EquipmentVo::~EquipmentVo()
{
	std::map<int, GoodsInfo>::iterator it;
	for ( it = m_equipments.begin(); it != m_equipments.end(); it++ )
	{
		//CC_SAFE_DELETE( it->second.explain );
	}
	m_equipments.clear();
}

int EquipmentVo::setIndex(int index, GoodsInfo goods)
{
	//Doyang 20120716
	/*std::map<int, GoodsInfo>::iterator it = m_equipments.find(index);
	if(it != m_equipments.end()) 
	{
		CC_SAFE_DELETE(it->second.explain);
		m_equipments.erase(it);
	}*/
// 		return -1;
// 	m_equipments.insert(make_pair(index, goods));
	

	m_equipments[index] = goods;
	return 0;
}

GoodsInfo* EquipmentVo::getIndex(int index)
{
	std::map<int, GoodsInfo>::iterator iter = m_equipments.find(index);
	if(iter == m_equipments.end())
		return NULL;
	return &(iter->second);
}

std::map<int, GoodsInfo>* EquipmentVo::getAll()
{
	return &m_equipments;
}