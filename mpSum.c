#include<stdio.h>
#include<omp.h>

int main()
{	
	int noOfElements;
	int i = 0;
	int sum = 0;
	int arr[1000];
	printf("Enter the size of array :- ");
	scanf("%d",&noOfElements);
	printf("Enter the array :- ");
	for(int i=0;i<noOfElements;i++){
		scanf("%d",&arr[i]);
	}
	#pragma omp parallel for private(i) shared(sum)
	for(i=0;i<noOfElements;i++){
		#pragma omp critical
		sum+=arr[i];
	}
	printf("The sum of the array is %d",sum);
	return 0;
}
