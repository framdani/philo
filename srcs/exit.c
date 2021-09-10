/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:30:19 by framdani          #+#    #+#             */
/*   Updated: 2021/09/10 17:31:29 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*init_errors(t_data *data, pthread_mutex_t *w, pthread_mutex_t *forks,
		pthread_mutex_t *eat)
{
	int	i;

	i = -1;
	if (data)
	{
		free(eat);
		free(w);
		free(forks);
		pthread_mutex_destroy(w);
		while (++i < data->nbr_philo)
			pthread_mutex_destroy(&forks[i]);
		free(data->philo);
		free(data);
	}
	printf("malloc/mutex init failed\n");
	return (NULL);
}
