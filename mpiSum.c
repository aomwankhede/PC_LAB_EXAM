#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[]){
   int rank,size;
   
   int n = 100;
   int local = 0;
   int global = 0;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   int start = (rank * n) / size;
   int end = ((rank+1) * n)/size;
   for(int i=start;i<end;i++ ){
   	local+=i;
   }
   MPI_Reduce(&local,&global,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
   if(rank == 0){
   	printf("The sum is %d",global);
   }
   MPI_Finalize();
   return 0;
}
