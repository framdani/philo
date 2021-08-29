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

int main(int argc, char **argv)
{
	if (argc < 6 || argc > 7)
	{
		printf("Error : Invalid number of arguments \n");
		exit (EXIT_FAILURE);
	}
	if (!all_digits(argc, argv))
	{
		printf("Errro : Arguments must all be digits \n");
		exit (EXIT_FAILURE);
	}
}
