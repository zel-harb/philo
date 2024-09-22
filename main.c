/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-harb <zel-harb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:34:49 by zel-harb          #+#    #+#             */
/*   Updated: 2024/08/04 02:32:59 by zel-harb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	check_arg(ac, av);
	init_threads(&data, ac, av);
	init_forks(&data);
	get_forks(&data);
	data.start_time = get_time();
	creat_threads(&data);
	monitor(&data);
	join_threads(&data);
	return (0);
}
