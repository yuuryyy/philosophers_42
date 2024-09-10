/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:01:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/10 20:57:35 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long long	timeofday(long long start)
{
	struct timeval	tval;

	if (gettimeofday(&tval, NULL))
		return (ft_perror("gettimeofday() has failed !!"), exit (1), 0);
	return (((tval.tv_sec * 1000) + (tval.tv_usec / 1000)) - start);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = timeofday(0);
	while (timeofday(start) < time)
		usleep(100);
}
