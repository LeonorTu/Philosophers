/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:19:50 by jtu               #+#    #+#             */
/*   Updated: 2024/05/02 13:47:34 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	convert_num(const char *str, long value, int sign)
{
	while (*str >= '0' && *str <= '9')
	{
		if (value > LONG_MAX / 10)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		value *= 10;
		if (value > LONG_MAX - (*str - '0'))
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		value += *str - '0';
		str++;
	}
	if (*str && !ft_isdigit(*str))
		return (-1);
	return (value);
}

/**
 * The atoi() function converts the initial portion of the
 * string pointed to by str to int representation.
*/
int	ft_atoi(const char *str)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	value = convert_num(str, value, sign);
	return (sign * value);
}