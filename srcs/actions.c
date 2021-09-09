/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <framdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:26:52 by framdani          #+#    #+#             */
/*   Updated: 2021/09/09 18:03:08 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(char *status, t_philo *philo)
{
	unsigned long long	timestamp;

	if (pthread_mutex_lock(philo->write))
	{
		printf("Lock failed\n");
		return ;
	}
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
	sleep_without_decalage(philo->time_to_sleep);
}

void	switch_fork(t_philo *ph_one, int first_fork, int second_fork)
{
	if (pthread_mutex_lock(&ph_one->forks[first_fork]))
	{
		printf("lock failed\n");
		return ;
	}
	print_status("has taken a fork", ph_one);
	if (pthread_mutex_lock(&ph_one->forks[second_fork]))
	{
		printf("lock failed\n");
		return ;
	}
	print_status("has taken a fork", ph_one);
	print_status("is eating", ph_one);
	ph_one->last_meal = get_current_time();
	ph_one->busy = 1;
	sleep_without_decalage(ph_one->time_to_eat);
}

void	ft_eat(t_philo *philo)
{
	switch_fork(philo, philo->l_fork, philo->r_fork);
	if (pthread_mutex_unlock(&philo->forks[philo->l_fork])
		|| pthread_mutex_unlock(&philo->forks[philo->r_fork]))
	{
		printf("unlock failed\n");
		return ;
	}
}