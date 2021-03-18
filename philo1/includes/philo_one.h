#ifndef PHILO_ONE
# define PHILO_ONE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEATH "is dead"
# define MS_IN_US 1000
# define S_IN_US 1000000

typedef enum			e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct			s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*stdout_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					index;
	int					last_meal;
	int					nb_meal_eat;
	t_bool				is_dead;

}						t_philo;

typedef struct			s_data
{
	t_bool				one_died;
	int					nb_philosopher;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					must_eat_nb_time;
	int					philo_ate_enough;
	unsigned int		start_sec;
	unsigned int		start_usec;
	struct timeval		start;
}						t_data;

typedef struct			s_stock
{
	t_data				*data;
	t_philo				*philo;
}						t_stock;

#endif

/*
**		INIT.C
*/
int						init_data(t_data *data, int ac, char **av);
void					init_philo(t_philo *philo, int nb_philosopher);

/*
**		PHILO_ACTIONS.C
*/
void					philo_take_fork(t_data *data, t_philo *philo);
void					philo_eat(t_data *data, t_philo *philo);
void					philo_sleep(t_data *data, t_philo *philo);
void					philo_think(t_data *data, t_philo *philo);
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
unsigned int			get_time(unsigned int start_sec, unsigned start_usec);
unsigned int			get_time_sec(void);
unsigned int			get_time_usec(void);
int						ft_strlen(char *str);
long					ft_atoi(const char *str);
