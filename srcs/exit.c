/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:30:19 by framdani          #+#    #+#             */
/*   Updated: 2021/09/09 17:54:47 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->philo)
		{
			if (data->philo[0].write)
				pthread_mutex_destroy(data->philo[0].write);
			if (data->philo[0].eat)
				pthread_mutex_destroy(data->philo[0].eat);
			if (data->philo[0].forks)
			{
				while (i < data->nbr_philo)
				{
					pthread_mutex_destroy(&data->philo[0].forks[i]);
					i++;
				}
			}
			free(data->philo);
		}
		free(data);
	}
}

int	error_mutex(t_data *data, char *str)
{
	printf("%s\n", str);
	ft_free(data);
	return (1);
}

void	*ft_error(t_data *data, char *str)
{
	printf("%s\n", str);
	ft_free(data);
	return (NULL);
}
