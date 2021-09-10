/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:46:52 by framdani          #+#    #+#             */
/*   Updated: 2021/09/10 12:52:50 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long long	ft_atoi(const char *str)
{
	unsigned long long	a;
	int					sign;

	a = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		str++;
		sign = (-1);
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + *str - '0';
		str++;
	}
	a = a * sign;
	return (a);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		i++;
		if (ft_strlen(str) == 1)
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

int	all_digits(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || !(all_digits(argc, argv)))
		return (0);
	if (ft_strlen(argv[2]) >= 19 || ft_strlen(argv[3]) >= 19
		|| ft_strlen(argv[4]) >= 19)
		return (0);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && (ft_strlen(argv[5]) >= 19 || ft_atoi(argv[5]) < 0))
		return (0);
	return (1);
}
