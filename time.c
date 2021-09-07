/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:54:25 by framdani          #+#    #+#             */
/*   Updated: 2021/09/07 17:22:20 by framdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec * 0.001));
}

void	sleep_without_decalage(int t_sleep)
{
	unsigned long long	start;

	start = get_current_time();
	usleep(10);
	while (get_current_time() - start < t_sleep)
		usleep(10);
}
