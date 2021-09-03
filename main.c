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

void print_status(char *status, t_philo *philo)
{
	pthread_mutex_lock(&philo->write);//I need to change time
	printf("Thread %d %s\n", philo->id, status);
	pthread_mutex_unlock(&philo->write);
//lock write
//print philo.id
//print currrent_time
//unlock write
}

t_data init_struct(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_mutex_t write;
	pthread_mutex_t *state = malloc(1*sizeof(pthread_mutex_t));
	int i;

	i = 0;
	data.nbr_philo = atoi(argv[1]);
	forks = (pthread_mutex_t *)malloc( data.nbr_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&write, NULL);
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
		philo[i].write = write;
		i++;
	}
	data.philo = philo;
	return (data);
}

void *routine(void *philo)
{
	t_philo *ph_one;
	//int tmp;
//	int swap = 0;

	ph_one = (t_philo *)philo;
	while (1)
	{
		//everyone takes a fork
		if (ph_one->id % 2 != 0)
		//if (swap == 0)
		{
		pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
		print_status("has taken a fork", ph_one);
		//printf("Thread %d has taken left fork (%d). \n", ph_one->id, ph_one->left_fork);
		pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
		print_status("has taken a fork", ph_one);
		//printf("Thread %d has taken right fork. (%d)\n", ph_one->id, ph_one->right_fork);
		//printf("Thread %d is eating.\n", ph_one->id);
		print_status("is eating", ph_one);
	//	swap = 1;
		}
		else {
		
		pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
		print_status("has taken a fork", ph_one);
		//printf("Thread %d has taken left fork (%d). \n", ph_one->id, ph_one->right_fork);
		pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
		print_status("has taken a fork", ph_one);
		//printf("Thread %d has taken a fork. (%d)\n", ph_one->id, ph_one->left_fork);
		//printf("Thread %d is eating.\n", ph_one->id);
		print_status("is eating", ph_one);
		}
	//	swap = 1;
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

	printf("%llu\n", get_current_time());
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
