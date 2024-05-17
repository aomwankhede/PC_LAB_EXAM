#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[]){
   int rank,size;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   printf("rank:-%d, TotalProcessors:-%d\n",rank,size);
   if(rank==0){
   	char message[] = "Hello World";
        MPI_Send(message,strlen(message),MPI_CHAR,1,0,MPI_COMM_WORLD);
        char message2[] = "I am broadcasted!!!";
        MPI_Bcast(message2,strlen(message),MPI_CHAR,0,MPI_COMM_WORLD);
   }
   else{
   	char message[100];
   	MPI_Recv(message,100,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   	printf("Received Message:-%s , current rank :- %d ",message,rank);
   }	
   MPI_Finalize();
   return 0;
}
