#include "../include/philo_one.h"

long			ft_nblen(long nb)
{
	int		len;

	len = nb <= 0 ? 1 : 0;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(long nb)
{
	int				sign;
	int				len;
	char			*str;

	sign = (nb < 0 ? 1 : 0);
	len = ft_nblen(nb);
	if (sign == 1)
	nb = -nb;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
	return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (sign == 1)
	str[0] = '-';
	return (str);
}

long		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	value;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	value = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
