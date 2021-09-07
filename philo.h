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
#include <sys/time.h>
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_philo
{
	int id;
	int l_fork;
	int r_fork;
	pthread_t thread_id;
	int	 nbr_meals;
	int count;
	pthread_mutex_t *forks;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int busy;
	unsigned long long start_time;
	unsigned long long last_meal;
	pthread_mutex_t *eat;
	pthread_mutex_t *write;
} t_philo;

typedef struct s_data
{
	t_philo *philo;
	int nbr_philo;
}t_data;

int valid_args(int argc, char **argv);
unsigned long long get_current_time(void);
void sleep_without_decalage(int t_sleep);
int ft_strlen(char *str);
long long ft_atoi(const char *str);
t_data init_struct(int argc, char **argv);
void print_status(char *status, t_philo *philo);
void switch_fork(t_philo *ph_one,int first_fork, int second_fork);
void ft_think(t_philo *philo);
void ft_sleep(t_philo *philo);
void ft_eat(t_philo *philo);
void	*routine(void *philo);
void	start_simulation(t_data *data);
void	end_simulation(t_data *data);
#endif
