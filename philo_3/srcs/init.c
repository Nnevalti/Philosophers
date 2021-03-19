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

int			init_sem(t_sem *sem, int nb_p)
{
	sem_unlink("forks");
	sem_unlink("state");
	sem_unlink("stdout");
	if ((sem->forks_sem = sem_open("forks", O_CREAT, 0644, nb_p)) == SEM_FAILED)
		return (1);
	if ((sem->state_sem = sem_open("state", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	if ((sem->stdout_sem = sem_open("stdout", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	return (0);
}

void		init_philo(t_data *data, t_sem *sem, t_philo *philo)
{
	if (!(philo->pid = malloc(sizeof(pid_t) * data->nb_philosopher)))
		return ;
	philo->data = data;
	philo->sem = sem;
	philo->last_meal = get_time();
	philo->nb_meal_eat = 0;
	philo->stop = FALSE;
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
