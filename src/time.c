/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:14:14 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/18 19:14:42 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_actual_time(void)
{
	struct timeval	act_time;

	gettimeofday(&act_time, NULL);
	return (act_time.tv_sec * 1000L + act_time.tv_usec / 1000L);
}

void	activity_pause(t_philo *one_philo, long input_time)
{
	long	sleep_start;

	sleep_start = get_actual_time();
	while (get_actual_time() - sleep_start < input_time)
	{
		if (philo_dead(one_philo->data))
			break ;
		usleep(100);
	}
}
