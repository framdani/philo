/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:41:14 by framdani          #+#    #+#             */
/*   Updated: 2021/09/10 16:00:19 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *philo)
{
	t_philo		*ph_one;

	ph_one = (t_philo *)philo;
	if (ph_one->id % 2 == 0)
		usleep(200);
	while (ph_one->nbr_meals != 0)
	{
		ft_eat(ph_one);
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
		if (data->philo[i].count >= data->philo[i].nbr_meals)
			count++;
		if (count == data->nbr_philo)
			return (1);
		i++;
	}
	return (0);
}

int	end_simulation(t_data *data)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < data->nbr_philo)
	{	
		if (!data->philo[i].busy)
		{
			if (get_current_time() - data->philo[i].last_meal
				>= (unsigned long long)data->philo[i].time_to_die)
			{
				pthread_mutex_lock(data->philo[i].eat);
				print_status("died", &data->philo[i]);
				return (1);
			}
		}
	}
	return (meal_check(data));
}

void	start_simulation(t_data *data)
{
	int				i;
	t_philo			*philo;

	philo = data->philo;
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].start_time = get_current_time();
		philo[i].last_meal = philo[i].start_time;
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]))
		{
			printf("pthread create failed\n");
			return ;
		}
		i++;
	}
	while (1)
	{
		if (end_simulation(data))
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!valid_args(argc, argv))
		printf("Error: invalid arguments\n");
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
		{
			printf("Malloc failed\n");
			return (1);
		}
		data = init_struct(data, argc, argv);
		if (!data)
			return (1);
		start_simulation(data);
	}
	return (0);
}
