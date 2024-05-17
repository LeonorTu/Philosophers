/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:54:18 by jtu               #+#    #+#             */
/*   Updated: 2024/05/17 20:34:04 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(char **argv, t_table *table)
{
	table->num_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->end = 0;
	if (pthread_mutex_init(&table->end_lock, NULL))
		return (err_msg("Mutex init fail"));
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (err_msg("Mutex init fail"));
	if (pthread_mutex_init(&table->meal_lock, NULL))
		return (err_msg("Mutex init fail"));
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->fork)
		return (err_msg("Malloc fail"));
	if (init_forks(table))
		return (1);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (err_msg("Mutex init fail"));
		i++;
	}
	return (0);
}

void	init_philos(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].table = table;
		philo[i].fork_right = &table->fork[i];
		philo[i].fork_left = &table->fork[(i + 1) % table->num_philo];
		i++;
	}
}
