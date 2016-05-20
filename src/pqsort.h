/*
 * pqsort.h
 *
 *  Created on: 19.05.2016
 *      Author: Belokrys-Fedotov A.I.
 */

#ifndef PQSORT_H_
#define PQSORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PQSORT_LIMIT_PER_PROC 1
//100

#ifdef WIN
#ifndef __compar_fn_t
typedef int (__cdecl*__compar_fn_t)(const void*,const void*);
#endif
#endif

void pqsort (void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar);


#endif /* PQSORT_H_ */
