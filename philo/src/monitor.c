/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:03:04 by jtu               #+#    #+#             */
/*   Updated: 2024/05/19 16:51:11 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_philo)
	{
		pthread_mutex_lock(&philo->table->meal_lock);
		if (get_current_time() - philo[i].last_meal \
		>= philo->table->time_to_die)
		{
			print_msg(&philo[i], "died");
			pthread_mutex_lock(&philo->table->end_lock);
			philo->table->end = 1;
			pthread_mutex_unlock(&philo->table->end_lock);
			pthread_mutex_unlock(&philo->table->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->meal_lock);
		i++;
	}
	return (0);
}

int	philo_finished(t_philo *philo)
{
	int	i;
	int	finished;

	finished = 0;
	if (philo->table->must_eat == -1)
		return (-1);
	i = 0;
	while (i < philo->table->num_philo)
	{
		pthread_mutex_lock(&philo->table->meal_lock);
		if (philo[i].meals_eaten >= philo->table->must_eat)
			finished++;
		pthread_mutex_unlock(&philo->table->meal_lock);
		i++;
	}
	if (finished == philo->table->num_philo || philo->table->must_eat == 0)
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
			break ;
	return (arg);
}

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end_lock);
	if (philo->table->end == 1)
	{
		pthread_mutex_unlock(&philo->table->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->end_lock);
	return (0);
}
