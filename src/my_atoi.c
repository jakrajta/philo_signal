/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:10:59 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/18 19:11:26 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *str)
{
	long	number;

	number = 0;
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!is_digit(*str))
			return (display_error("Input includes invalid characters atoi."),
				-1);
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number == 0)
		return (display_error("Input must > 0"), -1);
	if (number > INT_MAX)
		return (display_error("Input is not INT type."), -1);
	return ((int)number);
}
