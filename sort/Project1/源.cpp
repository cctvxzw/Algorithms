#include <stdio.h>  
#include <stdlib.h>  
#include "time.h"

//��ӡ����
void print_arry(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//1.��������
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

//2.�鲢����
/*�鲢����Ĺ鲢����*/
void Merge(int SR[], int TR[], int i, int middle, int rightend) {//ʵ���������iҲ����Ҫ����ϲ�������ε�����ʼ��
	int j, k, l;
	for (k = i, j = middle + 1; i <= middle && j <= rightend; k++) {
		if (SR[i] < SR[j])/*��SR�е�Ԫ�ذ�С�����˳�����TR,ֻ��Ƚ��е������Ӧ�±�Ԫ�ش�С*/
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= middle) {/*���е����Ԫ��ʣ��,��ʣ��Ԫ�ز���TR(ע�����ﲢ��ֻҪ����˳�򼴿�,��ΪSR�Ѿ��ź�����)*/
		for (l = 0; l <= middle - i; l++)
			TR[k + l] = SR[i + l];
	}
	if (j <= rightend) {/*���е��ұ�Ԫ��ʣ��,��ʣ��Ԫ�ز���TR*/
		for (l = 0; l <= rightend - j; l++)
			TR[k + l] = SR[j + l];
	}
}
/*�鲢����ݹ麯��*/
void MSort(int SR[], int TR1[], int s, int t) {
	int middle;
	int TR2[100 + 1];
	if (s == t)
		TR1[s] = SR[s];
	else {
		middle = (s + t) / 2;/*��SR�ֳ���middleΪ���������*/
		MSort(SR, TR2, s, middle);/*�ݹ齫SR[s,middle]�鲢Ϊ���������TR2*/
		MSort(SR, TR2, middle + 1, t);/*�ݹ齫SR[middle+1,t]�鲢Ϊ���������TR2*/
		Merge(TR2, TR1, s, middle, t);/*������������ֱַ������TR2�鲢Ϊ���������TR1*/
	}
}

//3.��������
void quick_sort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)//���ҵ����ҵ���һ��С��x����  
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] <= x)//���������ҵ���һ������x����  
				i++;
			if (i < j)
				s[j--] = s[i];

		}

		s[i] = x;//i = j��ʱ�򣬽�x�����м�λ��  
		quick_sort(s, l, i - 1);//�ݹ���� 
		quick_sort(s, i + 1, r);
	}
}

//4.��������
void count_sort(int *arr, int *sorted_arr, int n)
{
	int *count_arr = (int *)malloc(sizeof(int) * 100);
	int i;
	//��ʼ����������   
	for (i = 0; i < 100; i++)
		count_arr[i] = 0;
	//ͳ��i�Ĵ���   
	for (i = 0; i < n; i++)
		count_arr[arr[i]]++;
	//�����еļ����ۼ�   
	for (i = 1; i < 100; i++)
		count_arr[i] += count_arr[i - 1];
	//�������Դ���飨��֤�ȶ��ԣ������ݼ��������ж�Ӧ��ֵ��䵽�ȵ�������   
	for (i = n; i > 0; i--)
	{
		sorted_arr[count_arr[arr[i - 1]] - 1] = arr[i - 1];
		count_arr[arr[i - 1]]--;
	}
	free(count_arr);
}

//5.Ͱ����  

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
	//��������
	int *arr, *sorted_arr;
	printf("���������Сn:");
	scanf_s("%d", &n);

	arr = (int *)malloc(sizeof(int) * n);
	sorted_arr = (int *)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
	}

	printf("����ǰ�����飺");
	print_arry(arr, n);

	//1.��������
	insertion_sort(arr, n);
	//2.�鲢����
	//MSort(arr, sorted_arr, 0, n-1);
	//3.��������
	//quick_sort(arr, 0, n - 1);
	//4.��������
	//count_sort(arr, sorted_arr, n);
	//5.Ͱ����
	//bucket_sort(arr, n, n);
	printf("���������飺");
	print_arry(arr, n);

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("\n�������е�ʱ��Ϊ: %.5f ��", totaltime);
	system("pause");
	return 0;
}