/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:12:21 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/18 19:12:23 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_activity(t_philo *one_philo, t_activity activity)
{
	long	tstamp;

	if (philos_full(one_philo->data))
		return ;
	pthread_mutex_lock(&one_philo->data->print_lock);
	tstamp = get_actual_time() - one_philo->data->start_time;
	if (philo_dead(one_philo->data) && activity != DIE)
	{
		pthread_mutex_unlock(&one_philo->data->print_lock);
		return ;
	}
	if (activity == TAKE_FORK)
		printf(B GRE "%ld %d has taken a fork\n" R, tstamp, one_philo->id);
	else if (activity == EAT)
		printf(B MAG "%ld %d is eating\n" R, tstamp, one_philo->id);
	else if (activity == SLEEP)
		printf(B GR "%ld %d is sleeping\n" R, tstamp, one_philo->id);
	else if (activity == THINK)
		printf(B CYA "%ld %d is thinking\n" R, tstamp, one_philo->id);
	else if (activity == DIE)
		printf(B RED "%ld %d died\n" R, tstamp, one_philo->id);
	pthread_mutex_unlock(&one_philo->data->print_lock);
}

void	display_error(char *msg)
{
	printf("%s\n", msg);
}
