/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:45 by jtu               #+#    #+#             */
/*   Updated: 2024/04/30 16:52:16 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_msg(char *msg)
{
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	check_args(char **argv)
{
	t_table	*table;

	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > INT_MAX)
		err_msg("Invalid number of philosophers");
	if (ft_atoi(argv[2]) <= 0)
		err_msg("Invalid time to die");
	if (ft_atoi(argv[3]) <= 0)
		err_msg("Invalid time to eat");
	if (ft_atoi(argv[4]) <= 0)
		err_msg("Invalid time to sleep");
	if (argv[5] && ft_atoi(argv[5]) < 0)
		err_msg("Invalid number of times each philosopher must eat");
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
	printf("%d", table->num_philo);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Please give 5 or 6 arguments! Example: ./philo number_of_philosophers \
		time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
		exit(EXIT_FAILURE);
	}
	check_args(argv);
	init_table(argv, &table);

}