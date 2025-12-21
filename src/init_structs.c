/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:07:42 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/20 20:51:26 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **argv)
{
	data->philos_nbr = my_atoi(argv[1]);
	data->time_to_die = my_atoi(argv[2]);
	data->time_to_eat = my_atoi(argv[3]);
	data->time_to_sleep = my_atoi(argv[4]);
	if (argv[5])
		data->meals_nbr = my_atoi(argv[5]);
	else
		data->meals_nbr = -1;
	data->philo_dead = 0;
	data->full_philos = 0;
	data->start_time = get_actual_time();
	data->p_ths = malloc(sizeof(pthread_t) * data->philos_nbr);
	if (data->p_ths == NULL)
		return (display_error("Failed to malloc p_thread"));
	data->forks_locks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (data->forks_locks == NULL)
		return (display_error("Failed to malloc fork mutex array"));
}

void	init_philos(t_data *data)
{
	int		i;
	t_philo	*one_p;

	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (data->philos == NULL)
		return (display_error("Failed to malloc philos"));
	i = -1;
	while (++i < data->philos_nbr)
	{
		one_p = &data->philos[i];
		one_p->id = i + 1;
		one_p->last_meal_time = data->start_time;
		one_p->meals_eaten = 0;
		one_p->right_fork = &data->forks_locks[i];
		one_p->left_fork = &data->forks_locks[(i + 1) % data->philos_nbr];
		one_p->data = data;
	}
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL))
			return (display_error("Failed to create last meal mutex"));
		if (pthread_mutex_init(&data->forks_locks[i], NULL))
			return (display_error("Failed to create fork mutex"));
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (display_error("Failed to create print mutex"));
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (display_error("Failed to create dead mutex"));
	if (pthread_mutex_init(&data->finished_lock, NULL))
		return (display_error("Failed to create finished mutex"));
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		pthread_mutex_destroy(&data->forks_locks[i]);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->finished_lock);
}


