/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 21:58:25 by sjacki            #+#    #+#             */
/*   Updated: 2021/10/18 14:01:18 by alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int			powerdex(int power)
{
	int		walk;
	int		res;

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

static int			atoires(int walk, int result, int count, const char *str)
{
	if (count > 9)
		return (-1);
	while (count != 0)
	{
		result = result + ((str[walk] - 48) * powerdex(count - 1));
		walk++;
		count--;
	}
	return (result);
}

int					ft_atoi(const char *str)
{
	int		walk;
	int		count;
	int		result;
	int		negorpos;

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

void				cast_sleep(t_argv *arg, long long time)
{
	long long x;

	x = get_time();
	while (!arg->die)
	{
		if ((get_time() - x) >= time)
			break ;
		usleep(10);
	}
}

void				ph_eat(t_philo *philo)
{
	t_argv		*arg;

	arg = (t_argv*)philo->arg;
	pthread_mutex_lock(&(arg->fork[philo->l_fork]));
	ph_send(arg, philo->id, "has taken a fork");
	pthread_mutex_lock(&(arg->fork[philo->r_fork]));
	ph_send(arg, philo->id, "has taken a fork");
	ph_send(arg, philo->id, "is eating");
	cast_sleep(arg, arg->time_to_eat);
	philo->time_last_eat = get_time();
	philo->count_ate++;
	pthread_mutex_unlock(&(arg->fork[philo->l_fork]));
	pthread_mutex_unlock(&(arg->fork[philo->r_fork]));
	ph_send(arg, philo->id, "is sleeping");
	cast_sleep(arg, arg->time_to_sleep);
}
