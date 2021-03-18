#include "../includes/philo_one.h"

void	*philosophers(void *stock)
{
	t_data		*data;
	t_philo		*philo;

	data = ((t_stock *)stock)->data;
	philo = ((t_stock *)stock)->philo;
	while (!data->one_died && (!data->must_eat_nb_time || philo->nb_meal_eat < data->must_eat_nb_time))
	{
		philo_take_fork(data, philo);
		philo_eat(data, philo);
		philo_sleep(data, philo);
		philo_think(data, philo);
		philo->nb_meal_eat++;
	}
	if (data->must_eat_nb_time && philo->nb_meal_eat == data->must_eat_nb_time)
		data->philo_ate_enough++;
	return (NULL);
}

void	start_philosophers(t_data *data, t_philo *philo, t_stock *stock)
{
	int			i;

	i = 0;
	data->start_sec = get_time_sec();
	data->start_usec = get_time_usec();
	while (i < data->nb_philosopher)
	{
		stock[i].data = data;
		stock[i].philo = &philo[i];
		pthread_create(&philo[i].thread, NULL, &philosophers, &stock[i]);
		usleep(10);
		i++;
	}
}
void	wait_thread_to_end(t_philo *philo, int nb_philosopher)
{
	int		i;

	i = 0;
	while (i < nb_philosopher)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	t_stock	*stock;

	if (!(data = malloc(sizeof(t_data))))
		return (1);
	if (init_data(data, ac, av))
		return (exit_error("Error: Initialisation fatal error\n"));
	if (!(philo = malloc(sizeof(t_philo) * data->nb_philosopher)))
		return (1);
	init_philo(philo, data->nb_philosopher);
	if (!(stock = malloc(sizeof(t_stock) * data->nb_philosopher)))
		return (1);
	start_philosophers(data, philo, stock);
	wait_thread_to_end(philo, data->nb_philosopher);
	if (data->philo_ate_enough == data->nb_philosopher)
		printf("End: All philosophers ate enough\n");
	free_philo(data, philo, data->nb_philosopher);
	free(stock);
	return (0);
}
