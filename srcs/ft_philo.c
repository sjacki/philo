/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:40:59 by sjacki            #+#    #+#             */
/*   Updated: 2021/10/15 08:25:31 by alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int		main(int argc, char **argv)
{
	t_argv	arg;

	if (argc < 5 || argc > 6)
		return (ft_error("wrong number of arguments"));
	if (init_struct(argc, argv, &arg))
		return (1);
	if (launch_philo(&arg))
		return (1);
	return (0);
}
