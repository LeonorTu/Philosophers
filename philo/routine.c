/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:21:17 by jtu               #+#    #+#             */
/*   Updated: 2024/05/15 16:03:59 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_think(philo);
	while (!check_end(philo))
	{
		ft_eat(philo);
		ft_think(philo);
		ft_sleep(philo);
	}
	return (arg);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (err_msg("Failed to get time of day"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print_lock);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	ft_eat(t_philo *philo)
{
	int	eating;

	eating = 0;
	pthread_mutex_lock(philo->fork_right);
	print_msg(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->fork_left) != 0)
	{
		printf("philo 5");
		ft_think(philo);
		return ;
	}
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	ft_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

int	ft_usleep(size_t sleep)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep)
		usleep(500);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}