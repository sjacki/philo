/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:46:02 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/15 21:44:44 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int		init_struct(int argc, char **argv, t_argv *arg)
{
	int		buf;
	
	buf = ft_atoi(argv[1]);
	if (buf < 2 || buf > 250)
		return (ft_error("Error: wrong number of philosophers\n"));
	arg->number_of_philosophers = buf;
	buf = ft_atoi(argv[2]);
	if (buf < 0)
		return (ft_error("Error: wrong time to die\n"));
	arg->time_to_die = buf;
	buf = ft_atoi(argv[3]);
	if (buf < 0)
		return (ft_error("Error: wrong time to eat\n"));
	arg->time_to_eat = buf;
	buf = ft_atoi(argv[4]);
	if (buf < 0)
		return (ft_error("Error: wrong time to sleep\n"));
	arg->time_to_sleep = buf;
	if (argc == 6)
	{
		buf = ft_atoi(argv[5]);
		if (buf <= 0)
			return (ft_error("Error: wrong number of <must_eat>\n"));
		arg->number_of_times_each_philosopher_must_eat = buf;	
	}
	else
		arg->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}