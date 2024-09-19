/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:01:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/19 02:07:05 by ychagri          ###   ########.fr       */
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

void	dead_action(t_philo *philo)
{
	sem_wait(philo->data->write_sem);
	printf(RED"=> %lld ms philo %d %s.\n"RESET,
		timeofday(philo->data->start_time), philo->number, DEAD);
	sem_post(philo->data->dead_sem);
	pthread_mutex_unlock(&philo->lsttime_lock);
	exit(0);
}

void	kill_proc(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		kill(data->philos[i].id, SIGTERM);
		i++;
	}
}

void	destroy_n_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nb)
		pthread_mutex_destroy(&data->philos[i].lsttime_lock);
	free(data->philos);
	sem_close(data->dead_sem);
	sem_close(data->full_sem);
	sem_close(data->write_sem);
	sem_close(data->forks);
}
