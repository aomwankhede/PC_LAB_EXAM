#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[]){
   int rank,size;
   
   int arr[] = {3,2,100,4,1,7};
   int local = -1;
   int global = -1;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   int start = (rank * 6) / size;
   int end = ((rank+1) * 6)/size;
   for(int i=start;i<end;i++ ){
   	if(local < arr[i]){
   		local = arr[i];
   	}
   }
   MPI_Reduce(&local,&global,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
   if(rank == 0){
   	printf("The maximum is %d",global);
   }
   MPI_Finalize();
   return 0;
}
