#include<stdio.h>

void Print_Factorial(int N)
{
	int sum = 1;
	int i;
	if (N >= 0 && N <= 12)
	{
		sum = 1;
		for (i = N; i>1; i--)
		{
			sum = sum * i;
		}
		printf("%d\n", sum);
	}
	else if (N>12 && N <= 1000)
	{
		int a[3000] = {0};
		a[2999] = 1;
		int k;		//ָ����ƨ�ɿ�ʼ��λ��λ���ƶ�
		int mid;
		int num = 1; //��־λ������һλ��ʼ
		int temp = 0; //��־ÿ��λ�����ǰ��Ľ�λ
		for (i = 2; i <= N; i++)
		{
			k = 2999;
			//�����λ��ʼÿ��λ�ú�i��˲��ж��Ƿ��λ
			for (int t = num; t > 0; t--)
			{
				mid = (a[k] * i + temp) % 10;
				temp = (int)(a[k] * i + temp) / 10;
				a[k] = mid;
				k--;
				//ֻ�е������λ��˲ſ���û�н�λ
				if (t == 1)
				{
					//ѭ��֪����λ��Ϊ0
					while (temp != 0)
					{
						mid = (a[k] * i + temp) % 10;
						temp = (int)(a[k] * i + temp) / 10;
						a[k] = mid;
						k--;
					}
				}
				//����λ��
				num = 2999 - k;
			}
		}
		for (i = 0; i<num; i++)
		{
			printf("%d", a[3000 - num + i]);
		}
	}
	else {
		printf("Invalid input");
	}
}

int main()
{
	while (1)
	{
		int N;
		/*long sum = 1;*/
		printf("�����룺");
		scanf_s("%d", &N);
		Print_Factorial(N);
		/*int a[3000] = {};
		a[2999] = 1;
		int k;
		int mid;
		int i;
		int num = 1; //��־λ������һλ��ʼ
		int temp = 0; //��־ÿ��λ�����ǰ��Ľ�λ
		for (i = 2; i <= N; i++)
		{
			k = 2999;
			//�����λ��ʼÿ��λ�ú�i��˲��ж��Ƿ��λ
			for (int t = num; t > 0; t--)
			{
				mid = (a[k] * i + temp) % 10;
				temp = (int)(a[k] * i + temp) / 10;
				a[k] = mid;
				k--;
				//ֻ�е������λ��˲ſ���û�н�λ
				if (t == 1)
				{
					while (temp != 0)
					{
						mid = (a[k] * i + temp) % 10;
						temp = (int)(a[k] * i + temp) / 10;
						a[k] = mid;
						k--;
					}
				}
				//����λ��
				num = 2999 - k;
			}
		}
		for (i = 0; i<num; i++)
		{
			printf("%d", a[3000 - num + i]);
		}*/
	}
}