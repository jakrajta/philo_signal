#include "philo.h"

static void	count_full_philos(t_philo *one_philo)
{
	pthread_mutex_lock(&one_philo->data->finished_lock);
	one_philo->data->full_philos++;
	pthread_mutex_unlock(&one_philo->data->finished_lock);
}

bool	philos_full(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->finished_lock);
	result = (data->full_philos == data->philos_nbr);
	pthread_mutex_unlock(&data->finished_lock);
	return (result);
}

static void	synchro_start(t_philo *one_philo)
{
	while (get_actual_time() < one_philo->data->start_time)
		usleep(10);
}

static void delay_philo(t_philo *one_philo)
{
	if (one_philo->data->philos_nbr % 2 == 0)
	{
		if (one_philo->id % 2 == 1)
			activity_pause(one_philo, one_philo->data->time_to_eat / 2);
	}
	else
		if (one_philo->id % 2 == 1)
			think(one_philo);
}

void	*routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	synchro_start(one_philo); 
	delay_philo(one_philo);
	// if(one_philo->id % 2 == 0)
	// 	usleep(1000);  //spis dat thinking
	while (!philo_dead(one_philo->data) && !philos_full(one_philo->data))
	{
		// if (one_philo->data->meals_nbr != -1 &&
		// 	one_philo->meals_eaten == one_philo->data->meals_nbr)
		// 	break;
		take_forks(one_philo);
		eat(one_philo);		
		return_forks(one_philo);
		if (one_philo->data->meals_nbr != -1)
		{
			one_philo->meals_eaten++;
			if (one_philo->meals_eaten == one_philo->data->meals_nbr)
			{
				count_full_philos(one_philo);	
			}
			if (philos_full(one_philo->data))
				break;
		}
		psleep(one_philo);
		think(one_philo);
	}
	return (NULL);
}

