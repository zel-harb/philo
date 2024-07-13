/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:43:52 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/13 23:55:08 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    pthread_t thread;
    int     id;
    int     l_fork;
    int     r_fork;
    int    last_to_eat;
    int     time_eat;
    int     time_to_sleep;
    
    pthread_mutex_t *fork; // left + right
}   t_philo;

typedef struct s_data
{
    int     num_philo;
    int     time_eat;
    int     time_die;
    int     time_sleep;
    pthread_mutex_t *forks;  // {0, 1, 2, 3}
     // philo id 0  :  right -> forks[0] 
     // philo id 0  :  left  -> forks[1] 
     
     // philo id 1  :  right -> forks[1] 
     // philo id 1  :  left  -> forks[2]
     
     // philo id 3 : right -> fork[3] 
     // philo id 3 : left  -> fork[0] 
     int  die;
     int id_philo;//id_philo;
     pthread_mutex_t lock_id_philo;
    pthread_mutex_t lock_dead;
    t_philo         *philo;
} t_data;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int	    ft_strlen(char const *s);
void    check_arg(int ac,char **av);
int	    ft_atoi(const char *str);

#endif