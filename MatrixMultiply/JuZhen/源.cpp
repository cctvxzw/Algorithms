#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<math.h>
#define max 10;
#define min 1;


/*----------------------------------------*/
//            打印矩阵函数                //
/*---------------------------------------*/

void Square_print(int* A,int n) {

	printf("\n");
	for (int i = 0; i < (int)pow(n,2); i++)
	{
		printf("%d ", *(A + i));
		if ((i + 1) % n == 0) {
			printf("\n");
		}
	}
}

/*----------------------------------------*/
//            暴力矩阵相乘函数             //
/*---------------------------------------*/

int* Square_Multiply(int* A, int* B,int n) {

	int*C;
	//创建数组要标注大小和多少
	C = (int*)(malloc(sizeof(int)*n*n));
	for (int t = 0; t < n*n; t++)
	{
	//注意初始化
		*(C + t) = 0;
	}
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				*(C+i*n+j) += (*(A + n * i + k))*(*(B + n * k + j ));
				//printf("%d * %d ", *(A + 4 * i + k), *(B + 4 * k + j));
			}
			//printf("%d\n", *(C + i * 4 + j));
		}
	}
	return C;
}


/*----------------------------------------*/
//            矩阵相加函数                //
/*---------------------------------------*/

int* Square_add(int *A,int *B,int flag,int n) {

	int i;
	int *D;
	D = (int*)malloc(sizeof(int)*n*n);
	for (i = 0; i < pow(n,2); i++)
	{
		*(D + i) = 0;
	}
	if (flag == 1) {
		for (i = 0; i < pow(n,2); i++) {
			*(D + i) = *(A + i) + *(B + i);
		}
	}
	else if(flag == 0){
		for (i = 0; i < pow(n,2); i++) {
			*(D + i) = *(A + i) - *(B + i);
		}
	}
	/*for (i = 0; i < 16; i++)
	{
		printf("%d ", *(D + i));
	}
	printf("\n");*/
	return D;
}

/*----------------------------------------*/
//          矩阵合并函数                 //
/*---------------------------------------*/

int* Square_seal(int*A1, int*A2, int*A3, int*A4, int n)
{
	int*A;
	int i, j;
	A = (int*)malloc(sizeof(int)*(int)pow(2*n, 2));
	for (i = 0; i < 4 * n*n; i++) {
		*(A + i) = 0;
	}
	int t = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(A + j + 2 * n * i) = *(A1 + t);
			t++;
		}
	}
	t = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(A + j + 2 * n * i + n) = *(A2 + t);
			t++;
		}
	}
	t = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(A + j + 2 * n * (i+n) ) = *(A3 + t);
			t++;
		}
	}
	t = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(A + j + 2 * n * (i + n)+n) = *(A4 + t);
			t++;
		}
	}
	/*printf("\n");
	for (i = 0; i < 4*n*n; i++) {
		printf("%d ", *(A + i));
	}*/
	return A;
}


/*----------------------------------------*/
//            拆分矩阵函数                //
/*---------------------------------------*/


int* Square_seperate(int *A,int n,int flag) {
	int *G;
	int i,k,t;
	int m = pow(n / 2, 2);
	G = (int*)malloc(sizeof(int)*n / 2 * n / 2);
	for ( t = 0; t < n/2*n/2; t++)
	{
		*(G+t) = 0;
	}
	if (flag == 1) {
		t = 0;
		for (i = 0; i < n / 2 ; i++)
		{
			for (k = 0; k < n / 2; k++)
			{
				*(G + t) = *(A + i * n + k);
				t++;
			}
		}
	}

	else if (flag == 2) {
		t = 0;
		for (i = 0; i < n / 2; i++)
		{
			for (k = 0; k < n / 2; k++)
			{
				*(G + t) = *(A + i * n + k + n/2);
				t++;
			}
		}
	}
	else if (flag == 3) {
		t = 0;
		for (i = 0; i < n / 2; i++)
		{
			for (k = 0; k < n / 2; k++)
			{
				*(G + t) = *(A + (i + n / 2) * n + k);
				t++;
			}
		}
	}
	else if (flag == 4) {
		t = 0;
		for (i = 0; i < n / 2; i++)
		{
			for (k = 0; k < n / 2; k++)
			{
				*(G + t) = *(A + (i + n / 2) * n + k + n/2);
				t++;
			}
		}
	}

	return G;
}



/*----------------------------------------*/
//          矩阵相乘主函数                //
/*---------------------------------------*/



int* Square_Multiply2(int *A, int *B,int n) {

	int *A1, *A2, *A3, *A4, *B1, *B2, *B3, *B4, *S1, *S2, *S3, *S4, *S5, *S6, *S7, *S8, *S9, *S10, *P1, *P2, *P3, *P4, *P5, *P6, *P7, *C1, *C2, *C3, *C4;
	int *C;
	C = (int*)malloc(sizeof(int)*n*n);
	if (n == 1) {
		*C = (*A)*(*B);
	}
	else {
		A1 = Square_seperate(A, n, 1);
		A2 = Square_seperate(A, n, 2);
		A3 = Square_seperate(A, n, 3);
		A4 = Square_seperate(A, n, 4);
		B1 = Square_seperate(B, n, 1);
		B2 = Square_seperate(B, n, 2);
		B3 = Square_seperate(B, n, 3);
		B4 = Square_seperate(B, n, 4);
		S1 = Square_add(B2, B4, 0,n/2);
		S2 = Square_add(A1, A2, 1,n/2);
		S3 = Square_add(A3, A4, 1,n/2);
		S4 = Square_add(B3, B1, 0,n/2);
		S5 = Square_add(A1, A4, 1,n/2);
		S6 = Square_add(B1, B4, 1,n/2);
		S7 = Square_add(A2, A4, 0,n/2);
		S8 = Square_add(B3, B4, 1,n/2);
		S9 = Square_add(A1, A3, 0,n/2);
		S10 = Square_add(B1, B2, 1,n/2);
		P1 = Square_Multiply2(A1, S1, n / 2);
		P2 = Square_Multiply2(S2, B4, n / 2);
		P3 = Square_Multiply2(S3, B1, n / 2);
		P4 = Square_Multiply2(A4, S4, n / 2);
		P5 = Square_Multiply2(S5, S6, n / 2);
		P6 = Square_Multiply2(S7, S8, n / 2);
		P7 = Square_Multiply2(S9, S10, n / 2);
		C1 = Square_add(Square_add(P5, P4, 1,n/2), Square_add(P2, P6, 0,n/2), 0,n/2);
		C2 = Square_add(P1, P2, 1,n/2);
		C3 = Square_add(P3, P4, 1,n/2);
		C4 = Square_add(Square_add(P5, P1, 1,n/2), Square_add(P3, P7, 1,n/2), 0,n/2);
		C = Square_seal(C1, C2, C3, C4, n / 2);
		n = n / 2;
	}

	return C;
}





int main() {
	
	int A[8][8] = {};
	int B[8][8] = {};
	int* a = &A[0][0];
	int* b = &B[0][0];
	srand(time(0));
	for (int i = 0; i < 64; i++) {
		*(a+i) = rand() % (10 - 1) + 1;
	}
	for (int i = 0; i < 64; i++) {
		*(b + i) = rand() % (10 - 1) + 1;
	}
	//A[0][0] = 2;
	//B[0][0] = 3;
	Square_print(&A[0][0],8);
	Square_print(&B[0][0], 8);
	printf("\n");
	//Square_print(&B[0][0],16);
	//Square_print(Square_Multiply(&A[0][0], &B[0][0]));
	//Square_print(Square_Multiply(&A[0][0], &B[0][0]));
	//int* G = Square_print(&A[0][0]);
	//Square_print(Square_Multiply(&A[0][0], &B[0][0]));
	//Square_print(Square_seal(Square_seperate(&A[0][0],4,1), Square_seperate(&A[0][0],4,2), Square_seperate(&A[0][0],4,3), Square_seperate(&A[0][0],4,4),2),16);
	//Square_seal(Square_seperate(&A[0][0], 4, 1), Square_seperate(&A[0][0], 4, 2), Square_seperate(&A[0][0], 4, 3), Square_seperate(&A[0][0], 4, 4), 2);
	Square_print(Square_Multiply(&A[0][0], &B[0][0],8), 8);
	Square_print(Square_Multiply2(&A[0][0], &B[0][0], 8), 8);
	//Square_print(Square_seperate(&A[0][0], 4, 3), 2);
	system("pause");
}