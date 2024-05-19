/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:16:31 by jtu               #+#    #+#             */
/*   Updated: 2024/05/19 16:35:14 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_table(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->end_lock);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
}

void	clean(t_philo *philo)
{
	clean_table(philo->table);
	free(philo->table->fork);
	free(philo);
}
