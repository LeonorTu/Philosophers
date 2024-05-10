/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:48 by jtu               #+#    #+#             */
/*   Updated: 2024/05/10 16:50:28 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <limits.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			meals_eaten;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int	id;
	int	num_philo;
	pthread_mutex_t	*fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eating_times;
	t_philo	*philo;
}	t_table;

int	ft_atoi(const char *str);
int	err_msg(char *msg);
int	ft_eat(t_philo *philo);
int	ft_think(t_philo *philo);
int	ft_sleep(t_philo *philo);

#endif