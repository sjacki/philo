/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:40:07 by sjacki            #+#    #+#             */
/*   Updated: 2021/09/15 23:00:49 by sjacki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

typedef struct	s_argv
{
	unsigned int	number_of_times_each_philosopher_must_eat;
	unsigned int	number_of_philosophers;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
}				t_argv;

typedef struct	s_philo
{
	
}				t_philo;

int		init_struct(int argc, char **argv, t_argv *arg);
int		ft_atoi(const char *str);
int		ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_error(char *str);


#endif