
#include "NameManager.h"
#include "utils/Timer.h"

Namemanager::Namemanager()
{

}

int Namemanager::getRandomPos(int size)
{
	if (!size)
	{
		return 0;
	}
	srand(Timer::millisecondNow());
	return (rand()%size);
}

std::string Namemanager::randomName(int sex)
{
	std::string name = "";
	int num2or3 = getRandomPos(1000);
	if (sex == 1)
	{
		if(num2or3 < 500)
		{
			name = _firstMale[110][getRandomPos(_firstMale[110].size())];
			name.append(_secondNoThirdMale[21][getRandomPos(_secondNoThirdMale[21].size())]);
		}
		else
		{
			name = _firstMale[110][getRandomPos(_firstMale[110].size())];
			name.append(_secondMale[210][getRandomPos(_secondMale[210].size())]);
			name.append(_thirdMale[310][getRandomPos(_thirdMale[310].size())]);
		}
	}
	else
	{
		if(num2or3 < 500)
		{
			name = _firstFemale[120][getRandomPos(_firstFemale[120].size())];
			name.append(_secondNoThirdFemale[22][getRandomPos(_secondNoThirdFemale[22].size())]);
		}
		else
		{
			name = _firstFemale[120][getRandomPos(_firstFemale[120].size())];
			name.append(_secondFemale[220][getRandomPos(_secondFemale[220].size())]);
			name.append(_thirdFemale[320][getRandomPos(_thirdFemale[320].size())]);
		}
	}
	return name;
}