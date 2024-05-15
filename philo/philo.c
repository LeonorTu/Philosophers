/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:45 by jtu               #+#    #+#             */
/*   Updated: 2024/05/15 16:04:17 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *msg)
{
	printf("%s", msg);
	return (-1);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > INT_MAX)
		return (err_msg("Invalid number of philosophers"));
	if (ft_atoi(argv[2]) <= 0)
		return (err_msg("Invalid time to die"));
	if (ft_atoi(argv[3]) <= 0)
		return (err_msg("Invalid time to eat"));
	if (ft_atoi(argv[4]) <= 0)
		return (err_msg("Invalid time to sleep"));
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (err_msg("Invalid number of times each philosopher must eat"));
	return (0);
}

void	init_table(char **argv, t_table *table)
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
	pthread_mutex_init(&table->end_lock, NULL);
	pthread_mutex_init(&table->print_lock, NULL);
	// printf("%d", table->num_philo);
}

int	philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_philo)
	{
		if (get_current_time() - philo[i].last_meal >= philo->table->time_to_die)
		{
			print_msg(&philo[i], "died");
			pthread_mutex_lock(&philo->table->end_lock);
			philo->table->end = 1;
			pthread_mutex_unlock(&philo->table->end_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_finished(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philo->table->must_eat < 0)
		return (-1);
	while (i < philo->table->num_philo)
	{
		if (philo[i].meals_eaten >= philo->table->must_eat)
			finished++;
		i++;
	}
	if (finished == philo->table->num_philo)
	{
		pthread_mutex_lock(&philo->table->end_lock);
		philo->table->end = 1;
		pthread_mutex_unlock(&philo->table->end_lock);
		return (1);
	}
	return (0);
}

void	*table_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (philo_dead(philo) == 1 || philo_finished(philo) == 1)
			break;
	return (arg);
}

int	create_threads(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &table_monitor, philo) != 0)
			return (err_msg("Thread creation fail"));
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philo_routine, &philo[i]) != 0)
			return (err_msg("Thread creation fail"));
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
			return (err_msg("Thread join fail"));
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (err_msg("Thread join fail"));
		i++;
	}
	return (0);
}

void	init_forks(pthread_mutex_t *fork, t_table *table)
{
	int	i;

	i = 0;
	//fork = malloc(sizeof(pthread_mutex_t *) * table->num_philo);
	while (i < table->num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philo, pthread_mutex_t	*fork, t_table *table)
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
		philo[i].fork_right = &fork[i];
		philo[i].fork_left = &fork[(i + 1) % table->num_philo];
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	pthread_mutex_t	*fork;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("Please give 5 or 6 arguments! Example: ./philo number_of_philosophers \
		time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
		return (EXIT_FAILURE);
	}
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	init_table(argv, &table);
	fork = malloc(sizeof(pthread_mutex_t *) * table.num_philo);
	init_forks(fork, &table);
	philo = malloc(sizeof(t_philo) * table.num_philo);
	init_philos(philo, fork, &table);
	create_threads(philo);
	return (0);
}
