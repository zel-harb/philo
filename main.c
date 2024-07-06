/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:50:28 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/06 10:50:34 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
pthread_mutex_t mutex;

void *print()
{
    printf("hello\n");
    return NULL;
}
void init_threads(t_philo *philo,int ac,char **av)
{
    int i;
    i = 0;
    while(i < ac -1)
    {
        philo[i].id = i + 1;
        // philo[i].fork = i + 1;
        philo[i].num_philo = ft_atoi(av[1]);
        philo[i].time_die = ft_atoi(av[2]) ;
        philo[i].time_eat =ft_atoi(av[3]);
        philo[i].time_sleep =ft_atoi(av[4]);
        
        i++;
    }
}
void get_forks()
{
    
}
void *routin(void *arg)
{
 
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_lock(&mutex);
    
     pthread_mutex_unlock(&mutex);
    return NULL;
}
void creat_threads(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo[0].num_philo)
    {
        pthread_create(&philo[i].thread,NULL,routin,&philo[i]);
        pthread_join(philo[i].thread, NULL) ;
        i++;
    }
}

int main(int ac,char **av)
{
    t_philo philo[ac -1];
    pthread_t thread;
    check_arg(ac,av);
    init_threads(philo,ac,av);
    creat_threads(philo);
    pthread_create(&thread,NULL,print,NULL);
    pthread_join(thread,NULL);
    return 0;
}