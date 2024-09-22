/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:59:34 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/22 23:28:10 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->num_philo = ft_atoi(av[1]);
	data->dead = 0;
	data->full = 0;
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
		data->philo[i].dead = &data->dead;
		data->philo[i].data = data;
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].meal_stats_mutex, NULL);
		pthread_mutex_init(&data->philo[i].check_counter, NULL);
		i++;
	}
	pthread_mutex_init(&data->died, NULL);
	pthread_mutex_init(&data->full_mutex, NULL);
	pthread_mutex_init(&data->print_eat, NULL);
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

void	creat_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_ate_mutex);
		data->philo[i].last_time_eat = get_time();
		pthread_mutex_unlock(&data->philo[i].last_ate_mutex);
		pthread_create(&data->philo[i].thread, NULL, &routin, &data->philo[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return ;
}
