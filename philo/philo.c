/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:45 by jtu               #+#    #+#             */
/*   Updated: 2024/05/10 16:45:51 by jtu              ###   ########.fr       */
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
		table->eating_times = ft_atoi(argv[5]);
	else
		table->eating_times = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	table->fork = malloc(sizeof(pthread_mutex_t *) * table->num_philo);
	//printf("%d", table->num_philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_eat(philo);
		ft_think(philo);
		ft_sleep(philo);
	}
	return (arg);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&(table->philo[i].thread), NULL, &philo_routine, &table->philo[i]) != 0)
			return (err_msg("Thread creation fail"));
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (err_msg("Thread creation fail"));
		i++;
	}
	return (0);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	pthread_mutex_t	mutex;

	if (argc != 5 && argc != 6)
	{
		printf("Please give 5 or 6 arguments! Example: ./philo number_of_philosophers \
		time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
		return (EXIT_FAILURE);
	}
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	init_table(argv, &table);
	create_threads(&table);
	return (0);
}