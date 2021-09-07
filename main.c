/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:41:14 by framdani          #+#    #+#             */
/*   Updated: 2021/09/07 18:10:39 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*routine(void *philo)
{
	t_philo		*ph_one;
	pthread_t	t;

	ph_one = (t_philo *)philo;
	while (1)
	{
		ft_eat(ph_one);
		pthread_mutex_lock(ph_one->eat);
		if (ph_one->nbr_meals != -1)
			(ph_one->count)++;
		pthread_mutex_unlock(ph_one->eat);
		ph_one->busy = 0;
		ft_sleep(ph_one);
		ft_think(ph_one);
	}
	return (NULL);
}

int	meal_check(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->philo[0].nbr_meals != -1 && i < data->nbr_philo)
	{
		pthread_mutex_lock(data->philo[i].eat);
		if (data->philo[i].count >= data->philo[i].nbr_meals)
			count++;
		pthread_mutex_unlock(data->philo[i].eat);
		if (count == data->nbr_philo)
			return (1);
		i++;
	}
	return (0);
}

int	check_end_simulation(t_data *data)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < data->nbr_philo)
	{
		if (get_current_time() - data->philo[i].last_meal
			>= data->philo[i].time_to_die && !data->philo->busy)
		{
			print_status("died", &data->philo[i]);
			return (1);
		}
	}
	return (meal_check(data));
}

void	start_simulation(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].start_time = get_current_time();
		pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
		i++;
	}
	while (1)
	{
		if (check_end_simulation(data))
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (!valid_args(argc, argv))
		printf("Error: invalid arguments\n");
	else
	{
		data = init_struct(argc, argv);
		start_simulation(&data);
		//all the threads are close=>avoid threads leak
		//free all the pthread allocated
	//	end_simulation(&data);
	}
	return (0);
}
