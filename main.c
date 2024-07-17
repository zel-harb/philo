/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:49 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/17 01:37:31 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_threads(t_data *data,int ac,char **av)
{
    int i;
    i = 0;
    data->num_philo = ft_atoi(av[1]);
    data->forks = malloc(sizeof(pthread_mutex_t) *data->num_philo);
    data->philo= malloc(sizeof(t_philo)*data->num_philo);
    while(i < data->num_philo)
    {
        data->philo[i].id_philo = i+ 1;
        data->philo[i].time_die = ft_atoi(av[2]);
        data->philo[i].time_eat= ft_atoi(av[3]);
        data->philo[i].time_sleep= ft_atoi(av[4]);
        data->philo[i].last_time_eat = 0;
        i++;
    }
}
void init_forks(t_data *data)
{
    int i;
    i = 0;
    while(i < data->num_philo)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
}

void get_forks(t_data *data)
{
   int i;
   i = 0;
   while(i < data->num_philo)
   {
        data->philo[i].r_fork= &data->forks[i];
         if(i  == data->num_philo - 1)
            data->philo[i].l_fork = &data->forks[0];
        else 
            data->philo[i].l_fork = &data->forks[i +1];
        i ++;
        
    } 
}


void creat_threads(t_data *data)
{
    int i;
    i = 0;

    while(i < data->num_philo)
    {
        pthread_create(&data->philo[i].thread,NULL,&routin,&data->philo[i]);
        i++;
    }
    i = 0;
    while(i < data->num_philo)
    {
        pthread_join(data->philo[i].thread, NULL) ;
        i++;
    }
}

int main(int ac,char **av)
{
    t_data data;
    check_arg(ac,av);
    init_threads(&data,ac,av);
    init_forks(&data);
    get_forks(&data);
    creat_threads(&data);
    
    
}