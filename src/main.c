/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:08:53 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/21 16:30:18 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Atomic sig_atomic_t stop = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	stop = 1;
}

void	clean_all(t_data *data)
{
	destroy_mutexes(data);
	free(data->p_ths);
	free(data->forks_locks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (input_control(argc, argv) == -1)
		return (1);
	init_data(&data, argv);
	init_philos(&data);
	init_mutexes(&data);
	signal(SIGINT, handle_sigint);
	if (data.philos_nbr == 1)
	{
		one_philo_case(&data);
		return (0);
	}
	if (!handle_threads(&data))
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
