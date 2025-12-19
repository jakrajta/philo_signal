/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:11:57 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/18 19:11:59 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->data->start_time = get_actual_time();
	print_activity(philo, TAKE_FORK);
	activity_pause(philo, philo->data->time_to_sleep);
	print_activity(philo, DIE);
	return (NULL);
}

int	one_philo_case(t_data *data)
{
	if (pthread_create(&data->p_ths[0], NULL, single_philo, &data->philos[0]))
		return (display_error("Failed to create routine single thread"), -1);
	if (pthread_join(data->p_ths[0], NULL))
		return (display_error("Failed to join single thread"), -1);
	clean_all(data);
	return (0);
}
