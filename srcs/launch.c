/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:50:13 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/17 01:11:41 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ph_send(t_argv *arg, int philo_id, char *str)
{
	pthread_mutex_lock(&(arg->write));
	if (!(arg->die))
		printf("%lli %d %s\n", get_time() - arg->f_time, philo_id + 1, str);
	pthread_mutex_unlock(&(arg->write));
	return ;
}

void	close_lanch(t_argv *arg, t_philo *philo)
{
	int		x;

	x = -1;
	while (++x < arg->number_of_philosophers)
		pthread_join(philo[x].thr_id, NULL);
	x = -1;
	while (++x < arg->number_of_philosophers)
		pthread_mutex_destroy(&arg->fork[x]);
	pthread_mutex_destroy(&arg->write);
}

void	dead_check(t_argv *arg, t_philo *philo)
{
	int		x;

	x = 0;
	while (!arg->must_eat)
	{
		x = -1;
		while (++x < arg->number_of_philosophers && !arg->die)
		{
			pthread_mutex_lock(&arg->meal_check);
			if ((get_time() - philo[x].time_last_eat) > arg->time_to_die)
			{
				ph_send(arg, x, "died");
				arg->die++;
			}
			pthread_mutex_unlock(&arg->meal_check);
			usleep(100);
		}
		if (arg->die)
			break ;
		x = 0;
		while (arg->number_of_times_each_philosopher_must_eat != -1 && x < arg->number_of_philosophers &&
				philo[x].count_ate - 1 >= arg->number_of_times_each_philosopher_must_eat)
			x++;
		if (x == arg->number_of_philosophers)
			arg->must_eat++;
	}
}

void	cast_sleep(t_argv *arg, long long time)
{
	long long x;

	x = get_time();
	while (!arg->die)
	{
		if ((get_time() - x) >= time)
			break ;
		usleep(50);
	}
}

void	ph_eat(t_philo *philo)
{
	t_argv		*arg;

	arg = (t_argv*)philo->arg;
	pthread_mutex_lock(&(arg->fork[philo->l_fork]));
	ph_send(arg, philo->id, "has take a fork");
	pthread_mutex_lock(&(arg->fork[philo->r_fork]));
	ph_send(arg, philo->id, "has take a fork");
	pthread_mutex_lock(&(arg->meal_check));
	ph_send(arg, philo->id, "is eating");
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&(arg->meal_check));
	cast_sleep(arg, arg->time_to_eat);
	philo->count_ate++;
	pthread_mutex_unlock(&(arg->fork[philo->l_fork]));
	pthread_mutex_unlock(&(arg->fork[philo->r_fork]));
}

void	*thread(void *void_philo)
{
	t_philo		*philo;
	t_argv		*arg;
	int			x;

	x = 0;
	philo = (t_philo*)void_philo;
	arg = (t_argv*)philo->arg;
	if (philo->id % 2)
		usleep(15000);
	while (!arg->die)
	{
		ph_eat(philo);
		if (arg->must_eat)
			break ;
		ph_send(arg, philo->id, "is sleeping");
		cast_sleep(arg, arg->time_to_sleep);
		ph_send(arg, philo->id, "is thinking");
		x++;
	}
	return (NULL);
}

int		launch_philo(t_argv *arg)
{
	int			i;
	t_philo		*philo;

	philo = arg->philo;
	i = 0;
	if (!(philo = (t_philo*)malloc(sizeof(t_philo*) *
	 	arg->number_of_philosophers))
	 	|| !(arg->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t*)
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
	while (i < arg->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].arg = (struct t_argv*)arg;
		philo[i].count_ate = 0;
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % (arg->number_of_philosophers);
		philo[i].time_last_eat = 0;
		if (pthread_create(&(philo[i].thr_id), NULL, thread, &(philo[i])))
			return (ft_error("failed to create thread"));
		philo[i].time_last_eat = get_time();
		i++;
	}
	dead_check(arg, philo);
	close_lanch(arg, philo);
	return (0);
}