/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:41 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/17 01:17:57 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

void    check_arg(int ac,char **av);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int	    ft_strlen(char const *s);
int     ft_atoi(const char *str);
void *routin(void *arg);

typedef struct s_philo
{
   pthread_t thread;
   int      id_philo;
   int     time_eat;
   int     time_die;
   int     time_sleep;
   int      dead;
   int      last_time_eat;
   
   pthread_mutex_t *r_fork;
   pthread_mutex_t *l_fork;
    
} t_philo;
typedef struct s_data
{
    int     num_philo;
    pthread_mutex_t *forks;  // {0, 1, 2, 3}
     // philo id 0  :  right -> forks[0] 
     // philo id 0  :  left  -> forks[1] 
     
     // philo id 1  :  right -> forks[1] 
     // philo id 1  :  left  -> forks[2]
     
     // philo id 3 : right -> fork[3] 
     // philo id 3 : left  -> fork[0] 
    t_philo *philo;
} t_data;     
#endif