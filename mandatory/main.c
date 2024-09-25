/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:49 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/25 01:26:58 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_stats_mutex);
		pthread_mutex_destroy(&data->philo[i].check_counter);
		i++;
	}
	pthread_mutex_destroy(&data->died);
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->print_eat);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_arg(ac, av))
		return (1);
	init_threads(&data, ac, av);
	init_forks(&data);
	get_forks(&data);
	data.start_time = get_time();
	creat_threads(&data);
	monitor(&data);
	join_threads(&data);
	ft_destroy_mutex(&data);
	free(data.forks);
	free(data.philo);
	return (0);
}
