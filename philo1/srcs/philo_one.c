#include "../includes/philo_one.h"

int		main(int ac, char **av)
{
	(void)av;
	if (ac < 5 || ac > 6)
	{
		printf("not ok\n");
		return (1);
	}
	printf("ok\n");
	return (0);
}
