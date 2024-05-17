#include<stdio.h>
#include<omp.h>

int main()
{	
	int noOfElements;
	int i = 0;
	int maxi = -1;
	int arr[1000];
	printf("Enter the size of array :- ");
	scanf("%d",&noOfElements);
	printf("Enter the array :- ");
	for(int i=0;i<noOfElements;i++){
		scanf("%d",&arr[i]);
	}
	#pragma omp parallel for private(i) shared(maxi)
	for(i=0;i<noOfElements;i++){
		#pragma omp critical
		if(arr[i] > maxi){
			maxi = arr[i];
		}
	}
	printf("The maximum ELement in the array is %d",maxi);
	return 0;
}
