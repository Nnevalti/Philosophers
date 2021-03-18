#ifndef PHILO_ONE
# define PHILO_ONE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
	int			nb_philosopher;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_time_each_philo_must_eat;
}				t_philo;

#endif


/*
**		UTILS.C
*/
int				ft_strlen(char *str);
long			ft_atoi(const char *str);