/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:50:28 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/13 23:56:17 by zel-harb         ###   ########.fr       */
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
   pthread_mutex_init(&mutex,NULL);
    data->philo= malloc(sizeof(t_philo)*data->num_philo);
    data->time_die = ft_atoi(av[2]) ;
    data->time_eat =ft_atoi(av[3]);
    data->time_sleep =ft_atoi(av[4]);
    pthread_mutex_init(&data->lock_dead,NULL);
    pthread_mutex_init(&data->lock_id_philo,NULL);
    data->die = 0;
    data->id_philo = 0;
    while(i < data->num_philo)
    {
        data->philo[i].id= i + 1;
        data->philo[i].time_eat=0;
        data->philo[i].time_to_sleep=0;
        i++;
    }
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
    // size_t start;

    // start=get_time();
    // while((get_time() - start) < milliseconds)
    //     usleep(500);
    usleep(milliseconds);
    return;
}

void eating(t_data *data)
{
    int i;
    i = data->philo[data->id_philo].id;
    // pthread_mutex_lock(&data->forks[data->philo[i].r_fork]);
    printf("philosopher %d has taken a fork\n",i);
    // pthread_mutex_lock(&data->forks[data->philo[i].l_fork]);
    printf("philosopher %d has taken a fork\n",i);
    //pthread_mutex_lock(&data->philo[i].last_to_eat);
      
    data->philo[i].last_to_eat = get_time() + data->time_eat;
    printf(" %d philosopher %d is eating\n",data->philo[i].time_eat,i);
    data->philo[i].time_eat = data->philo[i].time_eat + data->time_eat;
    ft_usleep(data->time_eat);
    
    // pthread_mutex_unlock(&data->philo[i].last_to_eat);
    // pthread_mutex_unlock(&data->forks[data->philo[i].r_fork]);
    // pthread_mutex_unlock(&data->forks[data->philo[i].l_fork]);
}
void sleep_t(t_data *data )
{
    int i;
    i = data->philo[data->id_philo].id;
    printf("%d philosopher %d is sleeping\n",data->philo[i].time_to_sleep,data->philo[i].id);
    ft_usleep(data->time_sleep); 
    data->philo[i].time_to_sleep = data->philo[i].time_to_sleep + data->time_sleep;
}
void thinking(t_data *data )
{
    printf("philosopher %d is thinking\n",data->id_philo);
}
void *routin1(void *arg)
{
    t_data *data = (t_data *)arg;
    pthread_mutex_lock(&data->lock_dead);
    // printf("hi-->**%d\n", data->num_philo);
     eating(data);
     sleep_t(data);
     data->philo[data->id_philo].id ++;
    //  thinking(data);
    pthread_mutex_unlock(&data->lock_dead);
    
    return NULL;
}
void *routin()
{
    printf("kdkd\n");
    return NULL;
}
void creat_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_philo)
    {
        pthread_create(&data->philo[i].thread,NULL,&routin1,data);
        //   pthread_create(&data->philo[i+1].thread,NULL,&routin1,data);
        i++;
    }
    i = 0;
    
    while(i < data->num_philo)
    {
         
         //pthread_mutex_lock(&data->lock_id_philo);
          pthread_join(data->philo[i].thread, NULL) ;
        
        //  data->id_philo = i;
         i++;
        // if(i == data->num_philo)
        // {
        //        printf("hei,%d\n",i);
        //     i = 0;
        }
        printf("hi\n");
       // pthread_join(data->philo[0].thread, NULL) ;
       //pthread_mutex_unlock(&data->lock_id_philo);
      
        
    // }
}
// void creat_treads(t_data *data)
// {
//     int i;
//     i = 0;
//     while(i < data->num_philo)
//     {
//         pthread_create(data->philo[i].thread,NULL,&routin,)
//     }
// }

int main(int ac,char **av)
{
    t_data data;
    check_arg(ac,av);
    init_threads(&data,ac,av);
    get_forks(&data);
    int i = 0;
    // while(i <data.num_philo)
    // {
    //     printf("---------------------------------------------\n");
    //     printf("right philo [%d]---> %d \n",i , data.philo[i].r_fork);
    //     printf("left philo [%d]---> %d \n",i , data.philo[i].l_fork);
    //     i ++;
    // }
    // ft_usleep((size_t)data.time_sleep);
     //printf("hi\n");
    // printf("get_time %zu\n",get_time());
    creat_threads(&data);
    return 0;
}