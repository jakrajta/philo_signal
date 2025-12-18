#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>

# define B		"\x1b[1m"
# define RED    "\x1b[31m"
# define GRE	"\x1b[90m"
# define GR 	"\x1b[34m"
# define CYA    "\x1b[36m"
# define R		"\x1b[0m"

typedef enum e_activity
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_activity;

typedef struct s_data
{
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nbr;
	int				philo_dead;
	long			start_time;
	int				full_philos;
	pthread_t		*p_ths;
	pthread_mutex_t	*forks_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	finished_lock;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}	t_philo;

void	activity_pause(t_philo *one_philo, long input_time);
void	clean_all(t_data *data);
void	destroy_mutexes(t_data *data);
void	display_error(char *msg);
void	eat(t_philo *one_philo);
long	get_actual_time(void);
int		handle_threads(t_data *data);
void	init_data(t_data *data, char **argv);
void	init_mutexes(t_data *data);
void	init_philos(t_data *data);
int		input_control(int argc, char **argv);
bool	is_digit(char c);
bool	is_whitespace(char c);
void	*monitor(void *arg);
int		my_atoi(char *str);
int		one_philo_case(t_data *data);
bool	philo_dead(t_data *data);
bool	philos_full(t_data *data);
void	print_activity(t_philo *one_philo, t_activity activity);
void	psleep(t_philo *one_philo);
void	return_forks(t_philo *one_philo);
void	*routine(void *arg);
void	take_forks(t_philo *one_philo);
void	think(t_philo *one_philo);

#endif