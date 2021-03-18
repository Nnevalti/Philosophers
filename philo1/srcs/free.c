#include "../includes/philo_one.h"

void	free_philo(t_data *data, t_philo *philo, int nb_philosopher)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(philo[0].stdout_mutex);
	free(philo[i].stdout_mutex);
	while (i < nb_philosopher)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		free(philo[i].left_fork);
		i++;
	}
	free(philo);
	free(data);
}
