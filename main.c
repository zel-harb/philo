/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:49 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/26 22:35:07 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_threads(t_data *data,int ac,char **av)
{
    int i;
    i = 0;
    data->num_philo = ft_atoi(av[1]);
    data->dead =0;
    data->forks = malloc(sizeof(pthread_mutex_t) *data->num_philo);
    data->philo= malloc(sizeof(t_philo)*data->num_philo);
    while(i < data->num_philo)
    {
        data->philo[i].id_philo = i+ 1;
        data->philo[i].time_die = ft_atoi(av[2]);
        data->philo[i].time_eat= ft_atoi(av[3]);
        data->philo[i].time_sleep= ft_atoi(av[4]);
        if(ac == 6)
            data->philo[i].number_eat = ft_atoi(av[5]);
        data->philo[i].dead = &data->dead;
        data->philo[i].data = data;
        // data->philo[i].last_time_eat = 0;
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
    pthread_mutex_init(&data->died,NULL);
    
}

void get_forks(t_data *data)
{
   int i;
   i = 0;
   while(i < data->num_philo)
   {
        if(i  == data->num_philo - 1)
        {
            data->philo[i].l_fork = &data->forks[i];
            data->philo[i].r_fork = &data->forks[0];
        }
        else
        {
            data->philo[i].r_fork= &data->forks[i];
            data->philo[i].l_fork = &data->forks[i +1];
        }
        i ++;
        
    } 
}


void creat_threads(t_data *data)
{
    int i;
  
    i = 0;
    while(i < data->num_philo)
    {
        pthread_mutex_lock(&data->philo[i].last_ate_mutex);
        data->philo[i].last_time_eat = get_time();
        pthread_mutex_unlock(&data->philo[i].last_ate_mutex);
        pthread_create(&data->philo[i].thread,NULL,&routin,&data->philo[i]);
        i++;
    }
    // while(j < data->num_philo)
    // {
       
    //     if(get_time() - *data->philo[j].dead > data->philo[j].time_die)
    //         *data->philo[j].dead = 1;
    //         j++;
    //      if(j == data->num_philo)
    //         j =0;
    //      //  break;


    // } 
    // i = 0;
    // while(i < data->num_philo)
    // {
    //     pthread_join(data->philo[i].thread, NULL) ;
    //     i++;
    // }
}
int check_philo_die(t_philo * philo)
{
    size_t time_to_die;
    size_t last_ate;
    
    time_to_die = philo->time_die;
    last_ate = get_time() - philo->last_time_eat;
    return(time_to_die - last_ate);
}

int monitor(t_data *data)
{
    int i;
    
    while(1)
    {
       i = 0;
       while (i < data->num_philo)
       {
            if(check_philo_die(&data->philo[i]) < 0)
            {
                printf("%lu philosopher %d died \n",get_time()-data->start_time,data->philo[i].id_philo);
                pthread_mutex_lock(&data->died);
                data->dead = 1;
                pthread_mutex_unlock(&data->died);
                return(1);
            }
            i++;
       } 
    }
    return 0;
}
void	join_threads(t_data *data)
{
    int i;
    
    i = 0;
     while(i < data->num_philo)
    {
        pthread_join(data->philo[i].thread, NULL) ;
        i++;
    }
    return ;
 
}

int main(int ac,char **av)
{
    t_data data;
    pthread_t thread;
    check_arg(ac,av);
    init_threads(&data,ac,av);
    init_forks(&data);
    get_forks(&data);
    data.start_time = get_time();
    creat_threads(&data);
    monitor(&data);
    join_threads(&data);
    return 0;
    
}