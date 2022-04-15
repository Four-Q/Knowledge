//快速排序算法
//aha

//一.分而治之思想：
//1)找出简单的基线条件
//2)逐渐缩小问题规模，使其符合基线条件
//
//二.快速排序
//基准值-> 分区
//快速排序的独到之处在于：其速度取决于选择的基准值（均分时最快）
//---所以实现快速排序时，请随机地选择用作基准值的元素
//最糟情况（O(n^2)），平均情况（O(nlogn)）
//->层数（即调用栈的高度）为O(logn)，每层的时间为O(n)-->总共O(nlogn)

//三.时间常量c
//c是算法所需的固定时间量，称为常量
//合并排序无论什么情况，复杂度为O(nlogn)
//但快速排序比合并排序快，why?
//--->因为快速排序的常量比合并排序小，因此如果他们的时间复杂度均为O(nlogn),快速排序速度更快
//大O表示法中的常量有时候事关重大
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int* QuickSort(int* arr, int size);
void Needtime(clock_t Start, clock_t End);
int mycomp(const void* p1, const void* p2);
void Swap(int* p1, int* p2);
int* Partition(int* low, int* high);
void QuickSort_std(int* low, int* high);

int main(void)
{
    clock_t start = 0, end = 0;
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        int arr[] = {5,1,3,2,4,6,66,99,99,2,2,1};
        QuickSort(arr, sizeof(arr)/sizeof(int));
    }
    end = clock();
    Needtime(start, end);
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        int arr[] = {5,1,3,2,4,6,66,99,99,2,2,1};
        qsort(arr, sizeof(arr)/sizeof(int), sizeof(int),mycomp);
    }
    end = clock();
    Needtime(start, end);
    //标准快排
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        int arr[] = {5,1,3,2,4,6,66,99,99,2,2,1};
        QuickSort_std(arr, arr + (sizeof(arr)/sizeof(int)));
    }
    end = clock();
    Needtime(start, end);//与标准时间一样（嘿嘿）
    return 0;
}

int* QuickSort(int* arr, int size)
{
    if (size <= 1)
        return arr;
    else
    {
        int pivot = arr[0];
        int* Larr = (int*)malloc(sizeof(int)*size);
        int* Rarr = (int*)malloc(sizeof(int)*size);
        int Lsize = 0, Rsize = 0;
        for (int i = 1; i < size; i++)
        {
            if (arr[i] <= pivot)
            {
                Larr[Lsize++] = arr[i];
            }
            else
            {
                Rarr[Rsize++] = arr[i];
            }
        }
        QuickSort(Larr, Lsize);
        QuickSort(Rarr, Rsize);
        int i = 0;
        for (int L = 0; L < Lsize; L++)
            arr[i++] = Larr[L];
        arr[i++] = pivot;
        for (int R = 0; R < Rsize; R++)
            arr[i++] = Rarr[R];
    }
    return arr;
}
//时间计算函数
void Needtime(clock_t Start, clock_t End)
{
    double needtime = (double)(End - Start)/CLK_TCK;
    printf("%.6f\n", needtime);
}
//比较函数
int mycomp(const void* p1, const void* p2)
{
    const int* a1 = (const int*)p1;
    const int* a2 = (const int*)p2;
    if (*a1 < *a2)
        return -1;
    else if (*a1 == *a2)
        return 0;
    else
        return 1;
}
//为什么之前那个快速排序算法还要分配新的数组内存呢？
//-->看看官方的实现方法
//1.交换数组俩个元素的值函数
void Swap(int* p1, int* p2)
{
    int c = *p1;
    *p1 = *p2;
    *p2 = c;
}
//2.分区函数
int* Partition(int* low, int* high)
{
    int* pivot = low;
    int* i = low; int* j = high;
    while (i < j)
    {
        do
        {
            i++;
        }while(*i <= *pivot);
        do
        {
            j--;
        }while(*j > *pivot);
        if (i < j)
            Swap(i, j);
    }
    Swap(j, pivot);
    return j;
}
//3.快速排序函数
void QuickSort_std(int* low, int* high)
{
    if (low < high)
    {
        int* j = Partition(low, high);
        QuickSort_std(low, j);
        QuickSort_std(j+1, high);
    }
}