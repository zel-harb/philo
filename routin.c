/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:18:22 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/20 03:43:53 by zel-harb         ###   ########.fr       */
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
int  eating(t_philo *philo)
{
    if(philo->data->dead == 1)
    {
        // pthread_mutex_unlock(philo->r_fork);
        // pthread_mutex_unlock(philo->l_fork);
        return 0;
    }
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(philo->l_fork);
    printf("philosopher %d has taken a fork\n",philo->id_philo);
    printf("philosopher %d is eating\n",philo->id_philo);
      if(philo->data->dead == 1)
    {
         pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        return 0;
    }
    philo->last_time_eat = get_time();
    ft_usleep(philo->time_eat);
    if(philo->data->dead == 1)
    {
         pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        return 0;
    }
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
    
}
void sleeping(t_philo *philo )
{
    printf("philosopher %d is sleeping\n",philo->id_philo);
    ft_usleep(philo->time_sleep); 
}
void thinking(t_philo *philo)
{
     printf("philosopher %d is thinking\n",philo->id_philo);
}
void *routin(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    if(philo->id_philo % 2 != 0)
        ft_usleep(100);
    while(*philo->dead == 0)
    {  
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    
    return NULL;
}
