/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:00:49 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:00:49 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
			sem_wait(philo->sem->state_sem);
			data->state = DEAD;
			philo->stop = TRUE;
			sem_post(philo->sem->state_sem);
			break ;
		}
	}
	return (NULL);
}

void	*philosophers(void *philo_tmp)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	death;

	philo = (t_philo *)philo_tmp;
	data = philo->data;
	pthread_create(&death, NULL, &death_check, philo);
	pthread_detach(death);
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
		data->nb_philo_full++;
	return (NULL);
}

void	start_philosophers(t_data *data, t_philo *philo)
{
	int			i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philosopher)
	{
		pthread_create(&philo[i].thread, NULL, &philosophers, &philo[i]);
		usleep(10);
		i++;
	}
	i = 0;
	while (i < data->nb_philosopher)
		pthread_join(philo[i++].thread, NULL);
}

void	end_philosophers(t_philo *philo, t_sem *sem)
{
	sem_unlink("forks");
	sem_unlink("forks_protect");
	sem_unlink("state");
	sem_unlink("stdout");
	sem_close(sem->forks_sem);
	sem_close(sem->forks_protect_sem);
	sem_close(sem->state_sem);
	sem_close(sem->stdout_sem);
	free(philo);
}

int		main(int ac, char **av)
{
	t_data	data;
	t_sem	sem;
	t_philo	*philo;

	if (init_data(&data, ac, av))
		return (1);
	if (init_sem(&sem, data.nb_philosopher))
		return (exit_error("Error: init semaphore failed"));
	philo = init_philo(&data, &sem);
	start_philosophers(&data, philo);
	end_philosophers(philo, &sem);
	if (data.state == DEAD)
		printf("End of simulation: one of the philosophers died.\n");
	else if (data.must_eat_nb_time
		&& data.nb_philo_full == data.nb_philosopher)
		printf("End of simulation: Philosophers are full !\n");
	return (0);
}
