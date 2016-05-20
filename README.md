pqsort - parallel quick sort over OpenMP
=======
[![Build Status](https://travis-ci.org/BelokrysFedotov/pqsort.svg?branch=master)](https://travis-ci.org/BelokrysFedotov/pqsort)

Lib for parallel sorting with OpenMP on C.
Array divided on each threads, that use qsort on own parts, then parts sorting via merge sort.