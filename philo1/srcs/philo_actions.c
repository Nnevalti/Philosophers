#include "../includes/philo_one.h"

void	display_event(t_data *data, t_philo *philo, char *event)
{
	pthread_mutex_lock(philo->stdout_mutex);
	printf("%.3u.%.3u: Philo N°%d %s !\n",  (get_time_sec() - data->start_sec), get_time_usec()/1000, philo->index, event);
	pthread_mutex_unlock(philo->stdout_mutex);
}

void	philo_take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_event(data, philo, TAKE_FORK);
	pthread_mutex_lock(philo->right_fork);
	display_event(data, philo, TAKE_FORK);
}

void	philo_eat(t_data *data, t_philo *philo)
{
	display_event(data, philo, EATING);
	// philo.last_meal = get_time(data->start);
	usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	display_event(data, philo, SLEEPING);
	usleep(data->time_to_sleep);
}

void	philo_think(t_data *data, t_philo *philo)
{
	display_event(data, philo, THINKING);
}
