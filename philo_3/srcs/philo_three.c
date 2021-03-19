/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
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
	printf("%lu > %u\n",
		get_time() - philo->last_meal, data->time_to_die);
	while (42 && data->state != DEAD
		&& (!philo->nb_meal_eat
			|| philo->nb_meal_eat < data->must_eat_nb_time))
	{
		if ((get_time() - philo->last_meal) > data->time_to_die)
		{
			display_event(philo, DEATH);
			pthread_mutex_lock(&philo->state_mutex);
			data->state = DEAD;
			pthread_mutex_unlock(&philo->state_mutex);
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
	philo->index % 2 ? 0 : usleep(data->time_to_eat * MS_IN_US);
	while (42 && data->state != DEAD
		&& (!philo->nb_meal_eat
			|| philo->nb_meal_eat < data->must_eat_nb_time))
	{
		philo_eat(philo);
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

void	end_philosophers(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&philo[0].stdout_mutex);
	pthread_mutex_destroy(&philo[0].state_mutex);
	while (i < data->nb_philosopher)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		free(philo[i].left_fork);
		i++;
	}
	free(philo);
}

int		main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (init_data(&data, ac, av))
		return (1);
	philo = init_philo(&data);
	start_philosophers(&data, philo);
	end_philosophers(&data, philo);
	if (data.state == DEAD)
		printf("End of simulation: one of the philosophers died.\n");
	else if (data.nb_philo_full
		&& data.nb_philo_full == data.must_eat_nb_time)
		printf("End of simulation: Philosophers are full !\n");
	return (0);
}
