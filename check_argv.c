/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:46:52 by framdani          #+#    #+#             */
/*   Updated: 2021/08/29 17:46:54 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_valid_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int all_digits(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
