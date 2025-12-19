/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:08:10 by jakrajic          #+#    #+#             */
/*   Updated: 2025/12/18 19:08:12 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	char_control(int argc, char **argv)
{
	int		i;
	char	*str;

	if (argc < 5 || argc > 6)
		return (display_error("Invalid number of arguments"), -1);
	i = 0;
	while (++i < argc)
	{
		str = argv[i];
		while (*str != '\0')
		{
			if (!is_whitespace(*str) && !is_digit(*str)
				&& *str != '+')
				return (display_error("Input includes invalid characters"), -1);
			str++;
		}
	}
	return (0);
}

static int	number_control(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (my_atoi(argv[i]) == -1)
			return (-1);
	}
	return (0);
}

int	input_control(int argc, char **argv)
{
	if ((char_control(argc, argv) == -1) || (number_control(argc, argv) == -1))
		return (-1);
	return (0);
}
