/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:59:36 by zel-harb          #+#    #+#             */
/*   Updated: 2024/09/25 02:08:44 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_number(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i++] && av[i])
	{
		j = 0;
		if (av[i][j] == '\0')
			return (ft_putstr_fd("Error\nVide argument.\n", 2), 1);
		if (av[i][j] == '-')
			return (ft_putstr_fd("Error\nWe accept positive numbers.\n", 2), 1);
		else if (ft_strlen(av[i]) == 1 && av[i][0] == '+')
			return (ft_putstr_fd("Error\nNo number.\n", 2), 1);
		else if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (printf("Error\nYour argument contient non-digit.\n"),
					1);
		}
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	if (ac > 6 || ac < 5)
	{
		ft_putstr_fd("Error\nWe accept just 5 or 6 arguments. \n", 2);
		return (1);
	}
	if (check_is_number(av))
		return (1);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			milliseconds;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf("Error\n");
		return (0);
	}
	milliseconds = (size_t)((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
	return (milliseconds);
}
