#include "SortUtil.h"

SortUtil::SortUtil()
{

}

SortUtil::~SortUtil()
{

}

void SortUtil::reSort(int Arr[], int len , const int ConstSortArr[])
{
	for (int i = 0 ; i < len ; i++)
	{
		for (int j = i+1 ; j < len ; j++)
		{
			if (!Arr[i] || !Arr[j])
			{
				continue;
			}
			int a1 = getIndex(ConstSortArr , Arr[j]);
			int a2 = getIndex(ConstSortArr , Arr[i]);
			if (a1 >= 0 && a2>=0 && a1 < a2)
			{
				int p = Arr[j];
				Arr[j] = Arr[i];
				Arr[i] = p;
			}
		}
	}
}

int SortUtil::getIndex(const int ConstSortArr[] , int var)
{
	int len = sizeof(ConstSortArr)/sizeof(int);
	for (int i = 0 ; i < len ; i++)
	{
		if (ConstSortArr[i] == var)
		{
			return i;
		}		
	}
	return -1;
}