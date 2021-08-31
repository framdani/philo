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

int is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		i++;
		if (strlen(str) == 1) //rpelace with ft_strlen
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
		if (!is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int valid_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || !(all_digits(argc, argv)))
		return (0);
	if (atoi(argv[1]) <= 2 || atoi(argv[2]) < 0 || atoi(argv[3]) < 0 ||
		atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && atoi(argv[5]) < 0)
		return (0);
	return (1);
}
