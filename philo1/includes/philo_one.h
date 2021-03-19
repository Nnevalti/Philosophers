/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:03:13 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:03:14 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define FALSE 0
# define TRUE 1

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEATH "is dead"
# define MS_IN_US 1000
# define S_IN_US 1000000

typedef enum			e_state
{
	ALIVE,
	DEAD,
}						t_state;

typedef struct			s_data
{
	int					nb_philosopher;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					must_eat_nb_time;
	long				start;
	t_state				state;
	int					nb_philo_full;
}						t_data;

typedef struct			s_philo
{
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		state_mutex;
	pthread_mutex_t		stdout_mutex;
	int					index;
	long				last_meal;
	int					nb_meal_eat;
	int					stop;

}						t_philo;

#endif

/*
**		INIT.C
*/
t_philo					*init_philo(t_data *data);
int						init_data(t_data *data, int ac, char **av);

/*
**		PHILO_ACTIONS.C
*/
void					display_event(t_philo *philo, char *event);
void					philo_eat(t_philo *philo);

/*
**		FREE.C
*/
void					free_philo(t_data *data, t_philo *philo, int nb_philosopher);
/*
**		EXIT.C
*/
int						exit_error(char *str);

/*
**		UTILS.C
*/
long					get_time();
int						ft_isdigit(char c);
int						ft_strlen(char *str);
long					ft_atoi(const char *str);
