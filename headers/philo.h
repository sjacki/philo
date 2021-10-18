/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:40:07 by sjacki            #+#    #+#             */
/*   Updated: 2021/10/15 08:44:40 by alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct t_argv;

typedef struct	s_philo
{
	long long			time_last_eat;
	struct t_argv		*arg;
	pthread_t			thr_id;
	int					count_ate;
	int					l_fork;
	int					r_fork;
	int					id;
}				t_philo;

typedef struct	s_argv
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	meal_check;
	unsigned int	number_of_times_each_philosopher_must_eat;
	unsigned int	number_of_philosophers;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	long long		f_time;
	int				die;
	int				must_eat;
	t_philo			*philo;
}				t_argv;

int			init_struct(int argc, char **argv, t_argv *arg);
void		init_pfilo(t_philo *philo, t_argv *arg);
int			launch_philo(t_argv *arg);
int			ft_atoi(const char *str);
long long	get_time(void);
int			ft_putstr(char *str);
int			ft_strlen(char *str);
int			ft_error(char *str);
void		ph_send(t_argv *arg, int philo_id, char *str);
void		cast_sleep(t_argv *arg, long long time);
void		ph_eat(t_philo *philo);

#endif