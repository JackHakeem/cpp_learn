#pragma once

class WBPlayerInfoVo
{
public:
	WBPlayerInfoVo()
	{
		awardList.clear();
	}
	~WBPlayerInfoVo(){};

public:
	// ʵʱ����
	/** �ҵ��ۼ��˺�  */
	int damage;
	/** ����CD,ʱ���,����ʱ���ſ��ƶ� */
	int deathCD;
	/** �������  */
	int boostNum;
	/** �ҵ��ۼƽ���  */
	std::list<SCMD2C8::SCMD2C8Node> awardList;

protected:
private:
};