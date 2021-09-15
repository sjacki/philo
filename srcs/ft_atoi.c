/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 21:58:25 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/15 21:09:46 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int		powerdex(int power)
{
	int walk;
	int res;

	res = 1;
	walk = 0;
	if (power == 0)
		return (1);
	while (walk < power)
	{
		res = res * 10;
		walk++;
	}
	return (res);
}

static int		atoires(int walk, int result, int count, const char *str)
{
	while (count != 0)
	{
		result = result + ((str[walk] - 48) * powerdex(count - 1));
		walk++;
		count--;
	}
	return (result);
}

int		ft_atoi(const char *str)
{
	int walk;
	int count;
	int result;
	int negorpos;

	negorpos = 1;
	count = 0;
	walk = 0;
	result = 0;
	while (str[walk] == 32 || (str[walk] >= 9 && str[walk] <= 13))
		walk++;
	if (str[walk] == 45)
	{
		negorpos = -1;
		walk++;
	}
	else if (str[walk] == 43)
		walk++;
	while (str[walk] >= 48 && str[walk] <= 57)
	{
		walk++;
		count++;
	}
	walk = walk - count;
	return (atoires(walk, result, count, str) * negorpos);
}
