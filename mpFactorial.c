#include<stdio.h>
#include<omp.h>

int main()
{	
	int n;
	int i = 0;
	int fact = 1;
	printf("Enter a number:- ");
	scanf("%d",&n);
	#pragma omp parallel for private(i) shared(fact)
	for(i=0;i<n;i++){
		#pragma omp critical
		fact*=(i+1);
	}
	printf("The factorial of the given number is %d",fact);
	return 0;
}
