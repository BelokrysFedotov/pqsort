/*
 * readline.c
 *
 *  Created on: 26.06.2013
 *      Author: Belokrys-Fedotov A.I.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>
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

TEST(Test, test_check_int_sort){
	int*A;
	int N;
	int i;
	N = 100;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++)
		A[i] = i;

	ASSERT_EQ(check_int_sort(A,N),1);
	A[5] = 99;
	ASSERT_EQ(check_int_sort(A,N),0);

	for(i=0;i<N;i++)
		A[i] = N-i;
	ASSERT_EQ(check_int_sort(A,N),0);

	free(A);

}

void test_sort(int*A,int N){
	int*B;

	B = (int*)calloc(N,sizeof(int));
	memcpy(B,A,N*sizeof(int));

	pqsort(A,N,sizeof(int),_comp_int);
	 qsort(B,N,sizeof(int),_comp_int);

	ASSERT_EQ(check_int_sort(A,N),1);
	ASSERT_EQ(check_int_sort(B,N),1);
	ASSERT_EQ(cmp_int_array(A,B,N),1);
	free(B);

}

TEST(Test, test_check_int_123){
	int*A;
	int N;
	int i;

	N = 100;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = i;
	test_sort(A,N);
	free(A);
}

TEST(Test, test_check_int_321){
	int*A;
	int N;
	int i;

	N = 100;
	A = (int*)calloc(N,sizeof(int));
	for(i=0;i<N;i++) A[i] = N-i;
	test_sort(A,N);
	free(A);
}

TEST(Test, test_check_int_rand){
	int*A;
	int N;
	int i,n;

	for(n=0;n<10;n++){
		N = rand()%1000000+100;
		A = (int*)calloc(N,sizeof(int));
		for(i=0;i<N;i++)
			A[i] = rand();

		test_sort(A,N);
		free(A);
	}

}


/*TEST(Test, in_charset){
	ASSERT_LT(in_charset('a',CHARSET_SPACE), 0);
	ASSERT_LT(in_charset('0',CHARSET_SPACE), 0);
    ASSERT_LT(in_charset('9',CHARSET_SPACE), 0);
    ASSERT_GE(in_charset(' ',CHARSET_SPACE), 0);
    ASSERT_GE(in_charset('\t',CHARSET_SPACE), 0);
    ASSERT_GE(in_charset('\r',CHARSET_SPACE), 0);
    ASSERT_GE(in_charset('\n',CHARSET_SPACE), 0);
}

#define _TRIMC_TEST(FROM,TO,FUNCTION,CHARSET) 	strcpy(string1,FROM); \
	strcpy(string2,TO); \
	FUNCTION(string1,CHARSET); \
	ASSERT_STREQ(string1,string2);

#define _TRIM_TEST(FROM,TO,FUNCTION) 	strcpy(string1,FROM); \
	strcpy(string2,TO); \
	FUNCTION(string1); \
	ASSERT_STREQ(string1,string2);

TEST(Test, string_ltrim_charset){
	char string1[256],string2[256];

	_TRIMC_TEST("samplestring","samplestring",string_ltrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("sample  string","sample  string",string_ltrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("samplestring  ","samplestring  ",string_ltrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("  samplestring","samplestring",string_ltrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t   samplestring","samplestring",string_ltrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t sample  string  ","sample  string  ",string_ltrim_charset,CHARSET_SPACE)

}

TEST(Test, string_rtrim_charset){
	char string1[256],string2[256];

	_TRIMC_TEST("samplestring","samplestring",string_rtrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("sample  string","sample  string",string_rtrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("samplestring  ","samplestring",string_rtrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("  samplestring","  samplestring",string_rtrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t   samplestring\t   ","\t   samplestring",string_rtrim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t sample  string \t ","\t sample  string",string_rtrim_charset,CHARSET_SPACE)

}

TEST(Test, string_trim_charset){
	char string1[256],string2[256];

	_TRIMC_TEST("samplestring","samplestring",string_trim_charset,CHARSET_SPACE)
	_TRIMC_TEST("sample  string","sample  string",string_trim_charset,CHARSET_SPACE)
	_TRIMC_TEST("samplestring  ","samplestring",string_trim_charset,CHARSET_SPACE)
	_TRIMC_TEST("  samplestring","samplestring",string_trim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t   samplestring\t   ","samplestring",string_trim_charset,CHARSET_SPACE)
	_TRIMC_TEST("\t sample  string \t ","sample  string",string_trim_charset,CHARSET_SPACE)

}


TEST(Test, string_trim){
	char string1[256],string2[256];

	_TRIM_TEST("samplestring","samplestring",string_trim)
	_TRIM_TEST("sample  string","sample  string",string_trim)
	_TRIM_TEST("samplestring  ","samplestring",string_trim)
	_TRIM_TEST("  samplestring","samplestring",string_trim)
	_TRIM_TEST("\t   samplestring\t   ","samplestring",string_trim)
	_TRIM_TEST("\t sample  string \t ","sample  string",string_trim)

}


TEST(Test, string_is_integer){
    ASSERT_EQ(string_is_integer("a"), 0);
    ASSERT_EQ(string_is_integer("aasd"), 0);
    ASSERT_EQ(string_is_integer("aa2sd"), 0);
    ASSERT_EQ(string_is_integer("3aa2sd"), 0);
    ASSERT_EQ(string_is_integer("321a"), 0);
    ASSERT_EQ(string_is_integer("321 "), 0);
    ASSERT_EQ(string_is_integer("321"), 1);
    ASSERT_EQ(string_is_integer("+321"), 1);
    ASSERT_EQ(string_is_integer("-321"), 1);
    ASSERT_EQ(string_is_integer("-321+"), 0);
    ASSERT_EQ(string_is_integer("-32-1"), 0);
    ASSERT_EQ(string_is_integer("-32.1"), 0);
}


TEST(Test, string_count_of_words){
    ASSERT_EQ(string_count_of_words(""), 0);
    ASSERT_EQ(string_count_of_words("a"), 1);
    ASSERT_EQ(string_count_of_words("aasd"), 1);
    ASSERT_EQ(string_count_of_words("aasd  asdads"), 2);
    ASSERT_EQ(string_count_of_words(" aasd  asdads "), 2);
    ASSERT_EQ(string_count_of_words(" aasd \t  \n asdads "), 2);
    ASSERT_EQ(string_count_of_words(" aasd  asdads asdasd "), 3);
    ASSERT_EQ(string_count_of_words("a a s d  a s d a d s asdasd "), 11);
}

TEST(Test, string_cut_word){
	char string[256];
	char word[256];

#define _TEST_string_cut_word(F,R,T,W) 	strcpy(string,F); \
	ASSERT_EQ(string_cut_word(string,word),R); \
	ASSERT_STREQ(string,T); \
	ASSERT_STREQ(word,W);

	_TEST_string_cut_word("",0,"","")

	_TEST_string_cut_word("   ",0,"","")
	_TEST_string_cut_word("  \t ",0,"","")

	_TEST_string_cut_word("a",1,"","a")
	_TEST_string_cut_word("aasdzxc",1,"","aasdzxc")
	_TEST_string_cut_word("  aasdzxc",1,"","aasdzxc")
	_TEST_string_cut_word("aas-dzxc  ",1,"","aas-dzxc")
	_TEST_string_cut_word("  aa123sdzxc   ",1,"","aa123sdzxc")

	_TEST_string_cut_word("aasdzxc vvdaa",1,"vvdaa","aasdzxc")
	_TEST_string_cut_word(" aasdzxc vvdaa asdasfgasf",1,"vvdaa asdasfgasf","aasdzxc")
	_TEST_string_cut_word(" adasd123asdzxc vvdaa asdasfgasf   asd1asd a",1,"vvdaa asdasfgasf   asd1asd a","adasd123asdzxc")

	strcpy(string," adasd123asdzxc vvdaa asdasfgasf   asd1asd a  ");
	ASSERT_EQ(string_cut_word(string,word),1);
	ASSERT_STREQ(string,"vvdaa asdasfgasf   asd1asd a  ");
	ASSERT_STREQ(word,"adasd123asdzxc");

	ASSERT_EQ(string_cut_word(string,word),1);
	ASSERT_STREQ(string,"asdasfgasf   asd1asd a  ");
	ASSERT_STREQ(word,"vvdaa");

	ASSERT_EQ(string_cut_word(string,word),1);
	ASSERT_STREQ(string,"asd1asd a  ");
	ASSERT_STREQ(word,"asdasfgasf");

	ASSERT_EQ(string_cut_word(string,word),1);
	ASSERT_STREQ(string,"a  ");
	ASSERT_STREQ(word,"asd1asd");

	ASSERT_EQ(string_cut_word(string,word),1);
	ASSERT_STREQ(string,"");
	ASSERT_STREQ(word,"a");

	ASSERT_EQ(string_cut_word(string,word),0);
	ASSERT_STREQ(string,"");
	ASSERT_STREQ(word,"");
}*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
