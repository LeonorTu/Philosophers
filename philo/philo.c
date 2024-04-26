/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:45 by jtu               #+#    #+#             */
/*   Updated: 2024/04/26 14:44:00 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 || argc != 6)
	{
		printf("Please give 5 or 6 arguments! Example: ./philo number_of_philosophers \
		time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
		exit(EXIT_FAILURE);
	}
	parse();
	

}