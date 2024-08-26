/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:21:31 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/26 04:53:52 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timeofday(long long start)
{
	struct timeval	tval;

	if (gettimeofday(&tval, NULL))
		return (ft_perror("gettimeofday() has failed !!"), exit (1), 0);
	return (((tval.tv_sec * 1000) + (tval.tv_usec / 1000)) - start);
}

void	ft_usleep(long long time)
{
	long long start;

	start = timeofday(0);
	while (timeofday(start) < time)
		usleep(100);
}

int	monitor_threads(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&data->dead_lock);
		if (timeofday(data->philos[i].last_meal) > data->timing.time_to_die)
		{
			pthread_mutex_lock(&data->write);
			printf(MAGENTA"%llu ms %d died", timeofday(data->start_time) , data->philos[i].number);
			exit (0);
		}
		pthread_mutex_unlock(&data->dead_lock);
		if (data->timing.number_of_times_each_philosopher_must_eat &&( data->full_philos == data->number_of_philosophers))
			return (printf(MAGENTA"%llu ms all the philos have ate at least %d\n",
				timeofday(data->start_time),
				data->timing.number_of_times_each_philosopher_must_eat), 1);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
	return (0);
}


void	routine(void *philo)
{
	t_philo	*tmp = philo;

	if (!(tmp->number % 2))
		usleep(250);
		pthread_mutex_lock(&tmp->data->dead_lock);

	tmp->last_meal = timeofday(0);
		pthread_mutex_unlock(&tmp->data->dead_lock);

	while (1)
	{
		fork_lock(tmp);
		write_lock(tmp, eating);
		pthread_mutex_lock(&tmp->data->dead_lock);
	
		tmp->last_meal = timeofday(0);
		pthread_mutex_unlock(&tmp->data->dead_lock);
		
		ft_usleep(tmp->data->timing.time_to_eat);
		fork_unlock(tmp);
		tmp->meals_ate++;
		if (tmp->data->timing.number_of_times_each_philosopher_must_eat &&
			(tmp->meals_ate == tmp->data->timing.number_of_times_each_philosopher_must_eat))
			meals_lock(tmp);
		write_lock(tmp, thinking);
		write_lock(tmp, sleeping);
		ft_usleep(tmp->data->timing.time_to_sleep);
	}
}

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
}

int	creat_threads(t_data *data)
{
	int	index;

	index = 0;
	data->full_philos = 0;
	init_mutexes(data);
	data->start_time = timeofday(0);
	while (index < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[index].id, NULL, (void *)&routine, (void *)&data->philos[index]))
			return (ft_perror("pthread_creat() has failed !!"), 1);
		index++;
	}
	index = 0;
	while (index < data->number_of_philosophers)
	{ 
		if (pthread_detach(data->philos[index].id))
			return (ft_perror("pthread_detach() has failed !!"), 1);
		index++;
	}
	usleep(200);
	monitor_threads(data);
	destroy_mutexes(data);
	return (0);
}
