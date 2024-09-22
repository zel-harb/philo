/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:41 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/21 04:55:23 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

void					check_arg(int ac, char **av);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
size_t					get_time(void);
int						ft_strlen(char const *s);
int						ft_atoi(const char *str);
void					*routin(void *arg);
int						monitor(t_data *data);
void					init_threads(t_data *data, int ac, char **av);
void					init_forks(t_data *data);
void					get_forks(t_data *data);
void					creat_threads(t_data *data);
void					join_threads(t_data *data);

typedef struct s_philo
{
	pthread_t			thread;
	int					id_philo;
	int					time_eat;
	long				time_die;
	int					time_sleep;
	int					number_eat;
	int					counter;
	int					*dead;
	long				last_time_eat;
	int					check;
	pthread_mutex_t		meal_stats_mutex;
	pthread_mutex_t		check_counter;
	pthread_mutex_t		last_ate_mutex;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;

	t_data				*data;

}						t_philo;

typedef struct s_data
{
	int					num_philo;
	int					dead;
	int					full;
	int					number_eat;
	size_t				start_time;
	pthread_mutex_t		died;
	pthread_mutex_t		*forks;
	pthread_mutex_t		full_mutex;
	pthread_mutex_t		print_eat;
	t_philo				*philo;

}						t_data;
#endif