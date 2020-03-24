#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
int main(){
	//输入数据
	int length1,length2;
	scanf("%d %d",&length1,&length2);
	int num1[50];
	char s1[50];
	scanf("%s",s1);
	for(int i=0;i<length1;i++){
		num1[i]=(int)s1[i]-48;		//字符转整型数字 
	}
	for(int i=0;i<length2-1;i++){
		num1[length1+i]=0;
	}
	
	
	printf("\n");
	
//	for(int i=0;i<length;i++){
//		printf("%d",num[i]);
//	}
//	
	char s2[50];
	int num2[50];
	scanf("%s",s2);
	for(int i=0;i<length2;i++){
		num2[i]=(int)s2[i]-48;
	}
	
	
		
	//处理数据
	int num4[50];
	int num3[50];
	
	for(int i=0;i<length1+length2-1;i++){
		num3[i]=num1[i];
	}
	
	for(int i=0;i<length1;i++){
		//如果开头是0则照常复制到下一次 
			if(num3[i]==0){
//				printf("0\n");
				for(int j=1;j<length2;j++){
					num4[j-1]=num3[i+j];
				}
			}
			//若开头是1则进行模2 
			else{
//				printf("1\n")
				for(int j=1;j<length2;j++){
					if(num3[i+j]==num2[j]){
						num4[j-1]=0;
					}
					else{
						num4[j-1]=1;
					}
				}
				for(int j=1;j<length2;j++){
					num3[i+j]=num4[j-1];
				}
			}
			
	}
	
//	printf("\n\n");
//	
	for(int j=1;j<length2;j++){
	//	printf("%d",num4[j-1]);
		num1[length1-1+j]=num4[j-1];
	}
	
	for(int i=0;i<length1+length2-1;i++){
		printf("%d",num1[i]);
	}
	
	printf("\n");
	
	
	//判断是否出错
	
	
	 
}
