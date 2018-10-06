#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#define max 100
#define min 0

struct Point
{
	int x;
	int y;
}*point;


void goto_xy(int x, int y)//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

/*-----------------------------------*/
//         暴力求解两点最短          //
/*-----------------------------------*/
float Count_Distance1(struct Point *p, int n) {
	int t = 0;
	float Dmin;
	float *C;
	if (n == 1 || n == 0) {
		Dmin = 100;
		return Dmin;
	}
	else {
		//printf("\n%d", n);
		C = (float*)malloc(sizeof(float)*n*(n - 1) / 2);
		for (int i = 0; i < n; i++) {
			for (int k = i + 1; k < n; k++) {
				*(C + t) = (float)sqrt((float)pow(((float)(p + i)->x - (float)(p + k)->x), 2) + pow(((float)(p + i)->y - (float)(p + k)->y), 2));
				//printf("%f ", *(C + t));
				t++;
			}
		}
		//printf("%d \n",t);
		int id = 0;
		Dmin = *C;
		for (int i = 0; i < n*(n - 1) / 2; i++) {
			if (*(C + i) < Dmin) {
				Dmin = *(C + i);
				id = i;
			}
		}
		free(C);

		return Dmin;
	}

}



/*-----------------------------------*/
//           分治排序                //
/*-----------------------------------*/
Point* Merge(Point*X,Point*Y,int n,int flag){
	Point *z;
	z = (Point*)malloc(sizeof(Point)*n);
	for (int i = 0; i < n; i++)
	{
		(z + i)->x = 0;
	}
	int i, t, p;
	i = t = p = 0;
	int m = (int)n / 2;
	printf("\n");
	if (flag == 1) {
		for (i = 0; i < n; i++)
		{
			//printf("%d %d\n", (X+t)->x,(Y+p)->x);
			if (((X + t)->x >= (Y + p)->x&&p<(n-m))||t>=m)
			{
				*(z+i) = *(Y + p);
				p++;
			}
			else if (((X + t)->x < (Y + p)->x&&t<m)||p>=(n-m)) {
				*(z+i) = *(X + t);
				t++;
			}
		}
	}
	else if (flag == 0) {
		for (i = 0; i < n; i++)
		{
			if (((X + t)->y >= (Y + p)->y&&p<(n - m)) || t >= m)
			{
				*(z + i) = *(Y + p);
				p++;
			}
			else if (((X + t)->y < (Y + p)->y&&t<m) || p >= (n - m)) {
				*(z + i) = *(X + t);
				t++;
			}
		}
	}
	else
	{
		return NULL;
	}

	return z;
}

Point* Sort(struct Point *p,int n,int flag) {
	Point *y;
	y = (Point*)malloc(sizeof(Point) * n);
	if (n == 1) {
		*y = *p;
	}
	else {
		int m;
		m = (int)n / 2;
		y = Merge(Sort(p,m,flag),Sort((p+m),(n-m),flag),n,flag);
	}

	return y;
}




/*-----------------------------------*/
//         分治求解两点最短          //
/*-----------------------------------*/
float Count_Distance2(Point *p, int n) {
	float distance;
	if (n == 3||n == 2) {
		distance = Count_Distance1(p, n);
	}
	else {
		int m = (int)n / 2;
		float r1, r2,r3;
		Point *p1, *p2;
		p1 = (Point*)malloc(sizeof(Point)*m);
		p2 = (Point*)malloc(sizeof(Point)*(n - m));
		for (int i = 0; i<m; i++ )
		{
			*(p1 + i) = *(p + i);
		}
		for (int i = 0; i < (n-m); i++)
		{
			*(p2 + i) = *(p + m + i);
		}
		r1 = Count_Distance2(p1, m);
		r2 = Count_Distance2(p2, (n - m));
		if (r2 >= r1) {
			r3 = r1;
		}
		else
		{
			r3 = r2;
		}
		//printf("\n%.2f\n", r3);
		/*从中线分割开看*/
		float xmax = (p + m)->x + r3;
		float xmin = (p + m)->x - r3;
		float ymax = (p + m)->y + r3;
		float ymin = (p + m)->y - r3;
		Point *p3;
		int count = 0;
		for (int i = 0; i < n;i++) {
			if (((p + i)->x > xmin && (p + i)->x < xmax) || ((p + i)->y > ymin && (p + i)->y < ymax))
				count++;
		}
		p3 = (Point*)malloc(sizeof(Point)*count);
		for (int i = 0,t = 0; i < n; i++) {
			if (((p + i)->x > xmin && (p + i)->x < xmax) || ((p + i)->y > ymin && (p + i)->y < ymax)) {
				*(p3 + t) = *(p + i);
				t++;
			}
		}
		float r4 = Count_Distance1(p3, count);
		printf("\n%.2f\n", r4);
		if (r4 >= r3)
		{
			distance = r3;
		}
		else {
			distance = r4;
		}
		free(p1);
		free(p2);
		free(p3);
	}

	return distance;
}









void distance_main()
{
	struct Point p[10];


	//随机生成10个位置
	//srand(time(0));
	for (int i = 0; i < 10; i++) {
		p[i].x = rand() % (max - min) + min;
	}
	for (int i = 0; i < 10; i++) {
		p[i].y = rand() % (max - min) + min;
	}
	
	/*打印p的xy数值*/
	for (int i = 0; i < 10; i++) {
		//goto_xy(p[i].x, p[i].y);
		//printf("*");
		printf("(%d,%d)", (p+i)->x,(p+i)->y);
	}
	Point *X,*Y;
	float distance;
	X = Sort(p, 10, 1);
	distance=Count_Distance2(X, 10);
	printf("\n分治求解：%.2f\n", distance);
	/*以下注释是测试排序的可用性*/
	/*X = (Point*)malloc(sizeof(Point) * 10);
	for (int i = 0; i < 10; i++)
	{
		(X + i)->x = (p + i)->y;
		(X + i)->y = (p + i)->x;
	}
	for (int i = 0; i < 10; i++) {
		printf("(%d,%d)", (X + i)->x, (X + i)->y);
	}
	printf("\n");
	Y=Merge(p, X, 20,0);
	for (int i = 0; i < 20; i++)
	{
		printf("%d ", (Y + i)->y);
	}
	X = Sort(&p[0], 10, 1);
	Y = Sort(&p[0], 10, 0);
	//Sort(p, 10, 1);
	printf("\nX:");
	for (int i = 0; i < 10; i++) {
		printf(" %d",(X+i)->x);
	}
	printf("\nY:");
	for (int i = 0; i < 10; i++) {
		printf(" %d", (Y + i)->y);
	}*/



	//goto_xy(0, 101);
	printf("暴力求解为：%.2f\n", Count_Distance1(&p[0], 10));


	//system("pause");
}


int main()
{
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		distance_main();
	}

	system("pause");
}