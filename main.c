/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:50:28 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/06 17:57:27 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
pthread_mutex_t mutex;

void *print()
{
    printf("hello\n");
    return NULL;
}
void init_threads(t_data *data,int ac,char **av)
{
    int i;
    i = 0;
    data->num_philo = ft_atoi(av[1]);
    data->philo= malloc(sizeof(t_philo)*data->num_philo);
    while(i < ac -1)
    {
        data->philo[i].id = i + 1;
        // philo[i].fork = i + 1;
        data->time_die = ft_atoi(av[2]) ;
        data->time_eat =ft_atoi(av[3]);
        data->time_sleep =ft_atoi(av[4]);
        i++;
    }
}
// void get_forks()
// {
    
// }
void *routin(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_lock(&mutex);
    printf("hi-->**%d\n", philo->id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void creat_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_philo)
    {
        pthread_create(&data->philo[i].thread,NULL,routin,&data->philo[i]);
        pthread_join(data->philo[i].thread, NULL) ;
        i++;
    }
}

int main(int ac,char **av)
{
    t_data data;
    pthread_t thread;
    check_arg(ac,av);
    init_threads(&data,ac,av);
    creat_threads(&data);
    pthread_create(&thread,NULL,print,NULL);
    pthread_join(thread,NULL);
    return 0;
}