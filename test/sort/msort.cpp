#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<unistd.h>
#include<string.h>
using namespace std;

#define maxSize 50

static int sc = 0;
void Init_Array(int ar[],int n)
{
	srand(23);
	for(int i=0;i<n;++i)
	{
		ar[i] = rand() % 100;
	}
}

void printSortData(int ar[], int count)
{
	for(int i=0; i<count; i++)
	{
		cout<<setw(4)<<ar[i];
	}
	cout<<endl;
}

void Swap(int& Lval, int& Rval)
{
	Lval ^= Rval;
	Rval ^= Lval;
	Lval ^= Rval;
}

void insert_sort(int ar[], int n)
{
	int i,j,c;
	for( i=0; i<n; i++)
	{
		for( j=i; j>0; j--)
		{
			if( ar[j-1] > ar[j] )
				Swap(ar[j-1],ar[j]);
			c++;
		}
	}
	printf("insert_sort count:%d\n",c);	
}

void insert_sort2(int ar[], int n)
{
	int i,j,c;
	for( i=0; i<n; i++)
	{
		for( j=i; j>0 && ar[j-1] > ar[j]; j--)
		{
			Swap(ar[j-1],ar[j]);
			c++;
		}
	}
	printf("insert_sort2 count:%d\n",c);	
}

void select_sort(int ar[], int n)
{
	int i,j,v,c;
	for( i=0; i<n; i++ )
	{
		for( v=i,j=i+1; j<n; j++ )
		{
			if( ar[v] > ar[j] )
				v = j;
			c++;
		}
		if( i!=v )
			Swap(ar[i],ar[v]);
	}
	printf("select_sort count:%d\n",c);	
}

void max_heap_adjust(int ar[],int i,int n)
{
	int child = 2*i+1;
	for( ; child < n; i=child, child=2*i+1)
	{
		sc++;
		if( child < n-1 && ar[child] < ar[child+1] )
			child++;
		
		if( ar[child] > ar[i] )
			Swap(ar[child],ar[i]);
		else
			break;
	}
}

void max_heap_sort(int ar[],int n)
{
	int tmp;

	for(int i=n/2-1; i>=0; --i)
		max_heap_adjust(ar,i,n);

	for(int i=n-1; i>=0; i--)
	{
		Swap(ar[0],ar[i]);
		max_heap_adjust(ar,0,i);
	}
}

void bubble_sort(int ar[], int n)
{
	int i,j,c;
	for( i=0; i<n; i++ )
	{
		for( j=n-1; j>i; j-- )
		{
			if( ar[j] < ar[j-1] )
				Swap(ar[j-1],ar[j]);
			c++;
		}
	}		
	printf("bubble_sort count:%d\n",c);	
}

void bubble_sort2(int ar[], int n)
{
	int i,j,tag,c;
	for( i=0; i<n; i=tag )
	{
		tag = n;
		for( j=n-1; j>i; j-- )
		{
			if( ar[j] < ar[j-1] ){
				Swap(ar[j-1],ar[j]);
				tag = j;
			}
			c++;
		}
	}		
	printf("bubble_sort2 count:%d\n",c);	
}

void bubble_sort3(int ar[], int n)
{
	int i,j,tag,c;
	for( i=0; i<n; i++ )
	{
		tag = n;
		for( j=n-1; j>i; j-- )
		{
			if( ar[j] < ar[j-1] ){
				Swap(ar[j-1],ar[j]);
				tag = j;
			}
			c++;
		}
		if( n == tag )
			break;//用处不大
	}	
	printf("bubble_sort3 count:%d\n",c);	
}


int mpartition(int ar[], int l, int r)
{
	int pivot = ar[l];
	while( l<r )
	{
		while( l<r && pivot<=ar[r] ){
			r--;sc++;
		}
		if( l<r )
			ar[l++] = ar[r];
		while( l<r && pivot>ar[l] ){
			l++;sc++;
		}
		if( l<r )
			ar[r--] = ar[l];
	}
	ar[l] = pivot;
	//cout << setw(4) << c << ":" << setw(4);
	//printSortData(ar,maxSize);
	return l;
}	

void quick_sort(int ar[], int l, int r)
{
	if( l<r )
	{
		int q = mpartition(ar, l, r);//挖坑
		quick_sort(ar,l,q-1);//分治
		quick_sort(ar,q+1,r);
	}
}

//merge sort
void mergearray(int ar[], int first, int mid, int last, int temp[])
{
	int i=first,j=mid+1;
	int m=mid,n=last;
	int k=0;
	while( i<=m && j<=n )
	{
		sc++;
		if( ar[i]<=ar[j] ){
			temp[k++]=ar[i++];
		}else{
			temp[k++]=ar[j++];
		}
	}
	while( i<=m ){
		temp[k++]=ar[i++];sc++;
	}
	while( j<=n ){
		temp[k++]=ar[j++];sc++;
	}

	for(i=first,k=0;i<=last;++i)
		ar[i]=temp[k++];
}

void merge_sort(int ar[], int first, int last, int temp[])
{
	if( first<last )
	{
		int mid = (first + last) / 2;
		merge_sort(ar,first,mid,temp);//分治
		merge_sort(ar,mid+1,last,temp);
		mergearray(ar,first,mid,last,temp);//归并
	}
}


int main()
{
	int ar[maxSize];
	int br[maxSize];
	Init_Array(ar,maxSize);
	memcpy(br,ar,maxSize*sizeof(int));
	printSortData(ar,maxSize);
	{
		insert_sort(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		insert_sort2(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		select_sort(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		bubble_sort(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		bubble_sort2(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		bubble_sort3(ar,maxSize);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
	}
	{
		quick_sort(ar,0,maxSize-1);
		printf("quick_sort count:%d\n",sc);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
		sc=0;
	}
	{
		int tmp[maxSize] = {0};
		merge_sort(ar,0,maxSize-1,tmp);
		printf("merge_sort count:%d\n",sc);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
		sc=0;
	}
	{
		max_heap_sort(ar,maxSize);
		printf("heap_sort count:%d\n",sc);
		printSortData(ar,maxSize);
		memcpy(ar,br,maxSize*sizeof(int));
		sc=0;
	}
	
	return 0;
}
