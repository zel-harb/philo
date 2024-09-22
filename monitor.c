/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:45 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/21 04:56:19 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_die(t_philo *philo)
{
	size_t	time_to_die;
	size_t	last_ate;

	pthread_mutex_lock(&philo->meal_stats_mutex);
	time_to_die = philo->time_die;
	last_ate = get_time() - philo->last_time_eat;
	pthread_mutex_unlock(&philo->meal_stats_mutex);
	return (time_to_die - last_ate);
}

int	monitor(t_data *data)
{
	int	i;
	int	full;

	full = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->philo[i].check_counter);
			if (data->philo[i].counter == data->number_eat
				&& data->philo[i].check == 0)
			{
				data->philo[i].check = -1;
				full++;
			}
			pthread_mutex_unlock(&data->philo[i].check_counter);
			if (check_philo_die(&data->philo[i]) < 0 || full == data->num_philo)
			{
				pthread_mutex_lock(&data->died);
				data->dead = 1;
				pthread_mutex_unlock(&data->died);
				printf("%lu philosopher %d died \n", get_time()
					- data->start_time, data->philo[i].id_philo);
				return (1);
			}
			i++;
		}
	}
}
