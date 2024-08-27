/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:02:20 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/27 07:57:31 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->are_full);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->philos[i].l_fork);
		i++;
	}
	free(data->philos);
}

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

void	death_msg(t_data *data, int i)
{
	pthread_mutex_lock(&data->write);
	printf(MAGENTA"=> %llu ms philo %d died", timeofday(data->start_time),
		data->philos[i].number);
	destroy_mutexes(data);
	exit(0);
}

void	full_msg(t_data *data)
{
	if (data->timing.number_of_times_each_philosopher_must_eat
		&& (data->full_philos == data->number_of_philosophers))
	{
		pthread_mutex_lock(&data->write);
		printf(MAGENTA"=> %llu ms all the philos have ate at least %d times.\n",
			timeofday(data->start_time),
			data->timing.number_of_times_each_philosopher_must_eat);
		pthread_mutex_unlock(&data->are_full);
		destroy_mutexes(data);
		exit(0);
	}
	pthread_mutex_unlock(&data->are_full);
	return ;
}
