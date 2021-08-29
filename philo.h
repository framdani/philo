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

typedef struct s_philosopher
{
	int identifier;
	int time_eat;
	int time_die;
	int time_sleep;
	int nbr_meals;
} t_philosopher;

int all_digits(int argc, char **argv);
#endif
