/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:11:10 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/26 13:00:51 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->died);
	return (0);
}

void	lock_unlock(pthread_mutex_t *p1, pthread_mutex_t *p2)
{
	pthread_mutex_unlock(p1);
	pthread_mutex_unlock(p2);
}

void	print_msg(t_philo *philo, char *str)
{
	printf("%lu %d %s\n", (get_time() - philo->data->start_time),
		philo->id_philo, str);
}

void	counter_increment(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_counter);
	philo->counter++;
	pthread_mutex_unlock(&philo->check_counter);
}
