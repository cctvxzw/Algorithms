#include <stdio.h>  
#include <stdlib.h>  
#include "time.h"

//打印数组
void print_arry(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//1.插入排序
void insertion_sort(int a[], int n) {
	int i, j, key;
	for (j = 1; j < n; j++) {
		key = a[j];
		i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = key;
	}
}

//2.归并排序
/*归并排序的归并函数*/
void Merge(int SR[], int TR[], int i, int middle, int rightend) {//实际上这里的i也就是要排序合并的数组段的左起始点
	int j, k, l;
	for (k = i, j = middle + 1; i <= middle && j <= rightend; k++) {
		if (SR[i] < SR[j])/*将SR中的元素按小到大的顺序存入TR,只需比较中点两侧对应下标元素大小*/
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= middle) {/*若中点左边元素剩余,将剩余元素并入TR(注意这里并入只要按照顺序即可,因为SR已经排好序了)*/
		for (l = 0; l <= middle - i; l++)
			TR[k + l] = SR[i + l];
	}
	if (j <= rightend) {/*若中点右边元素剩余,将剩余元素并入TR*/
		for (l = 0; l <= rightend - j; l++)
			TR[k + l] = SR[j + l];
	}
}
/*归并排序递归函数*/
void MSort(int SR[], int TR1[], int s, int t) {
	int middle;
	int TR2[100 + 1];
	if (s == t)
		TR1[s] = SR[s];
	else {
		middle = (s + t) / 2;/*将SR分成以middle为界的两部分*/
		MSort(SR, TR2, s, middle);/*递归将SR[s,middle]归并为有序的数组TR2*/
		MSort(SR, TR2, middle + 1, t);/*递归将SR[middle+1,t]归并为有序的数组TR2*/
		Merge(TR2, TR1, s, middle, t);/*将上面的两部分分别有序的TR2归并为总体有序的TR1*/
	}
}

//3.快速排序
void quick_sort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)//从右到左找到第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] <= x)//从左往右找到第一个大于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];

		}

		s[i] = x;//i = j的时候，将x填入中间位置  
		quick_sort(s, l, i - 1);//递归调用 
		quick_sort(s, i + 1, r);
	}
}

//4.计数排序
void count_sort(int *arr, int *sorted_arr, int n)
{
	int *count_arr = (int *)malloc(sizeof(int) * 100);
	int i;
	//初始化计数数组   
	for (i = 0; i < 100; i++)
		count_arr[i] = 0;
	//统计i的次数   
	for (i = 0; i < n; i++)
		count_arr[arr[i]]++;
	//对所有的计数累加   
	for (i = 1; i < 100; i++)
		count_arr[i] += count_arr[i - 1];
	//逆向遍历源数组（保证稳定性），根据计数数组中对应的值填充到先的数组中   
	for (i = n; i > 0; i--)
	{
		sorted_arr[count_arr[arr[i - 1]] - 1] = arr[i - 1];
		count_arr[arr[i - 1]]--;
	}
	free(count_arr);
}

//5.桶排序  

typedef struct node {
	int key;
	struct node *next;
}KeyNode;

void bucket_sort(int keys[], int size, int bucket_size) {
	int i, j;
	KeyNode **bucket_table = (KeyNode **)malloc(bucket_size * sizeof(KeyNode*));
	for (i = 0; i < bucket_size; i++) {
		bucket_table[i] = (KeyNode*)malloc(sizeof(KeyNode));
		bucket_table[i]->key = 0;
		bucket_table[i]->next = NULL;
	}
	for (j = 0; j < size; j++) {
		KeyNode *node = (KeyNode *)malloc(sizeof(KeyNode));
		node->key = keys[j];
		node->next = NULL;
		int index = keys[j] / 10;
		KeyNode *p = bucket_table[index];
		if (p->key == 0) {
			bucket_table[index]->next = node;
			(bucket_table[index]->key)++;
		}
		else {
			while (p->next != NULL && p->next->key <= node->key)
				p = p->next;
			node->next = p->next;
			p->next = node;
			(bucket_table[index]->key)++;
		}
	}
	//print result
	KeyNode * k = NULL;
	for (i = 0; i < bucket_size; i++)
		for (k = bucket_table[i]->next; k != NULL; k = k->next)
			printf("%d ", k->key);
	printf("\n");
}

int main()
{
	clock_t start, finish;
	double totaltime;
	start = clock();
	int n, i;
	//生成数组
	int *arr, *sorted_arr;
	printf("输入数组大小n:");
	scanf_s("%d", &n);

	arr = (int *)malloc(sizeof(int) * n);
	sorted_arr = (int *)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
	}

	printf("排序前的数组：");
	print_arry(arr, n);

	//1.插入排序
	insertion_sort(arr, n);
	//2.归并排序
	//MSort(arr, sorted_arr, 0, n-1);
	//3.快速排序
	//quick_sort(arr, 0, n - 1);
	//4.计数排序
	//count_sort(arr, sorted_arr, n);
	//5.桶排序
	//bucket_sort(arr, n, n);
	printf("排序后的数组：");
	print_arry(arr, n);

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("\n程序运行的时间为: %.5f 秒", totaltime);
	system("pause");
	return 0;
}