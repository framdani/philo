/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:41:14 by framdani          #+#    #+#             */
/*   Updated: 2021/09/09 18:03:28 by framdani         ###   ########.fr       */
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
		pthread_mutex_lock(ph_one->eat);
		if (ph_one->nbr_meals != -1)
			(ph_one->count)++;
		ph_one->busy = 0;
		pthread_mutex_unlock(ph_one->eat);
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
		if (pthread_mutex_lock(data->philo[i].eat))
			return (error_mutex(data, "lock failed"));
		if (data->philo[i].count >= data->philo[i].nbr_meals)
			count++;
		if (pthread_mutex_unlock(data->philo[i].eat))
			return (error_mutex(data, "unlock failed"));
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
		if (pthread_mutex_lock(data->philo[i].eat))
			return (error_mutex(data, "lock failed"));
		if (get_current_time() - data->philo[i].last_meal
			> (unsigned long long)data->philo[i].time_to_die
			&& !data->philo[i].busy)
		{
			print_status("died", &data->philo[i]);
			return (1);
		}
		if (pthread_mutex_unlock(data->philo[i].eat))
			return (error_mutex(data, "lock failed"));
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
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]))
		{
			ft_error(data, "pthread create failed!");
			return ;
		}
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
	t_data	*data;
	int		i;

	i = 0;
	if (!valid_args(argc, argv))
		printf("Error: invalid arguments\n");
	else
	{
		data = init_struct(argc, argv);
		if (!data)
			return (1);
		start_simulation(data);
	}
	return (0);
}
