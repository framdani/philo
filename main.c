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
#include <time.h>
#include <unistd.h>

void print_status(char *status, t_philo *philo)
{
	unsigned long long timestamp;

	pthread_mutex_lock(&philo->write);
	timestamp = get_current_time() - philo->start_time;
	printf("%llu %d %s\n", timestamp, philo->id, status);
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
	pthread_mutex_t eat;
	pthread_mutex_t *state = malloc(sizeof(pthread_mutex_t));
	int i;

	i = 0;
	data.nbr_philo = atoi(argv[1]);
	forks = (pthread_mutex_t *)malloc( data.nbr_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&write, NULL);
	pthread_mutex_init(&eat, NULL);
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
		philo[i].eat = eat;
		philo[i].last_meal = get_current_time();
		i++;
	}
	data.philo = philo;
	return (data);
}

void starvation_check(t_data *data)
{
	int i;
	unsigned long long current = get_current_time();

	i = 0;
	while (i < data->nbr_philo)
	{
		if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
			print_status("died", &data->philo[i]);
		i++;
	}
}

void *routine(void *philo)
{
	t_philo *ph_one;

	ph_one = (t_philo *)philo;
	while (1)
	{//if ph->nbr_meal = nbr_meals
		//everyone takes a fork
		if (ph_one->id % 2 != 0)//this is not a valid solution
		{	
			pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
			print_status("has taken a left fork", ph_one);
			pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
			print_status("has taken a right fork", ph_one);
			print_status("is eating", ph_one);
		}
		else
		{
			pthread_mutex_lock(&ph_one->forks[ph_one->right_fork]);
			print_status("has taken a right fork", ph_one);
			pthread_mutex_lock(&ph_one->forks[ph_one->left_fork]);
			print_status("has taken a left fork", ph_one);
			print_status("is eating", ph_one);
		}
		//update the time of last_time_eat
		pthread_mutex_lock(&ph_one->eat);
		ph_one->last_meal = get_current_time();
		pthread_mutex_unlock(&ph_one->eat);
		usleep(ph_one->time_to_eat * 1000);
		pthread_mutex_unlock(&ph_one->forks[ph_one->right_fork]);
		pthread_mutex_unlock(&ph_one->forks[ph_one->left_fork]);
		/*print_status("is sleeping", ph_one);
		usleep(ph_one->time_to_sleep * 1000);
		print_status("is thinking", ph_one);*/
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
		philo[i].start_time = get_current_time();
			pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
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
		printf("Error: invalid arguments.\n");
	else
	{
		data = init_struct(argc, argv);
		start_simulation(&data); // initialize last-meal
		//pthread_mutex_destroy(rules.forks);
		//free_all_before_exit
	}
}

//solution correcte mais des philosophes attendent plus que d'autres en moyenne.
//they wait then which conclude to starving
//next_step => starvation check
//			=> check if all the philos already take the meal
