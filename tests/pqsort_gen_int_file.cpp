#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C" {
	#include "../../src/pqsort.h"
}

void write_file(const char*filename,int*A,int N){
	FILE*fd;
	int i;
	fd = fopen(filename,"w");
	if(!fd)return;

	fprintf(fd,"%d\n",N);
	for(i=0;i<N;i++)
		fprintf(fd,"%d\n",A[i]);
	fclose(fd);

}

int main(int argc, char *argv[])
{
	int N,i,n;
	char filename[256];
	int*A;

	N = 100;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = i;
	write_file("123.ia",A,N);
	free(A);

	N = 100;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = N-i;
	write_file("321.ia",A,N);
	free(A);

	N = 16;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = N-i;
	write_file("321_16.ia",A,N);
	free(A);

	N = 35;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = N-i;
	write_file("321_35.ia",A,N);
	free(A);

	for(n=0;n<10;n++){
		N = rand()%1000000+100;
		A = (int*)calloc(N,sizeof(int));
		for(i=0;i<N;i++)
			A[i] = rand();
		sprintf(filename,"rand_%d.ia",n+1);
		write_file(filename,A,N);
		free(A);
	}

	N = 10;
	for(n=0;n<7;n++){
		N *= 10;
		A = (int*)calloc(N,sizeof(int));
		for(i=0;i<N;i++)
			A[i] = rand();
		sprintf(filename,"size_1e%d_rand.ia",n+2);
		write_file(filename,A,N);
		free(A);
	}

    return 0;
}
