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

t_philo *init_struct(int argc, char **argv)
{
	t_philo *philo;
	t_data data;
	pthread_mutex_t *forks;
	pthread_mutex_t write;
	int i;

	i = 0;
	
	pthread_mutex_init(&write, NULL);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nbr_philo);
	while (i < atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		//pthread_mutex_lock(&forks[i]);
		i++;
	}
	data.nbr_philo = atoi(argv[1]);
	data.time_to_die = atoi(argv[2]);
	data.time_to_eat = atoi(argv[3]);
	data.time_to_sleep = atoi(argv[4]);
	philo = malloc(sizeof(t_philo) * data.nbr_philo);
	i = 0;
	while (i < data.nbr_philo)
	{
		philo[i].nbr_meals = -1;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i % data.nbr_philo) + 1;
		if (argc == 6)
			philo[i].nbr_meals = atoi(argv[5]);
		philo[i].data = data;
		philo[i].forks = forks;
		philo[i].lock_write = &write;
		//pthread_mutex_init(&philo[i].nbr_meals, NULL);
		i++;
	}
	return (philo);
}

void *start_simulation(void *philo)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = (t_philo *)philo;
	//printf("%d\n", rules->nbr_philo);
	//printf("%d\n", nbr_philo);
	while (1)
	{
		if (tmp->nbr_meals == 0)
			break;
		pthread_mutex_lock(&tmp->forks[tmp->left_fork]);
		pthread_mutex_lock(tmp->lock_write);
		printf("Thread %d take a fork\n", tmp->id + 1);
		pthread_mutex_unlock(tmp->lock_write);
		pthread_mutex_lock(&tmp->forks[tmp->right_fork]);
		pthread_mutex_lock(tmp->lock_write);
		printf("Thread %d take a fork\n", tmp->id +1);
		pthread_mutex_unlock(tmp->lock_write);
		usleep(tmp->data.time_to_eat * 1000);
		pthread_mutex_lock(tmp->lock_write);
		printf("Thread %d is eating\n", tmp->id + 1);
		pthread_mutex_unlock(tmp->lock_write);
		tmp->nbr_meals--;
		pthread_mutex_lock(tmp->lock_write);
		printf("Thread %d is sleeping\n", tmp->id + 1);
		pthread_mutex_unlock(tmp->lock_write);
		usleep(tmp->data.time_to_sleep * 1000);
		pthread_mutex_lock(tmp->lock_write);
		printf("Thread %d is thinking\n", tmp->id + 1);
		pthread_mutex_unlock(tmp->lock_write);
		pthread_mutex_unlock(&tmp->forks[tmp->left_fork]);
		pthread_mutex_unlock(&tmp->forks[tmp->right_fork]);
		i++;
	}
	return (NULL);
}

void create_threads(t_philo *philo)
{
	int i;
	t_data data;

	data = philo->data;
	i = 0;
	while (i < data.nbr_philo)
	{
		//we don't know which philo we're talking about
		pthread_create(&philo[i].thread_id, NULL, &start_simulation, (void *)&philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data.nbr_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo *philo;

	if (!valid_args(argc, argv))
		printf("Error : invalid arguments.\n");
	else
	{
		philo = init_struct(argc, argv);
		//init forks
		create_threads(philo);
		//pthread_mutex_destroy(rules.forks);
		//free_all_before_exit
	}
}
