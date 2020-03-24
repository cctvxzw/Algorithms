#include<stdio.h>
#include<stdlib.h>
struct Node{
	int first;
	int second;
	struct Node* next;
};
typedef struct Node* Poly;

Poly addpoly(Poly p1, Poly p2);
void attach(int a,int b,Poly *rear);
int compare(int a,int b);

int main()
{
	/*输入多项式*/
	int first, second;
	scanf("%d %d",&first,&second);
	Poly p1,p2,temp;
	Poly p1rear,p2rear;
	p1=(Poly)malloc(sizeof(struct Node));
	p1rear = p1; 
	p2=(Poly)malloc(sizeof(struct Node));
	p2rear = p2;
	for(int i=0;i<first;i++){
		temp = (Poly)malloc(sizeof(struct Node));
		scanf("%d %d",&temp->first,&temp->second);
		p1rear->next=temp;
		temp->next=NULL;
		p1rear=temp;
	}
	for(int i=0;i<second;i++){
		temp = (Poly)malloc(sizeof(struct Node));
		scanf("%d %d",&temp->first,&temp->second);
		p2rear->next=temp;
		temp->next=NULL;
		p2rear=temp;
	}
	
	temp=p1;
	p1=temp->next;
	
	temp=p2;
	p2=temp->next;
	
	free(temp);
	
	Poly p3;
	p3 = addpoly(p1,p2);
	
	
	while(p3){
		printf("%dx%d ",p3->first,p3->second);
		p3=p3->next;
	}
	
	return 0;
}






Poly addpoly(Poly p1, Poly p2){
	Poly front, rear, temp;
	int sum;
	rear = (Poly)malloc(sizeof(struct Node));
	front = rear;
	while(p1&&p2){
		switch(compare(p1->second,p2->second)){
			case 1:
				//printf("1\n");
				attach(p1->first,p1->second,&rear);
				p1=p1->next;
				break;
			case -1:
				//printf("-1\n");
				attach(p2->first,p2->second,&rear);
				p2=p2->next;
				break;
			case 0:
				//printf("0\n");
				sum=p1->first+p2->first;
				if(sum){
					attach(sum,p1->second,&rear);
					p1=p1->next;
					p2=p2->next;
				}
		}
	}
	
	for(;p1;p1=p1->next){
		attach(p1->first,p1->second,&rear);
		p1=p1->next;
	}
	
	for(;p2;p2=p2->next){
		attach(p2->first,p2->second,&rear);
		p2=p2->next;	
	}
	
	
	temp=front;
	front=temp->next;
	free(temp);
	
	//printf("%dx%d",front->first);
	
	return front;
}


int compare(int a,int b){
	if(a>b)
		return 1;
	else if(a<b)
		return -1;
	else if(a==b)
		return 0;
}


void attach(int a,int b,Poly *rear){
//	printf("%d %d",a,b);
	Poly p = (Poly)malloc(sizeof(struct Node));
	p->first=a;
	p->second=b;
	p->next=NULL;
	(*rear)->next=p;
	(*rear)=p;
}
