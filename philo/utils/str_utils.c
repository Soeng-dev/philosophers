#include "utils.h"

int ft_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2)
        return 0;
    while (*s1)
    {
        if (*s1 != *s2)
            break;
        ++s1;
        ++s2;
    }
    return (*s1 - *s2);
}

int compare_strnum(char *strnum1, char *sign, char *strnum2)
{
    int n1;
    int n2;

    if (!sign)
        return ERROR;

    n1 = ft_atoi(strnum1);
    n2 = ft_atoi(strnum2);
    
    if (!ft_strcmp(sign, ">"))
        return (n1 > n2);
    else if (!ft_strcmp(sign, "<"))
        return (n1 < n2);
    else if (!ft_strcmp(sign, ">="))
        return (n1 >= n2);
    else if (!ft_strcmp(sign, "<="))
        return (n1 <= n2);
    else
        return ERROR;
}

int ft_strlen(char *str)
{
	int length;

	length = 0;
	while (str[length])
		++length;
	return length;
}

int ft_atoi(const char *str)
{
	int		ret;
	int		sign;
	int		numlen;

	ret = 0;
	numlen = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-') ? (-1) : (1);
		str++;
	}
	while (str[numlen] >= '0' && str[numlen] <= '9')
		ret = 10 * ret + ((int)(str[numlen++]) - '0');
	return (sign * ret);
}
