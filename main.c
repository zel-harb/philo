/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:50:28 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/07 00:42:26 by zel-harb         ###   ########.fr       */
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
   
    data->num_philo = ft_atoi(av[1]);
   pthread_mutex_init(&mutex,NULL);
    data->philo= malloc(sizeof(t_philo)*data->num_philo);
    data->time_die = ft_atoi(av[2]) ;
    data->time_eat =ft_atoi(av[3]);
    data->time_sleep =ft_atoi(av[4]);
    
}
void get_forks(t_data *data)
{
    int i;

    i = 0;
    while( i < data->num_philo )
    {
        data->philo[i].r_fork = i ;
      
        if(i  == data->num_philo - 1)
            data->philo[i].l_fork = 0;
        else 
            data->philo[i].l_fork = i + 1;
        //     printf("---------------------------------------------\n");
        // printf("right philo [%d]---> %d \n",i , data->philo[i].r_fork);
        // printf("left philo [%d]---> %d \n",i , data->philo[i].l_fork);
        i ++;
    }
    
}
 void get_time()
 {
    
 }
void *routin(void *arg)
{
    t_data *data = (t_data *)arg;
    // pthread_mutex_lock(&mutex);
    // printf("hi-->**%d\n", data->num_philo);
    // pthread_mutex_unlock(&mutex);
    return NULL;
}
void creat_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_philo)
    {
        pthread_create(&data->philo[i].thread,NULL,&routin,&data);
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
    pthread_t thread;
    check_arg(ac,av);
    init_threads(&data,ac,av);
    get_forks(&data);
    int i;
    i = 0;
    while(i <data.num_philo)
    {
          printf("---------------------------------------------\n");
        printf("right philo [%d]---> %d \n",i , data.philo[i].r_fork);
        printf("left philo [%d]---> %d \n",i , data.philo[i].l_fork);
        i ++;
    }
    creat_threads(&data);
    //pthread_create(&thread,NULL,print,NULL);
    //pthread_join(thread,NULL);
    return 0;
}