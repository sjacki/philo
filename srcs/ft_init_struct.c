/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:46:02 by sjacki            #+#    #+#             */
/*   Updated: 2021/10/18 14:01:31 by alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int		ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

static int		check_dg(int argc, char **argv)
{
	int		x;
	int		y;

	y = 0;
	x = 1;
	while (argv[x])
	{
		while (argv[x][y])
		{
			if (argv[x][y] == 45 && y == 0)
			{
				y++;
				continue;
			}
			if (!ft_isdigit(argv[x][y]) &&
				ft_error("the argument contains letters"))
				return (1);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int				check_negotive(char **argv, t_argv *arg)
{
	int		buf;

	buf = ft_atoi(argv[1]);
	if (buf < 2 || buf > 250)
		return (ft_error("wrong number of philosophers"));
	arg->number_of_philosophers = buf;
	buf = ft_atoi(argv[2]);
	if (buf < 0)
		return (ft_error("wrong time to die"));
	arg->time_to_die = buf;
	buf = ft_atoi(argv[3]);
	if (buf < 0)
		return (ft_error("wrong time to eat"));
	arg->time_to_eat = buf;
	buf = ft_atoi(argv[4]);
	if (buf < 0)
		return (ft_error("wrong time to sleep"));
	arg->time_to_sleep = buf;
}

int				init_struct(int argc, char **argv, t_argv *arg)
{
	int		buf;

	arg->die = 0;
	arg->must_eat = 0;
	if (check_dg(argc, argv))
		return (1);
	if (check_negotive(argv, arg))
		return (1);
	if (argc == 6)
	{
		buf = ft_atoi(argv[5]);
		if (buf <= 0)
			return (ft_error("wrong number of <must_eat>"));
		arg->number_of_times_each_philosopher_must_eat = buf;
	}
	else
		arg->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}

void			init_pfilo(t_philo *philo, t_argv *arg)
{
	int i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].arg = (struct t_argv*)arg;
		philo[i].count_ate = 0;
		philo[i].time_last_eat = 0;
		if (philo[i].id == arg->number_of_philosophers)
		{
			philo[i].l_fork = philo[i].id - 1;
			philo[i].r_fork = 0;
		}
		else
		{
			philo[i].l_fork = philo[i].id - 1;
			philo[i].r_fork = philo[i].id;
		}
		i++;
	}
}
