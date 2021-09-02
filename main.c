/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:41:14 by framdani          #+#    #+#             */
/*   Updated: 2021/08/29 17:41:17 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>

t_data init_struct(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_mutex_t *state = malloc(1*sizeof(pthread_mutex_t));
	int i;

	i = 0;
	data.nbr_philo = atoi(argv[1]);
	forks = (pthread_mutex_t *)malloc( data.nbr_philo * sizeof(pthread_mutex_t));
	while (i < data.nbr_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	philo = (t_philo *)malloc(data.nbr_philo * sizeof(t_philo));
	i = 0;
	while (i < data.nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = atoi(argv[2]);
		philo[i].time_to_eat = atoi(argv[3]);
		philo[i].time_to_sleep = atoi(argv[4]);
		philo[i].nbr_meals = -1;
		if (argc == 6)
			philo[i].nbr_meals = atoi(argv[5]);
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data.nbr_philo;
		philo[i].forks = forks;
		philo[i].state = state;
		i++;
	}
	data.philo = philo;
	return (data);
}

void *routine(void *philo)
{
	t_philo *ph_one;
	int tmp;

	ph_one = (t_philo *)philo;
	while (1)
	{
		//everyone takes a fork
		if (ph_one->id % 2 == 1)
		{
		pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
		printf("Thread %d has taken left fork (%d). \n", ph_one->id, ph_one->left_fork);
		pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
		printf("Thread %d has taken right fork. (%d)\n", ph_one->id, ph_one->right_fork);
		}
		else {
		
		pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
		printf("Thread %d has taken left fork (%d). \n", ph_one->id, ph_one->right_fork);
		pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
		printf("Thread %d has taken a fork. (%d)\n", ph_one->id, ph_one->left_fork);
		printf("Thread %d is eating.\n", ph_one->id);
		}
		usleep(ph_one->time_to_eat * 1000);
		pthread_mutex_unlock(&ph_one->forks[ph_one->right_fork]);
		pthread_mutex_unlock(&ph_one->forks[ph_one->left_fork]);
		usleep(ph_one->time_to_sleep * 1000);
		
		//pthread_mutex_lock(ph_one->state);
		//printf("Thread %d is eating. \n", ph_one->id);
		//pthread_mutex_unlock(ph_one->state);
	}
	return (NULL);
}

void start_simulation(t_data *data)
{
	int i;
	t_philo *philo;

	philo = data->philo;
	i = 0;
	while (i < data->nbr_philo)
	{
		//we don't know which philo we're talking about
		pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
		//usleep(100);
		//continue the execution
		//printf("Thread %d is created \n", i+1);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data data;

	if (!valid_args(argc, argv))
		printf("Error : invalid arguments.\n");
	else
	{
		//pthread_mutex_init(&check_meal, NULL);
		data = init_struct(argc, argv);
		//init forks
		start_simulation(&data); // initialize last-meal
		//pthread_mutex_destroy(rules.forks);
		//free_all_before_exit
	}
}
