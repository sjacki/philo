/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:50:13 by sjacki            #+#    #+#             */
/*   Updated: 2021/10/18 14:01:45 by alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	close_lanch(t_argv *arg, t_philo *philo)
{
	int		x;

	x = -1;
	while (++x < arg->number_of_philosophers)
		pthread_detach(philo[x].thr_id);
	x = -1;
	while (++x < arg->number_of_philosophers)
		pthread_mutex_destroy(&arg->fork[x]);
	pthread_mutex_destroy(&arg->write);
}

void	dead_check(t_argv *arg, t_philo *philo)
{
	int		x;

	while (!arg->must_eat)
	{
		x = -1;
		while (++x < arg->number_of_philosophers && !arg->die)
		{
			if ((get_time() - philo[x].time_last_eat) > arg->time_to_die)
			{
				ph_send(arg, x, "is died");
				arg->die++;
			}
		}
		if (arg->die)
			break ;
		x = 0;
		while (arg->number_of_times_each_philosopher_must_eat != -1 &&
				x < arg->number_of_philosophers &&
				philo[x].count_ate >=
				arg->number_of_times_each_philosopher_must_eat)
			x++;
		if (x == arg->number_of_philosophers)
			arg->must_eat++;
	}
}

void	*thread(void *void_philo)
{
	t_philo		*philo;
	t_argv		*arg;
	int			x;

	x = 0;
	philo = (t_philo*)void_philo;
	arg = (t_argv*)philo->arg;
	if (!(philo->id % 2))
		cast_sleep(arg, 50);
	while (!arg->die)
	{
		if (arg->die)
			break ;
		ph_eat(philo);
		if (arg->must_eat)
			break ;
		ph_send(arg, philo->id, "is thinking");
		x++;
	}
	return (NULL);
}

int		start_launch_philo(t_argv *arg, t_philo *philo)
{
	int			i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		philo[i].time_last_eat = get_time();
		if (pthread_create(&(philo[i].thr_id), NULL, thread, &(philo[i])))
			return (ft_error("failed to create thread"));
		i++;
	}
	dead_check(arg, philo);
	close_lanch(arg, philo);
}

int		launch_philo(t_argv *arg)
{
	int			i;
	t_philo		*philo;

	philo = arg->philo;
	i = 0;
	if (!(philo = (t_philo*)malloc(sizeof(t_philo) *
			arg->number_of_philosophers))
			|| !(arg->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
		* arg->number_of_philosophers)))
		return (ft_error("memory allocation error"));
	while (i < arg->number_of_philosophers)
	{
		if (pthread_mutex_init(&(arg->fork[i]), NULL))
			return (ft_error("mutex initialization error"));
		i++;
	}
	if (pthread_mutex_init(&(arg->write), NULL))
		return (ft_error("mutex initialization error"));
	if (pthread_mutex_init(&(arg->meal_check), NULL))
		return (ft_error("mutex initialization error"));
	i = 0;
	arg->f_time = get_time();
	init_pfilo(philo, arg);
	start_launch_philo(arg, philo);
	return (0);
}
