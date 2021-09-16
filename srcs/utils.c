/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:20:36 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/16 22:18:45 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int		ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

int		ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

int		ft_error(char *str)
{
	ft_putstr("\033[1m\033[31mError: \033[22m");
	ft_putstr(str);
	ft_putstr("\n\033[35m");
	return (1);
}
