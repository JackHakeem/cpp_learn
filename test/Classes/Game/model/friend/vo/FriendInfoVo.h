#pragma once

#include "BaseType.h"
#include "BlessInfo.h"

class FriendInfoVo
{
public:
	FriendInfoVo(){OF = 0;}

		/**��ɫԭ��ID*/
	uint32 avatarID;
		/**��ɫ����*/
	std::string name;
		/**��֮ˮ���ȼ�*/
	uint32 level;
		/**�Ƿ��ܽ���ף������*/
	uint32 blessDisable;
		/**��ɫ�Ƿ����ߣ�0���ߣ�1������*/
	uint32 OF;
	uint32 cloth;
	uint32 sex;
	int32 id;
	BlessInfoVo blessInfo;
};
