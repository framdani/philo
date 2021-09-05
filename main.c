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

void is_starving(t_philo *ph_one)
{

	if (get_current_time() - ph_one->last_meal >= ph_one->time_to_die)
	{
		print_status("died", ph_one);
	}
}

void switch_fork(t_philo *ph_one,int first_fork, int second_fork)
{
	pthread_mutex_lock(&ph_one->forks[first_fork]);
	print_status("has taken a fork", ph_one);
	pthread_mutex_lock(&ph_one->forks[second_fork]);
	print_status("has taken a fork", ph_one);
	print_status("is eating", ph_one);
}

void sleep_without_decalage(long long t_sleep)
{
	long long start = get_current_time();
	do {
		usleep(10);
	}while (get_current_time() - start < t_sleep);	
}

void *routine(void *philo)
{
	t_philo *ph_one;

	ph_one = (t_philo *)philo;
	while (ph_one->nbr_meals == -1 || ph_one->nbr_meals != 0)
	{
		//everyone takes a fork
		if (ph_one->id % 2)//this is not a valid solution
			switch_fork(ph_one, ph_one->left_fork, ph_one->right_fork);
		else
			switch_fork(ph_one, ph_one->right_fork, ph_one->left_fork);
		//update the time of last_time_eat
		sleep_without_decalage(ph_one->time_to_eat); //convert ms en us
		pthread_mutex_unlock(&ph_one->forks[ph_one->right_fork]);
		pthread_mutex_unlock(&ph_one->forks[ph_one->left_fork]);
		pthread_mutex_lock(&ph_one->eat);
		ph_one->last_meal = get_current_time();
		//update number of meals taken for each philo
		if (ph_one->nbr_meals != -1)
			(ph_one->nbr_meals)--;
		pthread_mutex_unlock(&ph_one->eat);
		//sleep_without_decalage(ph_one->time_to_eat); //convert ms en us
		//pthread_mutex_unlock(&ph_one->forks[ph_one->right_fork]);
	//	pthread_mutex_unlock(&ph_one->forks[ph_one->left_fork]);
		print_status("is sleeping", ph_one);
		sleep_without_decalage(ph_one->time_to_sleep);
		print_status("is thinking", ph_one);
	}
	return (NULL);
}

void start_simulation(t_data *data)
{
	int i;
	t_philo *philo;
	pthread_t t;

	philo = data->philo;
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].start_time = get_current_time();//ms
			pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
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
//delete decalage => done 
