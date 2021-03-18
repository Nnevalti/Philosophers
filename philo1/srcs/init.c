#include "../includes/philo_one.h"

void	init_mutex_fork(t_philo *philo, int nb_philosopher)
{
	int		i;

	i = 0;
	while (i < nb_philosopher)
	{
		if (!(philo[i].left_fork = malloc(sizeof(pthread_mutex_t))))
			return ;
		pthread_mutex_init(philo[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philosopher)
	{
		philo[i].right_fork = philo[(i + 1) % nb_philosopher].left_fork;
		i++;
	}
}

void	init_stdout_mutex(t_philo *philo, int nb_philosopher)
{
	int					i;
	pthread_mutex_t		*stdout_mutex;

	i = 0;
	if (!(stdout_mutex = malloc(sizeof(pthread_mutex_t))))
		return ;
	pthread_mutex_init(stdout_mutex, NULL);
	while (i < nb_philosopher)
	{
		philo[i].stdout_mutex = stdout_mutex;
		i++;
	}
}

void	init_philo(t_philo *philo, int nb_philosopher)
{
	int		i;

	i = 0;
	init_mutex_fork(philo, nb_philosopher);
	init_stdout_mutex(philo, nb_philosopher);
	while (i < nb_philosopher)
	{
		philo[i].index = i + 1;
		philo[i].last_meal = 0;
		philo[i].nb_meal_eat = 0;
		philo[i].is_dead = FALSE;
		i++;
	}
}

int		init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (exit_error("Error: Bad arguments\n"));
	data->one_died = FALSE;
	data->nb_philosopher = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * MS_IN_US;
	data->time_to_eat = ft_atoi(av[3]) * MS_IN_US;
	data->time_to_sleep = ft_atoi(av[4]) * MS_IN_US;
	if (ac == 6)
		data->must_eat_nb_time = ft_atoi(av[5]);
	else
		data->must_eat_nb_time = 0;
	data->philo_ate_enough = 0;
	if (data->nb_philosopher < 2)
		return (exit_error("Error: Not enough philosophers\n"));
	return (0);
}
