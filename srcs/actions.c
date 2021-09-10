/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:26:52 by framdani          #+#    #+#             */
/*   Updated: 2021/09/10 15:58:17 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(char *status, t_philo *philo)
{
	unsigned long long	timestamp;

	pthread_mutex_lock(philo->write);
	timestamp = get_current_time() - philo->start_time;
	printf("%llu %d %s\n", timestamp, philo->id, status);
	if (status[0] != 'd')
		pthread_mutex_unlock(philo->write);
}

void	ft_think(t_philo *philo)
{
	print_status("is thinking", philo);
}

void	ft_sleep(t_philo *philo)
{
	print_status("is sleeping", philo);
	sleep_without_delay(philo->time_to_sleep);
}

void	switch_fork(t_philo *ph_one, int first_fork, int second_fork)
{
	pthread_mutex_lock(&ph_one->forks[first_fork]);
	print_status("has taken a fork", ph_one);
	pthread_mutex_lock(&ph_one->forks[second_fork]);
	print_status("has taken a fork", ph_one);
	print_status("is eating", ph_one);
	pthread_mutex_lock(&ph_one->eat);
	ph_one->last_meal = get_current_time();
	ph_one->busy = 1;
	sleep_without_delay(ph_one->time_to_eat);
	pthread_mutex_unlock(&ph_one->eat);
}

void	ft_eat(t_philo *philo)
{
	switch_fork(philo, philo->l_fork, philo->r_fork);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
}
