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
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct s_philo
{
	int id;
	int left_fork;
	int right_fork;
	pthread_t thread_id;
	int	 nbr_meals;
	pthread_mutex_t *forks;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	pthread_mutex_t *state;
} t_philo;

typedef struct s_data
{
	t_philo *philo;
	int nbr_philo;
}t_data;

int valid_args(int argc, char **argv);
#endif
