#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

extern "C" {
	#include "../../src/pqsort.h"
}

int check_int_sort(int*a,int N){
	int i;
	for(i=0;i+1<N;i++)
		if(a[i]>a[i+1])
			return 0;
	return 1;
}
int cmp_int_array(int*a,int*b,int N){
	int i;
	for(i=0;i<N;i++)
		if(a[i]!=b[i])
			return 0;
	return 1;
}

int _comp_int(const void *a, const void *b){
	if(*((int*)a)<*((int*)b))return -1;
	if(*((int*)a)>*((int*)b))return 1;
	return 0;
}

int test_sort(int*A,int N){
	int*B;
	double t,t1,t2;
	int num_threads;

	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
		}
	}

	B = (int*)calloc(N,sizeof(int));
	memcpy(B,A,N*sizeof(int));

	printf("N = %d\n",N);
	printf("num_threads = %d\n",num_threads);
	t = omp_get_wtime();
	pqsort(A,N,sizeof(int),_comp_int);
	t1 = omp_get_wtime()-t;
	printf("pqsort time = %lf\n",t1);
	t = omp_get_wtime();
	qsort(B,N,sizeof(int),_comp_int);
	t2 = omp_get_wtime()-t;
	printf(" qsort time = %lf\n",t2);
	printf("  acceleration %5.2lf\n",t2/t1);
	printf("  efficiency   %5.2lf%%\n",100.e0*t2/t1/num_threads);

	if(check_int_sort(A,N)!=1)return 1;
	if(check_int_sort(B,N)!=1)return 2;
	if(cmp_int_array(A,B,N)!=1)return 3;
	free(B);
	return 0;
}

int main(int argc, char *argv[])
{
	char*filename;
	FILE*fd;
	int N,i,j;
	int*A;

	if(argc<2)return 1;
	filename = argv[1];

	fd = fopen(filename,"r");
	if(!fd)return 1;

	i = fscanf(fd,"%d",&N);

	A = (int*)calloc(N,sizeof(int));

	for(i=0;i<N;i++)
		j = fscanf(fd,"%d",A+i);
	fclose(fd);
	printf("read.. ok\n");

	i = test_sort(A,N);
	if(i==0){
		printf("OK\n");
	}else{
		printf("FAIL (%d)\n",i);
	}

	free(A);
    return 0;
}
