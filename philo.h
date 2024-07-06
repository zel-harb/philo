/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:43:52 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/06 09:40:54 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
    pthread_t thread;
    int     id;
    int     time_eat;
    int     time_die;
    int     time_sleep;
    int     last_to_eat;
    int     num_philo;
    pthread_mutex_t *fork;
       pthread_mutex_t mutex;
    
} t_philo;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int	ft_strlen(char const *s);
void check_arg(int ac,char **av);
int	ft_atoi(const char *str);

#endif