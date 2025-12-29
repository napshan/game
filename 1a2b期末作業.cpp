#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
void guess(int a,int A,int b,int B,int number[4]);

int main(){
	int j,correct;
	int i,k;
	int a,A,b,B;
	char guessNum[4]; 
	int number_4[4];
	int number;
	int countA=0,countB=0;
	int randnumber[4];
		scanf("%s",guessNum);
		countA=0;
		countB=0;
		if(strlen(guessNum)!=4){
			printf("wrong number\n");
			scanf("%s",guessNum); 
			number = atoi(guessNum);
			printf("%d\n",number);
			for(i=3;i>=0;i--){
				number_4[i] = number%10;
				number = number/10;
			}
		}
		number = atoi(guessNum);
		for(i=3;i>=0;i--){
			number_4[i] = number%10;
			number = number/10;
	
		}
		while(number_4[3]<0||number_4[2]<0||number_4[2]<0||number_4[0]<0||number_4[3]>10||number_4[2]>10||number_4[1]>10||number_4[0]>10||number_4[3]==number_4[2]||number_4[3]==number_4[1]||number_4[3]==number_4[0]||number_4[2]==number_4[1]||number_4[1]==number_4[0]||number_4[2]==number_4[0]){
			printf("wrong number\n");
			scanf("%s",guessNum); 
			number = atoi(guessNum);
			for(i=3;i>=0;i--){
				number_4[i] = number%10;
				number = number/10;	
			}
		}
		srand(time(NULL));
		randnumber[0] = rand()%10;
		printf("randnum = %d",randnumber[0]);			
		for(k=1;k<4;k++){
			do{
				randnumber[k] = rand()%10;	
			}while(randnumber[k]==randnumber[k-1]||randnumber[k]==randnumber[k-2]||randnumber[k]==randnumber[k-3]);
			printf("%d",randnumber[k]);
		}
		printf("\n");
		scanf("%d%c%d%c",a,A,b,B);
		guess(a,A,b,B,number_4);
		return 0;
}
void guess(int a,int A,int b,int B,int number[4]){
	int i,k,count=0,randnumber[4];
	if(a==4){
		printf("correct");
	}
	if(a>0||b>0){
	}
	
	
}
