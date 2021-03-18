#include "../includes/philo_one.h"

unsigned int	get_time(unsigned int start_sec, unsigned start_usec)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start_sec * S_IN_US) + (now.tv_usec - start_usec));
}

unsigned int	get_time_sec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec);
}

unsigned int	get_time_usec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_usec);
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
