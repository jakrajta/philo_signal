#include "philo.h"

bool	philo_dead(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->dead_lock);
	result = (data->philo_dead == 1);
	pthread_mutex_unlock(&data->dead_lock);
	return (result);
}



static void	set_philo_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->philo_dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (get_actual_time() < data->start_time)
		usleep(50);

	while (!philo_dead(data) && !philos_full(data))
	{
		i = -1;
		while (++i < data->philos_nbr)
		{
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if ((get_actual_time() - data->philos[i].last_meal_time) > data->time_to_die)
			{
				pthread_mutex_unlock(&data->philos[i].meal_lock);
				set_philo_dead(data);
				print_activity(&data->philos[i], DIE);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_lock);
		}
		usleep(50); // aby se CPU nevytizilo na 100 %
	}
	return (NULL);
}
