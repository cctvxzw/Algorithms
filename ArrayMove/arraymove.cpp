#include <stdio.h>
void change(int *a,int *b)
{
  int c;
  c=*a;
  *a=*b;
  *b=c;
}
void move(int *a,int N,int M)
{
  int i,j;
  M=M%N;
  //ȫ������
  for(i=0,j=N-1;i<j;i++,j--)
  {
    change(a+i,a+j);
  }
  //����ͷ��
  for(i=0,j=M-1;i<j;i++,j--)
  {
    change(a+i,a+j);
  }
  //����β��
  for(i=M,j=N-1;i<j;i++,j--)
  {
    change(a+i,a+j);
  }
  
}

//ʹ���˴����µ�����
/*int* move(int *a,int N,int M)
{
  int *b;
  int i;
  b=(int*)malloc(sizeof(int)*N);
  for(int i=0;i<N;i++)
  {
    *(b+i)=*(a+(i+N-M%N)%N);
  }
  return b;
}*/
int main()
{
  int N;
  int M;
  int i;
  int *a;
  scanf("%d %d",&N,&M);
  a=(int*)malloc(sizeof(int)*N);
  for(i=0;i<N;i++)
  {
    scanf("%d",a+i);
  }
  move(a,N,M);
  for(i=0;i<N-1;i++)
  {
    printf("%d ",*(a+i));
  }
  printf("%d",*(a+N-1));
  return 0;
}