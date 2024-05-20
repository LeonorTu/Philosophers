/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:08:58 by jtu               #+#    #+#             */
/*   Updated: 2024/05/20 11:02:57 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	err_msg(char *msg)
{
	printf("%s", msg);
	return (EXIT_FAILURE);
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

int	ft_usleep(t_philo *philo, size_t sleep)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep)
	{
		if (check_end(philo))
			return (1);
		usleep(500);
	}
	return (0);
}
