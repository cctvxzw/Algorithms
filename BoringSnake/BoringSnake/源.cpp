#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include <time.h>

int speedFlag=0;
int pace = 0;			//用来标志蛇处于何种状态

int Random(int start, int end) {
	int dis = end - start;
	return rand() % dis + start;
}


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

/*struct Snake {
	int x;
	int y;
	Snake *next;
};*/

void gameOver(int *a){
	goto_xy(2, 21);
	printf("gameover\n");
}

struct Snakehead
{
	int x;
	int y;
	int length;
	int dire;				//0,1,2,3分别表示上右下左
	Snakehead *next;
}*snakehead;

Snakehead* drawBody(Snakehead *head) {
	Snakehead *body;
	Snakehead *sup1;
	Snakehead *sup2;
	body = (Snakehead*)malloc(sizeof(Snakehead));
	body->x = head->x - 1;
	body->y = head->y;
	sup1 = body;
	for (int i = 1; i < head->length - 1; i++) {
		sup2 = (Snakehead*)malloc(sizeof(Snakehead));
		sup2->x = sup1->x - 1;
		sup2->y = sup1->y;
		sup1->next = sup2;
		sup1 = sup2;
	}
	sup1->next = NULL;
	return body;
}

Snakehead* genSnake() {
	Snakehead *head;
	head = (Snakehead*)malloc(sizeof(Snakehead));
	head->length = 3;
	head->x = 10;
	head->y = 10;
	head->dire = 1;
	head->next=drawBody(head);
	return head;
}

int moveonSnake1(Snakehead* head,int *n) {
	Snakehead* point;
	int a, b, c, d, t1, t2;
	point = head;
	a = c = head->x;
	b = d = head->y;
	t1 = t2 = head->dire;
	if (*(n+head->x+head->y*20+1)==3)
	{
		//head->x = (head->x + 3) % 20;
		return 1;
	}
	else if (*(n + head->x + head->y * 20 + 1) == 1)
	{
		return 1;
	}
	else if (*(n + head->x + head->y * 20 + 1) == 4)
	{
		*(n + head->x + head->y * 20 + 1) = 0;
		return 4;
	}
	else if (*(n + head->x + head->y * 20 + 1) == 5)
	{
		*(n + head->x + head->y * 20 + 1) = 0;
		return 5;
	}
	else {
		/*把尾巴还原*/
		do{
			point = point->next;
		} while (point->next != NULL);
		*(n + point->x + point->y * 20) = 0;
		point = head;
		head->x = (head->x + 1) % 20;
		for (int i = 1; i < head->length; i++) {
			a = point->next->x;
			b = point->next->y;
			t1 = point->next->dire;
			point->next->x = c;
			point->next->y = d;
			point->next->dire = t2;
			c = a;
			d = b;
			t2 = t1;
			point = point->next;
		}
		return 10;
	}
}

int moveonSnake0(Snakehead* head,int *n) {
	Snakehead* point;
	int a, b, c, d, t1, t2;
	point = head;
	a = c = head->x;
	b = d = head->y;
	t1 = t2 = head->dire;
	if (*(n + (head->y - 1) * 20 + head->x) == 2)
	{
		//head->y = (head->y +17) % 20;
		return 0;
	}
	else if(*(n + (head->y - 1) * 20 + head->x) == 1)
	{
		return 0;
	}
	else if (*(n + head->x + head->y * 20 - 20) == 4)
	{
		*(n + head->x + head->y * 20 - 20) = 0;
		return 4;
	}
	else if (*(n + head->x + head->y * 20 - 20) == 5)
	{
		*(n + head->x + head->y * 20 - 20) = 0;
		return 5;
	}
	else {
		/*把尾巴还原*/
		do {
			point = point->next;
		} while (point->next != NULL);
		*(n + point->x + point->y * 20) = 0;
		point = head;
		head->y = (head->y - 1) % 20;
		for (int i = 1; i < head->length; i++) {
			a = point->next->x;
			b = point->next->y;
			t1 = point->next->dire;
			point->next->x = c;
			point->next->y = d;
			point->next->dire = t2;
			c = a;
			d = b;
			t2 = t1;
			point = point->next;
		}
		return 10;
	}
}

int moveonSnake2(Snakehead* head,int *n) {
	Snakehead* point;
	int a, b, c, d, t1, t2;
	point = head;
	a = c = head->x;
	b = d = head->y;
	t1 = t2 = head->dire;
	if (*(n + (head->y + 1) * 20 + head->x) == 2)
	{
		//head->y = (head->y + 3) % 20;
		return 2;
	}
	else if (*(n + (head->y + 1) * 20 + head->x) == 1)
	{
		return 2;
	}
	else if (*(n + head->x + head->y * 20 + 20) == 4)
	{
		*(n + head->x + head->y * 20 + 20) = 0;
		return 4;
	}
	else if (*(n + head->x + head->y * 20 + 20) == 5)
	{
		*(n + head->x + head->y * 20 + 20) = 0;
		return 5;
	}
	else {
		/*把尾巴还原*/
		do {
			point = point->next;
		} while (point->next != NULL);
		*(n + point->x + point->y * 20) = 0;
		point = head;
		head->y = (head->y + 1)%20;
		for (int i = 1; i < head->length; i++) {
			a = point->next->x;
			b = point->next->y;
			t1 = point->next->dire;
			point->next->x = c;
			point->next->y = d;
			point->next->dire = t2;
			c = a;
			d = b;
			t2 = t1;
			point = point->next;
		}
		return 10;
	}
	
}

int moveonSnake3(Snakehead* head,int *n) {
	Snakehead* point;
	int flag = 10;
	int a, b, c, d, t1, t2;
	point = head;
	a = c = head->x;
	b = d = head->y;
	t1 = t2 = head->dire;
	if (*(n + (head->x - 1) + head->y * 20) == 3)
	{
		//head->x = (head->x + 17) % 20;
		return 3;
	}
	else if (*(n + head->x + head->y * 20 - 1) == 4)
	{
		*(n + head->x + head->y * 20 - 1) = 0;
		return 4;
	}
	else if (*(n + head->x + head->y * 20 - 1) == 1)
	{
		return 3;
	}
	else if (*(n + head->x + head->y * 20 - 1) == 5)
	{
		*(n + head->x + head->y * 20 - 1) = 0;
		return 5;
	}
	else {
		/*把尾巴还原*/
		do {
			point = point->next;
		} while (point->next != NULL);
		*(n + point->x + point->y * 20) = 0;
		point = head;
		head->x = (head->x - 1)%20;
		for (int i = 1; i < head->length; i++) {
			a = point->next->x;
			b = point->next->y;
			t1 = point->next->dire;
			point->next->x = c;
			point->next->y = d;
			point->next->dire = t2;
			c = a;
			d = b;
			t2 = t1;
			point = point->next;
		}
		return 10;
	}
}


Snakehead* growSnake(Snakehead *head)
{
	Snakehead *point2;
	point2 = (Snakehead*)malloc(sizeof(Snakehead));
	switch (head->dire)
	{
	case 0:
		point2->y = head->y - 1;
		point2->x = head->x;
		point2->dire = head->dire;
		break;
	case 1:
		point2->x = head->x + 1;
		point2->y = head->y;
		point2->dire = head->dire;
		break;
	case 2:
		point2->y = head->y + 1;
		point2->x = head->x;
		point2->dire = head->dire;
		break;
	case 3:
		point2->x = head->x - 1;
		point2->y = head->y;
		point2->dire = head->dire;
		break;
	default:
		break;
	}
	point2->next = head;
	point2->length = head->length + 1;
	head = point2;

	if (pace > 0)
		pace--;

	return head;
}

void speedUp() {
	speedFlag = 1;
}

Snakehead* moveSnake(Snakehead* head,int *a) {

	int ch=0;

	/*读取键盘输入*/
	if(_kbhit()) {
		ch = _getch();
		if (ch == 65 || ch == 97) {
			if (head->dire != 1) {
				head->dire = 3;
			}
		}
		else if (ch == 83 || ch == 115) {
			if (head->dire != 0) {
				head->dire = 2;
			}
		}
		else if (ch == 69 || ch == 100) {
			if (head->dire != 3) {
				head->dire = 1;
			}
		}
		else if (ch == 87 || ch == 119) {
			if (head->dire != 2)
				head->dire = 0;
		}
	}

	int flag;

	switch (head->dire)
	{
	case 0:
		flag=moveonSnake0(head,a);
		break;
	case 1:
		flag=moveonSnake1(head,a);
		break;
	case 2:
		flag=moveonSnake2(head,a);
		break;
	case 3:
		flag=moveonSnake3(head,a);
		break;
	default:
		break;
	}

	if (flag == 0 || flag == 1 || flag == 2 || flag == 3)
	{
		gameOver(a);
	}
	else if (flag == 4)
	{
		head = growSnake(head);
		int x, y;
		do
		{
			x = Random(1, 19);
			y = Random(1, 19);
		} while (*(a + x + y * 20) != 0 );
		*(a + x + y * 20) = 4;
	}
	else if (flag == 5)
	{
		speedUp();
		int m, n;
		do
		{
			m = Random(1, 19);
			n = Random(1, 19);
		} while (*(a + m + n * 20) != 0);
		*(a + m + n * 20) = 5;
	}
		

	return head;
}


int* drawSnake(int *a, Snakehead *head, int n) {
	Snakehead *point;
	
	point = head;
	*(a + point->y*n + point->x) = 1;
	for (int i = 0; i < (head->length-1); i++)
	{
		point = point->next;
		*(a + point->y*n + point->x) = 1;
	}
	return a;
}



void drawMap(int *a,int n) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);

	int i;
	int x;
	int y;
	for (i = 0; i < n*n; i++)
	{
		if (*(a + i) == 2) {
			y = (int)(i / n);
			x = (i % n)*2;
			goto_xy(x, y);
			printf("==");
		}
		else if (*(a + i) == 0) {
			y = (int)(i / n);
			x = (i % n) * 2;
			goto_xy(x, y);
			printf("  ");
		}
		else if (*(a + i) == 3) {
			y = (int)(i / n);
			x = (i % n)*2;
			goto_xy(x, y);
			printf("||");
		}
		else if (*(a + i) == 1) {
			y = (int)(i / n);
			x = (i % n) * 2;
			goto_xy(x, y);
			printf("■");
		}
		else if (*(a + i) == 4) {
			y = (int)(i / n);
			x = (i % n) * 2;
			goto_xy(x, y);
			printf("<>");
		}
		else if (*(a + i) == 5) {
			y = (int)(i / n);
			x = (i % n) * 2;
			goto_xy(x, y);
			printf("[]");
		}
	}
}

void gameOn(int *a, int n,int speed)
{
	int statSpeed = speed;
	Snakehead *snake;
	snake = genSnake();
	drawMap(drawSnake(a, snake, n), n);
	srand((unsigned)time(NULL));
	while (1)
	{
		Sleep(speed);
		snake = moveSnake(snake, a);
		drawMap(drawSnake(a, snake, n), n);
		if (speedFlag == 0 && pace == 0) {
			speed = statSpeed;
		}
		else if (speedFlag == 1) {
			speed = speed / 2;
			pace = 3;
			speedFlag = 0;
		}
		/*goto_xy(2, 22);
		printf("speed：%d",speed);*/
	}
}

int main() {
	int a[20][20] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
					 3,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
					 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	gameOn(&a[0][0], 20, 100);
}










