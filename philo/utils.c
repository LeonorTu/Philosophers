/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:08:58 by jtu               #+#    #+#             */
/*   Updated: 2024/05/17 20:33:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *msg)
{
	printf("%s", msg);
	return (1);
}

void	print_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print_lock);
	time = get_current_time() - philo->start_time;
	if (!check_end(philo))
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (err_msg("Failed to get time of day"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t sleep)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep)
		usleep(500);
	return (0);
}

void	clean(t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->table->end_lock);
	pthread_mutex_destroy(&philo->table->print_lock);
	pthread_mutex_destroy(&philo->table->meal_lock);
	i = 0;
	while (i < philo->table->num_philo)
	{
		pthread_mutex_destroy(&philo->table->fork[i]);
		i++;
	}
	free(philo->table->fork);
	free(philo);
}
