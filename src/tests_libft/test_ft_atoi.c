#include "libft.h"  // ft_atoi
#include <stdlib.h> // atoi
#include <limits.h> // INT_MIN, INT_MAX
#include <stdio.h>  // printf

int	compare(const char *str)
{
	int	    real;
	int	    ft;

	real = atoi(str);
	ft = ft_atoi(str);
	printf("atoi(\"%s\") = real[%d] == ft[%d]\t", str, real, ft);
	int r = (real == ft);
	printf(r?"-------> PASS!\n" : "-------> FAIL!\n");
	return(!r);
}

int	main()
{
	int	nb_err=0;

	//CAS OBSERVATION COMPORTEMENT ASCII
	printf("CAS test atoi({0 <= i <= 127, '5', '\\0'}):\n");
	char	list0[128][4];
	for (int j=0; j<128; j++)
	{
		list0[j][0] = j;
		list0[j][1] = '5';
		list0[j][2] = '\0';
	}

	int		i = 0;
	while (i < 128)
		nb_err+=compare(list0[i++]);

	//CAS nb_err+=compare
	printf("CAS INTERESSANTS\n");
	char	int_min[16]; 
	char	int_max[16]; 
	snprintf(int_min, sizeof(int_min), "%d", INT_MIN);
	snprintf(int_max, sizeof(int_max), "%d", INT_MAX);
	char	*list[] = {\
		"+","++","  +","   ++","  ", " ","\n","\t\t","\t",\
		"+1","++1","  +1","   ++1","+42paris"," +42paris",\
		"+01","+001","++01","  +01","  +001","   ++01",\
		"-","--","  -","   --",\
		"-1","--1","  -1","   --1","-42paris"," -42paris",\
		"-01","-001","--01","  -01","  -001","   --01",\
		"0","00","01","+01","++01","+ 01","+ -1",\
		"-100","100", "+-42", "-+42", "--042",\
		"-","-01","-001","--1","-10","10", "+-42", "-+42", "--042",\
		"     -1","          -01","\t\n\v  404    01","\t\n\v--404",\
		" -1"," -01","-0\t\t01"," 01 ","\t 10-2","e 10",\
		"-23e", "-00000000004", "0.2", "2,4", "2.4",\
		"\f-2","\n-2","\r-2","\t-2","\v-2","42e",\
		"-123","123","-1","1", \
		"\t\v\f\r\n \f+\t\v\f\r\n \f1234","+\t\v\f\r\n \f1234", \
		int_min, int_max, NULL};
	i = 0;
	while (list[i])
	{
		nb_err+=compare(list[i]);
		i++;
	}

	return (nb_err);
}
