/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:18:22 by zel-harb          #+#    #+#             */
/*   Updated: 2024/08/04 01:28:35 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time()
{
    struct timeval time;
    size_t milliseconds;
     
    if (gettimeofday(&time, NULL) != 0) {
        printf("Error\n");
        return 0;
    }
    milliseconds = (size_t)((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
    return milliseconds;
}
void ft_usleep(size_t milliseconds)
{
    size_t start;
    
    start = get_time();
    while ((get_time() - start) < milliseconds)
		usleep(500);
}

int end_simulation(t_philo *philo)
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

int  eating(t_philo *philo)
{
    if (end_simulation(philo) == 1)
        return (0);
    pthread_mutex_lock(philo->r_fork);
    if (end_simulation(philo) == 1)
    {
        pthread_mutex_unlock(philo->r_fork);
        return 0;
    }
    printf("%lu philosopher %d has taken a fork\n",(get_time()-philo->data->start_time),philo->id_philo);
    if (end_simulation(philo) == 1)
    {
        pthread_mutex_unlock(philo->r_fork);
        return 0;
    }
    pthread_mutex_lock(philo->l_fork);
    if (end_simulation(philo) == 1)
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return 0;
    }
    printf("%lu philosopher %d has taken a fork\n",get_time()-(philo->data->start_time),philo->id_philo);
    if (end_simulation(philo) == 1)
    {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        return 0;
    }
    printf("%lu philosopher %d is eating\n",get_time()-(philo->data->start_time),philo->id_philo);
    pthread_mutex_lock(&philo->meal_stats_mutex);
    // printf("******%d \n");
    if(philo->data->number_eat != -1)
    {
        pthread_mutex_lock(&philo->check_counter);
        philo->counter++;
        pthread_mutex_unlock(&philo->check_counter);
    }
    philo->last_time_eat = get_time();
    pthread_mutex_unlock(&philo->meal_stats_mutex);
    ft_usleep(philo->time_eat);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
    return 1;
    
}
int  sleeping(t_philo *philo )
{
    if (end_simulation(philo) == 1)
        return 0;
    printf("%lu philosopher %d is sleeping\n",get_time()-(philo->data->start_time),philo->id_philo);
    ft_usleep(philo->time_sleep);
    return (1);
}

int thinking(t_philo *philo)
{
    if (end_simulation(philo) == 1)
        return 0;
    printf("%lu philosopher %d is thinking\n",
    get_time() - philo->data->start_time,philo->id_philo);
    return 1;
}

void *routin(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;

    if (philo->id_philo % 2 == 0)
        ft_usleep(philo->time_eat / 2);
    while(1)
    {  
       if (eating(philo) == 0)
            return NULL;
        if (sleeping(philo) == 0)
            return NULL;
        if (thinking(philo) == 0)
            return NULL;
        ft_usleep((philo->time_die - (get_time() - philo->last_time_eat)) / 2);
    }
    return NULL;
}
