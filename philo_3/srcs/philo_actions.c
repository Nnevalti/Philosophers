/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:00:42 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:00:43 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	display_event(t_philo *philo, char *event)
{
	sem_wait(philo->sem->stdout_sem);
	if (philo->data->state != DEAD && !philo->stop)
		printf("%.4ldms: Philo N°%d %s !\n",
			get_time() - philo->data->start, philo->index, event);
	sem_post(philo->sem->stdout_sem);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem->forks_protect_sem);
	sem_wait(philo->sem->forks_sem);
	display_event(philo, TAKE_FORK);
	sem_wait(philo->sem->forks_sem);
	display_event(philo, TAKE_FORK);
	philo->last_meal = get_time();
	display_event(philo, EATING);
	usleep(philo->data->time_to_eat * MS_IN_US);
	if (philo->data->must_eat_nb_time)
		philo->nb_meal_eat++;
	sem_post(philo->sem->forks_sem);
	sem_post(philo->sem->forks_sem);
	sem_post(philo->sem->forks_protect_sem);
}
