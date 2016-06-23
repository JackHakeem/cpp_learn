#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

#define maxSize 10

void Init_Array(int ar[],int n)
{
	srand(23);
	for(int i=1;i<=n;++i)
	{
		ar[i] = rand() % 100;
	}
}

void printSortData(int ar[], int count)
{
	for(int i=1; i<=count; i++)
	{
		cout<<setw(4)<<ar[i];
	}
	cout<<endl;
}
void printSortData_1(int ar[], int count)
{
	for(int i=0; i<count; i++)
	{
		cout<<setw(4)<<ar[i];
	}
	cout<<endl;
}

void Swap(int& Lval, int& Rval)
{
	int temp = Lval;
	Lval = Rval;
	Rval = temp;
}

void insert_sort(int ar[], int n)//插入排序
{
	int i,j,v;
	for(i=1; i<=n; i++)
	{
		//如果第i个元素小于第j个，则第j个向后移动
		for(v=ar[i],j=i-1; j>=0 && v<ar[j]; j--)
			ar[j+1] = ar[j];
		ar[j+1] = v;
	}
}

void selection_sort(int a[], int n)//选择排序
{
    int i,j,pos;
    for(i=0; i<n; i++) 
	{
        for(pos=i, j=i+1; j<=n; j++)//寻找最小的值
		{
            if(a[pos]>a[j])
                pos=j;
		}
        if(pos != i) 
            Swap(a[i], a[pos]);
    }
}

void bubble_sort(int a[], int n)//冒泡排序
{
    int i, j, lastSwap;
    for(j=n-1; j>0; j=lastSwap)
	{
        lastSwap=0;//每一轮要初始化为0，防止某一轮未发生交换，lastSwap保留上一轮的值进入死循环
        for (i=0; i<j; i++)
		{
            if (a[i] > a[i+1])
			{
                Swap(a[i],a[i+1]);
				lastSwap = i; //最后一次交换位置的坐标
            }
        }
    }
}

void BubbleSort(int ar[] ,int n)//优化
{
	bool tag;
	for(int i=1;i<n;++i)
	{
		tag = true;
		for(int j=1;j<=n-i;++j)
		{
			if(ar[j] > ar[j+1])
			{
				tag = false;
				Swap(ar[j],ar[j+1]);
			}
		}
		if(tag) break;
		tag=true;
	}
}

int mpartition(int a[], int l, int r) //快速排序
{
    int pivot = a[l];
    while (l<r)
	{
        while(l<r && pivot<=a[r])
			r--;
        if(l<r)
			a[l++]=a[r];
        while(l<r && pivot>a[l])
			l++;
        if(l<r)
			a[r--]=a[l];
    }
    a[l]=pivot;
    return l;
}
void quick_sort(int a[], int l, int r)
{
    if (l < r)
	{
        int q = mpartition(a, l, r);
        quick_sort(a, l, q-1);
        quick_sort(a, q+1, r);
    }
}
//归并排序
void mergearray(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1;
    int m = mid,   n = last;
    int k = 0;
    while (i <= m && j <= n)
    {  
		if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= n)
        temp[k++] = a[j++];
    for (i = 0; i < k; i++)
        a[first + i] = temp[i];
}
void merge_sort(int a[], int first, int last, int temp[])
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        merge_sort(a, first, mid, temp);		//左边有序
        merge_sort(a, mid + 1, last, temp);		//右边有序
        mergearray(a, first, mid, last, temp);	//再将二个有序数列合并
    }
} 

//希尔排序1
void shell_sort(int a[], int L, int R)
{
	int i, j, gap = R-L+1;
	int temp;
	do 
	{
		gap = gap/3 + 1;
		for(i = L+gap; i<=R; i++)
		{
			if(a[i] < a[i-gap])
			{
				temp = a[i];
				j = i-gap;
				do 
				{
					a[j+gap] = a[j];
					j = j-gap;
				} while (j >= L && temp < a[j]);
				a[j+gap] = temp;
			}
		}
	} while (gap > 1);
}
//最初，shell提出取gap=n/2,,gap=gap/2,直到gap=1，但由于到最后一步，在奇数位置的元素
//才会与偶数位置的元素比较，这样使用这个序列的效率很低，后来，Knuth提出取gap=gap/3+1

//希尔排序2
void shell_sort_1(int a[], int n)
{
    int d, i, j, temp;			//d为增量
    for(d=n/2; d>0; d=d/2)		//增量递减到1使完成排序
    {
        for(i=d; i<=n; i++)		//插入排序的一轮
        {
            temp = a[i];
            for(j=i-d; (j>=0)&&(a[j]>temp); j=j-d)
            {
                a[j+d] = a[j];
            }
			a[j+d] = temp;
        }
    }
}

//堆排序
void heapAdjust(int a[], int start, int nLength)
{
    int i = start;
	int j = 2*i+1;		// 子结点的位置=2*（父结点位置）+ 1
    int nTemp = a[i];	//暂存子树根节点

	while(j <= nLength)
	{
		if(j < nLength && a[j] < a[j+1])
			j++;
		if(nTemp >= a[j])	//temp的排序码大则不做调整
			break;
		else
		{
			a[i] = a[j];
			i=j;			//i降到子女位置
			j = 2*j + 1;
		}
	}
	a[i] = nTemp;
}

void heap_sort(int a[], int length)
{
	// 调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素此处"/"为整除
	for(int i = (length-2)/2; i>=0; i--)
		heapAdjust(a, i, length-1);
	// 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
	for(int i = length; i>=0; i--)
	{
		// 把第一个元素和当前的最后一个元素交换，
		// 保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
		Swap(a[0], a[i]);
		// 不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
		heapAdjust(a, 0, i-1);
	}
}

//二叉树排序
struct BST
{
    int number; //保存数组元素的值
    struct BST* left;
    struct BST* right;
};

void insertBST(BST** tree, int v)
{
    if (*tree == NULL)
	{
        *tree = new BST;
        (*tree)->left=(*tree)->right=NULL;
        (*tree)->number=v;
        return;
    }
    if (v < (*tree)->number)
        insertBST(&((*tree)->left), v);
    else
        insertBST(&((*tree)->right), v);
}

void printResult(BST* tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        printResult(tree->left);
    cout << tree->number << "  ";
    if (tree->right != NULL)
        printResult(tree->right);
}

void createBST(BST** tree, int a[], int n)
{
    *tree = NULL;
    for(int i=1; i<=n; i++)
        insertBST(tree, a[i]);
}

//桶排序
int getNumInPos(int num,int pos) //获得某个数字的第pos位的值
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}

#define RADIX_10 10    //十个桶，表示每一位的十个数字
#define KEYNUM 5     //整数位数
void radix_sort(int* pDataArray, int iDataNum)
{
	int *radixArrays[RADIX_10];    //分别为0~9的序列空间
	for(int i = 0; i < RADIX_10; i++)
	{
		radixArrays[i] = new int[iDataNum];
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
	}

	for(int pos = 1; pos <= KEYNUM; pos++)    //从个位开始到31位
	{
		for(int i = 0; i < iDataNum; i++)    //分配过程
		{
			int num = getNumInPos(pDataArray[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = pDataArray[i];
		}

		for(int i = 0, j =0; i < RADIX_10; i++) //写回到原数组中，复位radixArrays
		{
			for (int k = 1; k <= radixArrays[i][0]; k++)
				pDataArray[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;
		}
	}
}

void main()
{
	int ar[maxSize+1];
	Init_Array(ar, maxSize);
	printSortData(ar, maxSize);
//test_插入
//	insert_sort(ar, maxSize);
//	printSortData(ar, maxSize);

//test_选择
//	selection_sort(ar, maxSize);
//	printSortData(ar, maxSize);

//test_冒泡
//	bubble_sort(ar,maxSize);
//	printSortData(ar,maxSize);

//test_快排
//	quick_sort(ar, 0, maxSize);
//	printSortData(ar,maxSize);

//test_归并排序
//	int temp[maxSize+1];
//	merge_sort(ar,0,maxSize,temp);
//	printSortData(ar,maxSize);

//test_希尔排序
// 	shell_sort(ar, 0, maxSize);
// 	printSortData(ar,maxSize);

//test_堆排序
// 	heap_sort(ar, maxSize);
// 	printSortData(ar, maxSize);

//test_二叉树排序
// 	BST* root;
// 	createBST(&root, ar, maxSize);
// 	printResult(root);
// 	cout<<endl;

//test_桶排序
	int arr[] = {7, 8, 8, 9, 5, 16, 5, 3,56,21};
	radix_sort(arr, maxSize);
	printSortData_1(arr, maxSize);

}
