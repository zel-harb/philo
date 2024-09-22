/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:45 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/22 23:27:12 by zel-harb         ###   ########.fr       */
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

int	check_dead(t_data *data, int *full, int index)
{
	pthread_mutex_lock(&data->philo[index].check_counter);
	if (data->philo[index].counter == data->number_eat
		&& data->philo[index].check == 0)
	{
		data->philo[index].check = -1;
		(*full)++;
	}
	pthread_mutex_unlock(&data->philo[index].check_counter);
	if (check_philo_die(&data->philo[index]) < 0 || (*full) == data->num_philo)
	{
		pthread_mutex_lock(&data->died);
		data->dead = 1;
		pthread_mutex_unlock(&data->died);
		printf("%lu philosopher %d died \n", get_time() - data->start_time,
			data->philo[index].id_philo);
		return (1);
	}
	return (0);
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
			if (check_dead(data, &full, i) == 1)
				return (1);
			i++;
		}
	}
}
