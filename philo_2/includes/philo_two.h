/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:03:13 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:03:14 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>


# define FALSE 0
# define TRUE 1

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEATH "is dead"
# define MS_IN_US 1000
# define S_IN_US 1000000

typedef enum		e_state
{
	ALIVE,
	DEAD,
}					t_state;


typedef struct		s_data
{
	int				nb_philosopher;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				must_eat_nb_time;
	long			start;
	t_state			state;
	int				nb_philo_full;
}					t_data;

typedef struct		s_sem
{
	sem_t			*forks_sem;
	sem_t			*state_sem;
	sem_t			*stdout_sem;
}					t_sem;

typedef struct		s_philo
{
	t_data			*data;
	pthread_t		thread;
	t_sem			*sem;
	int				index;
	long			last_meal;
	int				nb_meal_eat;
	int				stop;

}					t_philo;

/*
**		INIT.C
*/
int					init_sem(t_sem *sem, int nb_p);
t_philo				*init_philo(t_data *data, t_sem *sem);
int					init_data(t_data *data, int ac, char **av);

/*
**		PHILO_ACTIONS.C
*/
void				display_event(t_philo *philo, char *event);
void				philo_eat(t_philo *philo);
/*
**		EXIT.C
*/
int					exit_error(char *str);

/*
**		UTILS.C
*/
long				get_time();
int					ft_isdigit(char c);
int					ft_strlen(char *str);
long				ft_atoi(const char *str);

#endif
