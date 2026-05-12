#include "philo.h"

void	take_forks(t_philo *one_philo)
{
	if (philo_dead(one_philo->data) || stop)
		return ;
	if (one_philo->id % 2 == 0)
	{
		pthread_mutex_lock(one_philo->right_fork);
		print_activity(one_philo, TAKE_FORK);
		pthread_mutex_lock(one_philo->left_fork);
		print_activity(one_philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(one_philo->left_fork);
		print_activity(one_philo, TAKE_FORK);
		pthread_mutex_lock(one_philo->right_fork);
		print_activity(one_philo, TAKE_FORK);
	}
}

void	return_forks(t_philo *one_philo)
{
	pthread_mutex_unlock(one_philo->left_fork);
	pthread_mutex_unlock(one_philo->right_fork);
}

void	eat(t_philo *one_philo)
{
	if (philo_dead(one_philo->data))
		return ;
	pthread_mutex_lock(&one_philo->meal_lock);
	one_philo->last_meal_time = get_actual_time();
	pthread_mutex_unlock(&one_philo->meal_lock);
	print_activity(one_philo, EAT);
	activity_pause(one_philo, one_philo->data->time_to_eat);
}

void	psleep(t_philo *one_philo)
{
	if (philo_dead(one_philo->data) || stop)
		return ;
	print_activity(one_philo, SLEEP);
	activity_pause(one_philo, one_philo->data->time_to_sleep);
}

void	think(t_philo *one_philo)
{
	long	think_time;

	if (philo_dead(one_philo->data) || stop)
		return ;
	print_activity(one_philo, THINK);
	if (one_philo->data->philos_nbr % 2 == 0)
		return ;
	think_time = (one_philo->data->time_to_eat * 2)
		- one_philo->data->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	activity_pause(one_philo, (think_time * 0.3));
}
