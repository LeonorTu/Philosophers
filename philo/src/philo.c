/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:45 by jtu               #+#    #+#             */
/*   Updated: 2024/05/19 17:12:34 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err_msg("Example: ./philo_bonus <philo_count> <time_to_die> "
				"<time_to_eat> <time_to_sleep> [times_each_must_eat]\n"));
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

int	create_threads(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &table_monitor, philo) != 0)
		return (err_msg("Thread creation fail"));
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philo_routine, \
		&philo[i]) != 0)
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

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philo;

	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (init_table(argv, &table))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * table.num_philo);
	if (!philo)
	{
		clean_table(&table);
		return (err_msg("Malloc fail"));
	}
	init_philos(philo, &table);
	if (create_threads(philo))
	{
		clean(philo);
		return (EXIT_FAILURE);
	}
	clean(philo);
	return (0);
}
