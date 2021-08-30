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

t_rules init_rules(int argc, char **argv)
{
	t_rules rules;
	int i;

	i = 0;
	//rules.nbr_meals = -1;
	rules.nbr_philo = atoi(argv[1]);
	rules.time_to_die = atoi(argv[2]);
	rules.time_to_eat = atoi(argv[3]);
	rules.time_to_sleep = atoi(argv[4]);
	rules.philo = malloc(sizeof(t_philo) * argc);
	//if (argc == 6)
//		rules.nbr_meals = atoi(argv[4]);
	return (rules);
}

void *print(void *rules)
{

	//pthread_mutex_lock(rules);

	printf("Hello world !\n");
	return (0);
}

void create_threads(t_rules *rules)
{
	int i;
	t_philo *philo;

	philo = rules->philo;
	i = 0;
	while (i < rules->nbr_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, &print, (void *)rules);
		i++;
	}
	i = 0;
	while (i < rules->nbr_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_rules rules;

	//pthread_mutex_init(&rules.nbr_meals, NULL);
	if (!valid_args(argc, argv))
	{
		printf("Error : invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	rules = init_rules(argc, argv);
	create_threads(&rules);
	//destroy before exit => free
}
