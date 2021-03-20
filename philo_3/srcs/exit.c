/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:00:29 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:00:31 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	wait_for_process(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < data->nb_philosopher)
	{
		waitpid(philo->pid[i], NULL, 0);
		i++;
	}
}

int		exit_error(char *str)
{
	printf("%s\n", str);
	return (1);
}
