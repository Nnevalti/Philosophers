/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:00:35 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:00:36 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		init_semaphore_fork(t_philo *philo, int nb_philosopher)
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

t_philo		*init_philo(t_data *data)
{
	t_philo				*philo;
	pthread_mutex_t		stdout_mutex;
	pthread_mutex_t		state_mutex;
	int					i;

	if (!(philo = malloc(sizeof(t_philo) * data->nb_philosopher)))
		return (NULL);
	i = 0;
	init_mutex_fork(philo, data->nb_philosopher);
	pthread_mutex_init(&stdout_mutex, NULL);
	pthread_mutex_init(&state_mutex, NULL);
	while (i < data->nb_philosopher)
	{
		philo[i].data = data;
		philo[i].state_mutex = state_mutex;
		philo[i].stdout_mutex = stdout_mutex;
		philo[i].index = i + 1;
		philo[i].last_meal = get_time();
		philo[i].nb_meal_eat = 0;
		i++;
	}
	return (philo);
}

int			check_isnum(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int			check_args(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (check_isnum(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int			init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (exit_error("Error: Wrong number of arguments\n"));
	if (check_args(av))
		return (exit_error("Error: Non numeric value in arguments!\n"));
	data->state = ALIVE;
	data->nb_philosopher = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_nb_time = ft_atoi(av[5]);
	else
		data->must_eat_nb_time = 0;
	data->nb_philo_full = 0;
	if (data->nb_philosopher < 2)
		return (exit_error("Error: There should be at least 2 philosophers\n"));
	return (0);
}
