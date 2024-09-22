/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:18:22 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/23 00:10:46 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	if (end_simulation(philo) == 1)
		return (0);
	pthread_mutex_lock(philo->r_fork);
	if (end_simulation(philo) == 1)
		return (pthread_mutex_unlock(philo->r_fork), 0);
	print_msg(philo, "has taken a fork");
	if (end_simulation(philo) == 1)
		return (pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_lock(philo->l_fork);
	if (end_simulation(philo) == 1)
		return (lock_unlock(philo->r_fork, philo->l_fork), 0);
	print_msg(philo, "has taken a fork");
	if (end_simulation(philo) == 1)
		return (lock_unlock(philo->r_fork, philo->l_fork), 0);
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->meal_stats_mutex);
	if (philo->data->number_eat != -1)
		counter_increment(philo);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->meal_stats_mutex);
	ft_usleep(philo->time_eat);
	lock_unlock(philo->r_fork, philo->l_fork);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (end_simulation(philo) == 1)
		return (0);
	printf("%lu philosopher %d is sleeping\n", get_time()
		- (philo->data->start_time), philo->id_philo);
	ft_usleep(philo->time_sleep);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (end_simulation(philo) == 1)
		return (0);
	printf("%lu philosopher %d is thinking\n", get_time()
		- philo->data->start_time, philo->id_philo);
	return (1);
}

void	*routin(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id_philo % 2 == 0)
		ft_usleep(philo->time_eat / 2);
	while (1)
	{
		if (eating(philo) == 0)
			return (NULL);
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
		ft_usleep((philo->time_die - (get_time() - philo->last_time_eat)) / 2);
	}
	return (NULL);
}
