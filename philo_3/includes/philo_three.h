/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:03:13 by vdescham          #+#    #+#             */
/*   Updated: 2021/03/19 15:03:14 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	int				full;
}					t_data;

typedef struct		s_sem
{
	sem_t			*forks_sem;
	sem_t			*forks_protect_sem;
	sem_t			*philo_full_sem;
	sem_t			*state_sem_parent;
	sem_t			*state_sem_child;
	sem_t			*stdout_sem;
}					t_sem;

typedef struct		s_philo
{
	t_data			*data;
	t_sem			*sem;
	pid_t			*pid;
	int				index;
	long			last_meal;
	int				nb_meal_eat;
	int				stop;

}					t_philo;

/*
**		INIT.C
*/
int					init_sem(t_sem *sem, int nb_p);
void				init_philo(t_data *data, t_sem *sem, t_philo *philo);
int					init_data(t_data *data, int ac, char **av);

/*
**		PHILO_ACTIONS.C
*/
void				display_event(t_philo *philo, char *event);
void				philo_eat(t_philo *philo);

/*
**		MONITOR.C
*/
void				*philo_died_in_parent(void *philo_tmp);
void				*philo_died_in_child(void *philo_tmp);
void				*philo_eat_meal(void *philo_tmp);
/*
**		EXIT.C
*/
void				wait_for_process(t_data *data, t_philo *philo);
int					exit_error(char *str);

/*
**		UTILS.C
*/
long				get_time();
int					ft_isdigit(char c);
int					ft_strlen(char *str);
long				ft_atoi(const char *str);

#endif
