/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:48 by jtu               #+#    #+#             */
/*   Updated: 2024/05/02 18:06:26 by jtu              ###   ########.fr       */
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
}	t_philo;

typedef struct s_table
{
	int	id;
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eating_times;
	t_philo	*philos;
}	t_table;



int	ft_atoi(const char *str);
int	err_msg(char *msg);

#endif