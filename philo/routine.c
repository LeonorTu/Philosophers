/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:21:17 by jtu               #+#    #+#             */
/*   Updated: 2024/05/10 16:46:09 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	printf("%zu %d %s\n", time, philo->id, msg);
}

int	ft_eat(t_philo *philo)
{
	int	fork_right;
	int	fork_left;

	fork_right = philo->id;
	pthread_mutex_lock(&table->fork[fork_right]);
	print_msg(philo, "has taken a fork");
	fork_left = (philo->id + 1) % table->num_philo;
	pthread_mutex_lock(&table->fork[fork_left]);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->fork[fork_right]);
	pthread_mutex_unlock(&table->fork[fork_left]);

}

int	ft_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

int	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	//usleep(table->time_to_sleep);  //improve
}