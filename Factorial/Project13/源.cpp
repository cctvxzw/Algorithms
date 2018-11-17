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
		int k;		//指定从屁股开始的位数位置移动
		int mid;
		int num = 1; //标志位数，从一位开始
		int temp = 0; //标志每个位相乘向前面的进位
		for (i = 2; i <= N; i++)
		{
			k = 2999;
			//从最低位开始每个位置和i相乘并判断是否进位
			for (int t = num; t > 0; t--)
			{
				mid = (a[k] * i + temp) % 10;
				temp = (int)(a[k] * i + temp) / 10;
				a[k] = mid;
				k--;
				//只有到了最高位相乘才看有没有进位
				if (t == 1)
				{
					//循环知道进位化为0
					while (temp != 0)
					{
						mid = (a[k] * i + temp) % 10;
						temp = (int)(a[k] * i + temp) / 10;
						a[k] = mid;
						k--;
					}
				}
				//返回位数
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
		printf("请输入：");
		scanf_s("%d", &N);
		Print_Factorial(N);
		/*int a[3000] = {};
		a[2999] = 1;
		int k;
		int mid;
		int i;
		int num = 1; //标志位数，从一位开始
		int temp = 0; //标志每个位相乘向前面的进位
		for (i = 2; i <= N; i++)
		{
			k = 2999;
			//从最低位开始每个位置和i相乘并判断是否进位
			for (int t = num; t > 0; t--)
			{
				mid = (a[k] * i + temp) % 10;
				temp = (int)(a[k] * i + temp) / 10;
				a[k] = mid;
				k--;
				//只有到了最高位相乘才看有没有进位
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
				//返回位数
				num = 2999 - k;
			}
		}
		for (i = 0; i<num; i++)
		{
			printf("%d", a[3000 - num + i]);
		}*/
	}
}