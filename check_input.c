/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:59:36 by zel-harb          #+#    #+#             */
/*   Updated: 2024/07/01 18:58:45 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_is_number(char **av)
{
	int i;
	int j;
	
	i = 1;
	while(av[i])
	{
		j = 0;
		while(av[i][j] == ' ')
			j++;
		if(av[i][j] == '-')
		{
			ft_putstr_fd("Error\nwe accept positive numbers.\n",2);
			exit(1);
		}
		else if(av[i][j]=='+')
			j++;
		while(av[i][j])
		{
			if(av[i][j] >= '0' && av[i][j] <='9')
				j++;
			else 
			{
				ft_putstr_fd("Error\nyour argument contient non-digit.\n",2);
				exit(1);
			}
		}
		i++;
	}
}
void check_arg(int ac,char **av)
{
	if(ac > 6 || ac < 5)
	{
		ft_putstr_fd("Error\nWe accept just 5 or 6 arguments. \n",2);
		exit(1);
	}
	check_is_number(av);
}