/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:40:59 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/15 21:30:39 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"


int		main(int argc, char **argv)
{
	t_argv	arg;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: wrong number of arguments\n"));
	if (init_struct(argc, argv, &arg))
		return (1);
}