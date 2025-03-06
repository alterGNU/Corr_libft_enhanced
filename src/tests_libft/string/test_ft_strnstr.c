#include "libft.h"      //ft_strnstr
#include <bsd/string.h> // strnstr
#include <stdio.h>      // printf

int	compare(const char *big, const char *little, size_t length)
{
	char	*real;

	real = strnstr(big, little, length);
	//printf("REAL:%s\n", real);
	//return (0);
	
	char	*ft;
	ft = ft_strnstr(big, little, length);
	printf("strnstr(\"%s\", \"%s\", %ld) = real[%s](vs)ft[%s]",big, little, length ,real ,ft);
	printf((real == ft)?"---------->PASS\n" : "---------->FAIL\n");
	return (real != ft);
}

int	main()
{
	int	nb_err = 0;
	// CAS PARTICULIERS DE NULL
	printf("\n------ CAS PARTICULIERS:\n");
	printf("big=NULL, small="" et n=0\n");
	nb_err+=compare(NULL, "", 0);
	printf("big=NULL, small=\"\" et n=1\n");
	nb_err+=compare(NULL, "", 2);
	printf("big="", small=\"x\" et n=0\n");
	nb_err+=compare("", "x", 0);
	printf("big="", small=\"x\" et n=1\n");
	nb_err+=compare("", "x", 1);
	printf("big=\"x\", small=\"x\" et n=1\n");
	nb_err+=compare("x", "x", 1);

	// CAS little == big
	printf("\n------ CAS:big=little=\"\":\n");
	for (int i=-1; i<2; i++)
		nb_err+=compare("", "", i);

	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "a", "a");
	for (int i=-1; i<4; i++)
		nb_err+=compare("a", "a", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "abc");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "abc", i);
	// CAS big:NON VIDE ET little=""
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "", i);
	// CAS big:"" ET little=NON VIDE
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "", "abc");
	for (int i=-1; i<4; i++)
		nb_err+=compare("", "abc", i);
	// CAS little not in big
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "d");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "d", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "ac");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "ac", i);
	// CAS little in big at start
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "a");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "a", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "ab");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "a", i);
	// CAS little in big at start
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "a");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "a", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abc", "bc");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abc", "bc", i);
	// CAS little multiple times in big
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abcab", "a");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abcab", "a", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abcab", "ab");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abcab", "ab", i);
	printf("\n------ CAS:big=\"%s\" little=\"%s\":\n", "abcabc", "bc");
	for (int i=-1; i<4; i++)
		nb_err+=compare("abcbc", "bc", i);
	// CAS big with \0
	printf("\n------ CAS:big=\"ab\\0cd\" little=\"%s\":\n", "c");
	for (int i=-1; i<4; i++)
	{
		nb_err+=compare("ab\0cd", "c", i);
		nb_err+=compare("ab\0cd", "cd", i);
	}

	return (nb_err);
}
