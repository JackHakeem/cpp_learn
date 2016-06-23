#pragma once
#include "../Singleton.h"

class SortUtil : public Singleton<SortUtil>
{
public:
	SortUtil();
	virtual ~SortUtil();

	void reSort(int Arr[] , int len , const int ConstSortArr[]);
	int getIndex(const int ConstSortArr[] , int var);

protected:
private:
};