#include "philo.h"

int	handle_threads(t_data	*data)
{
	pthread_t	p_monitor;
	int			i;

	data->start_time = get_actual_time() + 50;  // dam buffer, aby se vsechna vlakna stacila pripravit
	i = -1;
	while (++i < data->philos_nbr)
	{
		if (pthread_create(&data->p_ths[i], NULL, routine, &data->philos[i]))
			return (display_error("Failed to create routine thread"), -1);
	}
	if (pthread_create(&p_monitor, NULL, monitor, data))
		return (display_error("Failed to create monitor thread"), -1);
	// natavit ze vscechny threads jsour ready. pak v routin pred spustenim jidla nastavit actual time
	i = -1;
	while (++i < data->philos_nbr)
	{
		if (pthread_join(data->p_ths[i], NULL))
			return (display_error("Failed to join thread"), -1);
	}
	if (pthread_join(p_monitor, NULL))
		return (display_error("Failed to join thread"), -1);
	return (0);
}
