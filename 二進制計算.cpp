 #include <stdio.h>

void Function_print(int ans){
	if(ans){
		printf("1"); 
	}
	else
		printf("0");
}
int* Fib_array(int *n){
	int i;
	n[0]=1;
	n[1]=2;
	for(i=2;i<39;i++){
		n[i]=n[i-1]+n[i-2];
	}
	return n;
}
int main(){
	int number[500]={0};
	int count;
	scanf("%d",&count);
	
	do{
		int count_1=0,i,k;
		printf("\n");
		scanf("%d",&number[0]);	
    	int n[50];
		int *fib= Fib_array(n); 
		//int ans[100]={0};
		for(i=30;i>=0;i--){
			if(number[0]>=fib[i]){
				number[0]=number[0]-fib[i];
				i--;
				Function_print(1);
				count_1++;			
			}
			if(count_1!=0&&number[0]<fib[i]){
				Function_print(0);
			}
		}
		count--;
	}while(count>0);
	return 0;
}
