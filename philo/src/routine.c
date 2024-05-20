/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:21:17 by jtu               #+#    #+#             */
/*   Updated: 2024/05/20 13:47:58 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->must_eat == 0)
		return (arg);
	if (philo->id % 2 == 1)
	{
		ft_think(philo);
		ft_usleep(philo, philo->table->time_to_eat - 2);
	}
	while (!check_end(philo))
	{
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_think(philo))
			break ;
	}
	if (philo->fork_l)
		pthread_mutex_unlock(philo->fork_left);
	if (philo->fork_r)
		pthread_mutex_unlock(philo->fork_right);
	return (arg);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	philo->fork_r = 1;
	print_msg(philo, "has taken a fork");
	if (philo->table->num_philo == 1)
		return (1);
	pthread_mutex_lock(philo->fork_left);
	philo->fork_l = 1;
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (ft_usleep(philo, philo->table->time_to_eat))
		return (1);
	pthread_mutex_unlock(philo->fork_left);
	philo->fork_l = 0;
	pthread_mutex_unlock(philo->fork_right);
	philo->fork_r = 0;
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (check_end(philo))
		return (1);
	print_msg(philo, "is thinking");
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	if (ft_usleep(philo, philo->table->time_to_sleep))
		return (1);
	return (0);
}
