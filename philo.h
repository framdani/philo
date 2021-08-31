/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:43:04 by framdani          #+#    #+#             */
/*   Updated: 2021/08/29 17:45:33 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct s_data
{
	int nbr_philo;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
} t_data;

typedef struct s_philo
{
	int id;
	int left_fork;
	int right_fork;
	pthread_t thread_id;
	int		nbr_meals;
	t_data	data;
	pthread_mutex_t *forks;
	pthread_mutex_t *lock_write;
} t_philo;

int valid_args(int argc, char **argv);
#endif
