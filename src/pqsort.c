/*
 * pqsort.h
 *
 *  Created on: 19.05.2016
 *      Author: Belokrys-Fedotov A.I.
 */

#include "stdlib.h"

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_num_threads() 0
#endif

#include "pqsort.h"

int check_int_sort(int*a,int N){
	int i;
	for(i=0;i+1<N;i++)
		if(a[i]>a[i+1])
			return 0;
	return 1;
}

inline void _merge(void *__base,void *__buffer,size_t __size, __compar_fn_t __compar,
		size_t pa, size_t pb, size_t pc){
	size_t ai,aj,bi,bj,i;
	int c;

	ai = aj = pa;
	bi = bj = pb;
	i = pa;
	while(aj<pb && bj<pc){
		c = __compar(__base+__size*aj,__base+__size*bj);
		if(c<=0){
			if(bj!=bi){
				memcpy(__buffer+__size*i,__base+__size*bi,__size*(bj-bi));
				i += bj-bi;
				bi = bj;
			}
			aj++;
		}else{
			if(aj!=ai){
				memcpy(__buffer+__size*i,__base+__size*ai,__size*(aj-ai));
				i += aj-ai;
				ai = aj;
			}
			bj++;
		}
	}
	if(aj!=ai){
		memcpy(__buffer+__size*i,__base+__size*ai,__size*(aj-ai));
		i += aj-ai;
		ai = aj;
	}
	if(bj!=bi){
		memcpy(__buffer+__size*i,__base+__size*bi,__size*(bj-bi));
		i += bj-bi;
		bi = bj;
	}
	if(aj<pb){
		aj = pb;
		if(aj!=ai){
			memcpy(__buffer+__size*i,__base+__size*ai,__size*(aj-ai));
			i += aj-ai;
			ai = aj;
		}
	}
	if(bj<pc){
		bj = pc;
		if(bj!=bi){
			memcpy(__buffer+__size*i,__base+__size*bi,__size*(bj-bi));
			i += bj-bi;
			bi = bj;
		}
	}
	//memcpy(__base+__size*pa,__buffer+__size*pa,__size*(pc-pa));

}

void pqsort (void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar){
	int i;
	int this_thread;
	int num_threads;
	void*B1,*B2,*bt;
	size_t np;
	size_t pa,pb,pc;

	#if defined(_OPENMP)
		#pragma omp parallel private(this_thread,num_threads,np,pa,pb,pc)
		{
			num_threads = omp_get_num_threads();

			if(num_threads==0 || num_threads==1 || num_threads*PQSORT_LIMIT_PER_PROC>__nmemb){
				#pragma omp single
				{
					qsort(__base,__nmemb,__size,__compar);
				}
			}else{
				this_thread = omp_get_thread_num();
				pa = (this_thread+0) * __nmemb / num_threads;
				pb = (this_thread+1) * __nmemb / num_threads;
				pc = pb - pa;
				//printf("%3d %3d %3d %3d\n",this_thread,pa,pb,pc);
				qsort(__base+pa*__size,pc,__size,__compar);
				#pragma omp single
				{
					B2 = __base;
					//B2 = malloc(__nmemb*__size);
					B1 = calloc(__nmemb,__size);
				}
				np = 1;
				while(np<num_threads){

					#pragma omp barrier
					#pragma omp single
					{
//						printf("%d switch %p <-> %p\n",this_thread,B1,B2);
						bt = B1; B1 = B2; B2 = bt;
					}
					if(this_thread%(np*2)==0){
						if(this_thread+np<num_threads){
							// merge part a and b

							pa = (this_thread+0) * __nmemb / num_threads;
							pb = (this_thread+np) * __nmemb / num_threads;
							pc = (this_thread+2*np) * __nmemb / num_threads;
							if(pc>__nmemb) pc = __nmemb;

//							printf("%d merge part %d and %d : [%lu..%lu] and [%lu..%lu] %p %p\n",this_thread,this_thread,this_thread+np,pa,pb,pb,pc,B1,B2);
							_merge(B1,B2,__size,__compar,pa,pb,pc);
//							printf("%d merge %d\n",this_thread,check_int_sort(B2+pa*__size,pc-pa));
						}
					}else{

					}
					np*=2;
				}

				#pragma omp barrier
				#pragma omp single
				{
//					printf("__base = %p\nB1     = %p\nB2     = %p\n",__base,B1,B2);
//					printf("%d result %d\n",this_thread,check_int_sort(__base,__nmemb));
//					printf("%d result %d\n",this_thread,check_int_sort(B1,__nmemb));
//					printf("%d result %d\n",this_thread,check_int_sort(B2,__nmemb));
					if(B2==__base){
						//bt = B1; B1 = B2; B2 = bt;
						free(B1);
					}else{
						memcpy(B1,B2,__nmemb*__size);
						free(B2);
					}
				}
			}
		}
	#else
		qsort(__base,__nmemb,__size,__compar);
	#endif

	//qsort(__base,__nmemb,__size,__compar);
}
