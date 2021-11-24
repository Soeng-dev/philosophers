static int	is_longint_overflow(const char *str, size_t numlen)
{
	char	*longint_max;

	longint_max = "9223372036854775807\0";
	if (numlen < ft_strlen(longint_max))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (*str > *longint_max)
			return (1);
		longint_max++;
		str++;
	}
	return (0);
}

static int	is_longint_underflow(const char *str, size_t numlen)
{
	char	*longint_min;

	longint_min = "9223372036854775808\0";
	if (numlen < ft_strlen(longint_min))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (*str > *longint_min)
			return (1);
		longint_min++;
		str++;
	}
	return (0);
}

int			ft_atoi(const char *str)
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
	if (sign > 0)
	{
		if (is_longint_overflow(str, numlen))
			return (-1);
	}
	else if (sign < 0)
		if (is_longint_underflow(str, numlen))
			return (0);
	return (sign * ret);
}