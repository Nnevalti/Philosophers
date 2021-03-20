/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:17:34 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/20 15:17:35 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*philo_died_in_parent(void *philo_tmp)
{
	t_philo		*philo;

	philo = (t_philo *)philo_tmp;
	sem_wait(philo->sem->state_sem_parent);
	philo->data->state = DEAD;
	return (NULL);
}

void	*philo_died_in_child(void *philo_tmp)
{
	t_philo		*philo;

	philo = (t_philo *)philo_tmp;
	sem_wait(philo->sem->state_sem_child);
	philo->data->state = DEAD;
	philo->stop = TRUE;
	sem_post(philo->sem->state_sem_child);
	return (NULL);
}

void	*philo_eat_meal(void *philo_tmp)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)philo_tmp;
	data = philo->data;
	while (data->must_eat_nb_time && data->state != DEAD)
	{
		sem_wait(philo->sem->philo_full_sem);
		data->nb_philo_full++;
		if (data->nb_philo_full == data->nb_philosopher && data->state != DEAD)
		{
			data->full = TRUE;
			sem_post(philo->sem->state_sem_parent);
			break ;
		}
	}
	return (NULL);
}
