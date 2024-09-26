/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:59:34 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/26 06:34:43 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->num_philo = ft_atoi(av[1]);
	data->dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	data->number_eat = -1;
	while (i < data->num_philo)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].counter = 0;
		data->philo[i].check = 0;
		data->philo[i].time_die = ft_atoi(av[2]);
		data->philo[i].time_eat = ft_atoi(av[3]);
		data->philo[i].time_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->number_eat = ft_atoi(av[5]);
		data->philo[i].counter = 0;
		data->philo[i].data = data;
		i++;
	}
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		if (pthread_mutex_init(&data->philo[i].meal_stats_mutex, NULL))
			return (1);
		if (pthread_mutex_init(&data->philo[i].check_counter, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->died, NULL))
		return (1);
	if (pthread_mutex_init(&data->full_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_eat, NULL))
		return (1);
	return (0);
}

void	get_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (i == data->num_philo - 1)
		{
			data->philo[i].l_fork = &data->forks[i];
			data->philo[i].r_fork = &data->forks[0];
		}
		else
		{
			data->philo[i].r_fork = &data->forks[i];
			data->philo[i].l_fork = &data->forks[i + 1];
		}
		i++;
	}
}

int	creat_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].last_time_eat = get_time();
		if (pthread_create(&data->philo[i].thread, NULL, &routin,
				&data->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
