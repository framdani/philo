/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:31:16 by framdani          #+#    #+#             */
/*   Updated: 2021/09/10 17:34:58 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philosphers(int argc, char **argv)
{
	int		i;
	int		nbr_philo;
	t_philo	*philo;

	i = -1;
	nbr_philo = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * nbr_philo);
	if (!philo)
		return (NULL);
	while (++i < nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].nbr_meals = -1;
		philo[i].count = 0;
		if (argc == 6)
			philo[i].nbr_meals = ft_atoi(argv[5]);
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % nbr_philo;
		philo[i].busy = 0;
	}
	return (philo);
}

pthread_mutex_t	*init_forks(int nbr_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(nbr_philo * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_data	*init_struct(t_data *data, int argc, char **argv)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*eat;
	int				i;

	data->nbr_philo = ft_atoi(argv[1]);
	data->philo = init_philosphers(argc, argv);
	write = malloc(sizeof(pthread_mutex_t));
	forks = init_forks(data->nbr_philo);
	eat = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!eat || !write || pthread_mutex_init(write, NULL)
		|| !forks || !data->philo)
		return (init_errors(data, write, forks, eat));
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&eat[i], NULL))
			return (init_errors(data, write, forks, eat));
		data->philo[i].forks = forks;
		data->philo[i].write = write;
		data->philo[i].eat = &eat[i];
	}
	return (data);
}
