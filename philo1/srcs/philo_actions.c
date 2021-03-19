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

#include "../includes/philo_one.h"

void	display_event(t_philo *philo, char *event)
{
	pthread_mutex_lock(&philo->stdout_mutex);
	if (philo->data->state != DEAD && !philo->stop)
		printf("%.4ldms: Philo N°%d %s !\n",
			get_time() - philo->data->start, philo->index, event);
	pthread_mutex_unlock(&philo->stdout_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	display_event(philo, TAKE_FORK);
	pthread_mutex_lock(philo->left_fork);
	display_event(philo, TAKE_FORK);
	philo->last_meal = get_time();
	display_event(philo, EATING);
	usleep(philo->data->time_to_eat * MS_IN_US);
	if (philo->data->must_eat_nb_time)
		philo->nb_meal_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
