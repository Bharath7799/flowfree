#include <iostream>
using namespace std;
void swap(int *a,int *b)
{
	int *t=NULL;
	t=a;
	a=b;
	b=t;
}
int partition (int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}
void quickSort(int A[], int l, int h)
{
    if (l < h)
    {        
        int p = partition(A, l, h); /* Partitioning index */
        quickSort(A, l, p - 1);  
        quickSort(A, p + 1, h);
    }
}
int main()
{
	int arr[10]={1,2,3,7,8,9,4,5,6,10};
	int p=0, r=9;
	quickSort(arr,0,9);
	for (int i = 0; i < 10; ++i)
	{
		cout<<arr[i]<<" ";
	}
}