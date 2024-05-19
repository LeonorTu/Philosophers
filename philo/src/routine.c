/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:21:17 by jtu               #+#    #+#             */
/*   Updated: 2024/05/19 17:12:50 by jtu              ###   ########.fr       */
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
		ft_sleep(philo);
		ft_think(philo);
	}
	return (arg);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_msg(philo, "has taken a fork");
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_lock(philo->fork_left);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	ft_usleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void	ft_think(t_philo *philo)
{
	if (check_end(philo))
		return ;
	print_msg(philo, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo, philo->table->time_to_sleep);
}
