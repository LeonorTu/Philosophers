/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:48 by jtu               #+#    #+#             */
/*   Updated: 2024/05/13 15:46:35 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	t_table		*table;
	pthread_t	thread;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
}	t_philo;

typedef struct s_table
{
	int	id;
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eating_times;
}	t_table;

int	ft_atoi(const char *str);
int	err_msg(char *msg);
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
int	ft_usleep(size_t sleep);

#endif