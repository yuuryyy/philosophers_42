/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:21:31 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/27 07:54:28 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	monitor_threads(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (timeofday(data->philos[i].last_meal) > data->timing.time_to_die)
			death_msg(data, i);
		pthread_mutex_unlock(&data->dead_lock);
		full_msg(data);
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
	return (0);
}

void	routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(&tmp->data->dead_lock);
	tmp->last_meal = timeofday(0);
	pthread_mutex_unlock(&tmp->data->dead_lock);
	if (tmp->number % 2 == 0)
		usleep(tmp->data->number_of_philosophers * 20);
	while (1)
	{
		fork_lock(tmp);
		write_lock(tmp, EATING);
		pthread_mutex_lock(&tmp->data->dead_lock);
		tmp->last_meal = timeofday(0);
		pthread_mutex_unlock(&tmp->data->dead_lock);
		ft_usleep(tmp->data->timing.time_to_eat);
		fork_unlock(tmp);
		tmp->meals_ate++;
		meals_lock(tmp);
		write_lock(tmp, THINKING);
		write_lock(tmp, SLEEPING);
		ft_usleep(tmp->data->timing.time_to_sleep);
	}
}

int	creat_threads(t_data *data)
{
	int	index;

	index = 0;
	data->full_philos = 0;
	data->start_time = timeofday(0);
	while (index < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[index].id, NULL,
				(void *)&routine, (void *)&data->philos[index]))
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
	return (0);
}
