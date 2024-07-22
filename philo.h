/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:41 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/22 01:26:03 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

void    check_arg(int ac,char **av);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t   get_time();
int	    ft_strlen(char const *s);
int     ft_atoi(const char *str);
void    *routin(void *arg);


typedef struct s_philo
{
   pthread_t thread;
   int      id_philo;
   int     time_eat;
   int     time_die;
   int     time_sleep;
   int      *dead;
   int      last_time_eat;
  
   pthread_mutex_t last_ate_mutex;
   pthread_mutex_t *r_fork;
   pthread_mutex_t *l_fork;
   
   t_data *data;
   
} t_philo;

typedef struct s_data
{
    int     num_philo;
    int     dead;
     size_t   start_time;
    pthread_mutex_t died;
    pthread_mutex_t *forks;
    t_philo *philo;
    
} t_data;     
#endif