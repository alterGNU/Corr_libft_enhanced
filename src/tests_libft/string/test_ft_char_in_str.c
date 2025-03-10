#include "libft.h"  // ft_char_in_str()
#include <string.h> // strlen()
#include <stdio.h>  // printf

#define f_name "strlen"

int	compare_with_strlen(char *str)
{
	size_t	real;
	int	ft;

	real = strlen(str);
	ft = ft_char_in_str(0, str);
	printf("strlen(%s) = real[%ld] == [%d]ft_char_in_str(0,%s)",str ,real ,ft, str); 
	if ((!real && ft) || (real && !ft))
	{
		printf("----> FAIL!"); 
		printf("\tERROR : strlen(%s) = real[%ld] != [%d]ft\n",str ,real ,ft); 
		return (1);
	}
	printf("----> PASS!\n"); 
	return (0);
}

int	test(char c, char *str, int res)
{
	int	ft;

	ft = ft_char_in_str(c, str);
	printf("ft_char_in_str('%c',\"%s\")==[%d]vs[%d]",c, str ,res ,ft); 
	if ((!res && ft) || (res && !ft))
		return (printf("----> FAIL!"), 1); 
	return (printf("----> PASS!\n"), 0);
}

int	main()
{
	int	tot_fail=0;
	char *sn = NULL;
	tot_fail += test('a', sn, -1); // check when str is null
	tot_fail += test(0, sn, -1);   // check when str is null
	char s0[4] = {'\0','\0','\0','\0'} ;
	char s1[4] = {'\0','a','\0','\0'} ;
	char *list[7]={s0, s1, "", "\0",  "toto", "to\0to","\nle\tgras\tc'est\rla\tvie\nle GRAS\n"};
	// Check that when c is '\0', ft_char_in_str(0, str) behave like strlen(str)
	for(int i=0;i<7;i++)
		tot_fail += compare_with_strlen(list[i]);
	char *str="abc123";
	tot_fail += test('a', str, 0); // check when char in str
	tot_fail += test('b', str, 1); // check when char in str
	tot_fail += test('c', str, 2); // check when char in str
	tot_fail += test('1', str, 3); // check when char in str
	tot_fail += test('2', str, 4); // check when char in str
	tot_fail += test('3', str, 5); // check when char in str
	tot_fail += test('\0', str, 6);// check work like strlen()
	tot_fail += test('d', str, -1);// check when c not in str
	tot_fail += test('4', str, -1);// check when c not in str
	tot_fail += test('\0', list[2], 0); // check on empty string
	tot_fail += test('\0', s0, 0); // check on string with multiple '\0'
	tot_fail += test('a', s1, -1); // check that stop at '\0'
	return (tot_fail);
}

