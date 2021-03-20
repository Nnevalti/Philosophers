/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:00:49 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:00:49 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*death_check(void *philo_tmp)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)philo_tmp;
	data = philo->data;
	while (data->state != DEAD && !philo->stop)
	{
		if ((get_time() - philo->last_meal) > data->time_to_die)
		{
			display_event(philo, DEATH);
			data->state = DEAD;
			philo->stop = TRUE;
			sem_post(philo->sem->state_sem_parent);
			sem_post(philo->sem->state_sem_child);
			sem_post(philo->sem->philo_full_sem);
			break ;
		}
	}
	return (NULL);
}

void	*philosophers(t_data *data, t_philo *philo)
{
	pthread_t	death;
	pthread_t	state;

	pthread_create(&death, NULL, &death_check, philo);
	pthread_detach(death);
	pthread_create(&state, NULL, &philo_died_in_child, philo);
	pthread_detach(state);
	while (data->state != DEAD && philo->stop == FALSE)
	{
		philo_eat(philo);
		if (data->must_eat_nb_time
			&& philo->nb_meal_eat == data->must_eat_nb_time)
			philo->stop = TRUE;
		display_event(philo, SLEEPING);
		usleep(data->time_to_sleep * MS_IN_US);
		display_event(philo, THINKING);
	}
	if (data->must_eat_nb_time
		&& philo->nb_meal_eat == data->must_eat_nb_time)
		sem_post(philo->sem->philo_full_sem);
	return (NULL);
}

void	start_philosophers(t_data *data, t_philo *philo)
{
	pthread_t	philo_died;
	pthread_t	philo_full;
	int			i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philosopher)
	{
		if ((philo->pid[i] = fork()) == -1)
			return ;
		if (philo->pid[i++] == 0)
		{
			philo->index = i;
			philosophers(data, philo);
			exit(0);
		}
	}
	pthread_create(&philo_full, NULL, &philo_eat_meal, philo);
	pthread_create(&philo_died, NULL, &philo_died_in_parent, philo);
	pthread_join(philo_full, NULL);
	pthread_join(philo_died, NULL);
	wait_for_process(data, philo);
}

void	end_philosophers(t_philo *philo, t_sem *sem)
{
	sem_unlink("state_parent");
	sem_unlink("state_child");
	sem_unlink("philo_full");
	sem_unlink("forks");
	sem_unlink("stdout");
	sem_close(sem->state_sem_child);
	sem_close(sem->state_sem_parent);
	sem_close(sem->philo_full_sem);
	sem_close(sem->forks_sem);
	sem_close(sem->stdout_sem);
	free(philo->pid);
}

int		main(int ac, char **av)
{
	t_data	data;
	t_sem	sem;
	t_philo	philo;

	if (init_data(&data, ac, av))
		return (1);
	if (init_sem(&sem, data.nb_philosopher))
		return (exit_error("Error: init semaphore failed"));
	init_philo(&data, &sem, &philo);
	start_philosophers(&data, &philo);
	end_philosophers(&philo, &sem);
	if (data.full == TRUE)
		printf("End of simulation: Philosophers are full !\n");
	else if (data.state == DEAD)
		printf("End of simulation: one of the philosophers died.\n");
	return (0);
}
