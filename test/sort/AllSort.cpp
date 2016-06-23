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

void insert_sort(int ar[], int n)//��������
{
	int i,j,v;
	for(i=1; i<=n; i++)
	{
		//�����i��Ԫ��С�ڵ�j�������j������ƶ�
		for(v=ar[i],j=i-1; j>=0 && v<ar[j]; j--)
			ar[j+1] = ar[j];
		ar[j+1] = v;
	}
}

void selection_sort(int a[], int n)//ѡ������
{
    int i,j,pos;
    for(i=0; i<n; i++) 
	{
        for(pos=i, j=i+1; j<=n; j++)//Ѱ����С��ֵ
		{
            if(a[pos]>a[j])
                pos=j;
		}
        if(pos != i) 
            Swap(a[i], a[pos]);
    }
}

void bubble_sort(int a[], int n)//ð������
{
    int i, j, lastSwap;
    for(j=n-1; j>0; j=lastSwap)
	{
        lastSwap=0;//ÿһ��Ҫ��ʼ��Ϊ0����ֹĳһ��δ����������lastSwap������һ�ֵ�ֵ������ѭ��
        for (i=0; i<j; i++)
		{
            if (a[i] > a[i+1])
			{
                Swap(a[i],a[i+1]);
				lastSwap = i; //���һ�ν���λ�õ�����
            }
        }
    }
}

void BubbleSort(int ar[] ,int n)//�Ż�
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

int mpartition(int a[], int l, int r) //��������
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
//�鲢����
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
        merge_sort(a, first, mid, temp);		//�������
        merge_sort(a, mid + 1, last, temp);		//�ұ�����
        mergearray(a, first, mid, last, temp);	//�ٽ������������кϲ�
    }
} 

//ϣ������1
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
//�����shell���ȡgap=n/2,,gap=gap/2,ֱ��gap=1�������ڵ����һ����������λ�õ�Ԫ��
//�Ż���ż��λ�õ�Ԫ�رȽϣ�����ʹ��������е�Ч�ʺܵͣ�������Knuth���ȡgap=gap/3+1

//ϣ������2
void shell_sort_1(int a[], int n)
{
    int d, i, j, temp;			//dΪ����
    for(d=n/2; d>0; d=d/2)		//�����ݼ���1ʹ�������
    {
        for(i=d; i<=n; i++)		//���������һ��
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

//������
void heapAdjust(int a[], int start, int nLength)
{
    int i = start;
	int j = 2*i+1;		// �ӽ���λ��=2*�������λ�ã�+ 1
    int nTemp = a[i];	//�ݴ��������ڵ�

	while(j <= nLength)
	{
		if(j < nLength && a[j] < a[j+1])
			j++;
		if(nTemp >= a[j])	//temp�����������������
			break;
		else
		{
			a[i] = a[j];
			i=j;			//i������Ůλ��
			j = 2*j + 1;
		}
	}
	a[i] = nTemp;
}

void heap_sort(int a[], int length)
{
	// �������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ�ش˴�"/"Ϊ����
	for(int i = (length-2)/2; i>=0; i--)
		heapAdjust(a, i, length-1);
	// �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
	for(int i = length; i>=0; i--)
	{
		// �ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
		// ��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
		Swap(a[0], a[i]);
		// ������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
		heapAdjust(a, 0, i-1);
	}
}

//����������
struct BST
{
    int number; //��������Ԫ�ص�ֵ
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

//Ͱ����
int getNumInPos(int num,int pos) //���ĳ�����ֵĵ�posλ��ֵ
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}

#define RADIX_10 10    //ʮ��Ͱ����ʾÿһλ��ʮ������
#define KEYNUM 5     //����λ��
void radix_sort(int* pDataArray, int iDataNum)
{
	int *radixArrays[RADIX_10];    //�ֱ�Ϊ0~9�����пռ�
	for(int i = 0; i < RADIX_10; i++)
	{
		radixArrays[i] = new int[iDataNum];
		radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
	}

	for(int pos = 1; pos <= KEYNUM; pos++)    //�Ӹ�λ��ʼ��31λ
	{
		for(int i = 0; i < iDataNum; i++)    //�������
		{
			int num = getNumInPos(pDataArray[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = pDataArray[i];
		}

		for(int i = 0, j =0; i < RADIX_10; i++) //д�ص�ԭ�����У���λradixArrays
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
//test_����
//	insert_sort(ar, maxSize);
//	printSortData(ar, maxSize);

//test_ѡ��
//	selection_sort(ar, maxSize);
//	printSortData(ar, maxSize);

//test_ð��
//	bubble_sort(ar,maxSize);
//	printSortData(ar,maxSize);

//test_����
//	quick_sort(ar, 0, maxSize);
//	printSortData(ar,maxSize);

//test_�鲢����
//	int temp[maxSize+1];
//	merge_sort(ar,0,maxSize,temp);
//	printSortData(ar,maxSize);

//test_ϣ������
// 	shell_sort(ar, 0, maxSize);
// 	printSortData(ar,maxSize);

//test_������
// 	heap_sort(ar, maxSize);
// 	printSortData(ar, maxSize);

//test_����������
// 	BST* root;
// 	createBST(&root, ar, maxSize);
// 	printResult(root);
// 	cout<<endl;

//test_Ͱ����
	int arr[] = {7, 8, 8, 9, 5, 16, 5, 3,56,21};
	radix_sort(arr, maxSize);
	printSortData_1(arr, maxSize);

}
