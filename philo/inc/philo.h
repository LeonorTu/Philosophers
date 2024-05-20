/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:48 by jtu               #+#    #+#             */
/*   Updated: 2024/05/20 13:10:11 by jtu              ###   ########.fr       */
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
	int				id;
	int				meals_eaten;
	int				fork_r;
	int				fork_l;
	size_t			start_time;
	size_t			last_meal;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	int				end;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*fork;
}	t_table;

int		init_table(char **argv, t_table *table);
int		init_forks(t_table *table);
void	init_philos(t_philo *philo, t_table *table);

int		ft_atoi(const char *str);
int		err_msg(char *msg);
void	print_msg(t_philo *philo, char *msg);
size_t	get_current_time(void);

void	*philo_routine(void *arg);
void	*table_monitor(void *arg);
int		ft_eat(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_usleep(t_philo *philo, size_t sleep);
int		check_end(t_philo *philo);

void	clean_table(t_table *table);
void	clean(t_philo *philo);

#endif
