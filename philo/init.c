/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:21:31 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/21 05:33:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timeofday(void)
{
	struct timeval	tval;
	long long		ms;

	gettimeofday(&tval, NULL);
	ms = tval.tv_sec * 1000 + tval.tv_usec / 1000;
	return (ms);
}

void	*routine(void *philo)
{
	t_philo	*tmp = (t_philo *)philo;

	if (tmp->number % 2 == 1)
		usleep(1000 * tmp->time_interv.time_to_eat);
	while (1)
	{
		printf("%lld %d is sleeping\n",timeofday() ,tmp->number);
		usleep(tmp->time_interv.time_to_sleep * 1000);
		pthread_mutex_lock(&tmp->l_fork);
		printf("%lld %d has taken a fork\n",timeofday() ,tmp->number);
		pthread_mutex_lock(&tmp->r_fork);
		printf("%lld %d has taken a fork\n",timeofday() ,tmp->number);
		printf("%lld %d is eating\n",timeofday() ,tmp->number);
		usleep(tmp->time_interv.time_to_eat * 1000);
		tmp->last_meal = timeofday();
		tmp->meals_ate++;
		pthread_mutex_unlock(&tmp->l_fork);
		pthread_mutex_unlock(&tmp->r_fork);
	}
	return (NULL);
}

void	creat_threads(t_data *data)
{
	size_t	index;

	index = 0;
	memset(data->philos, 0, sizeof(t_philo));
	while (index < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[index], NULL))
			return (ft_perror("pthread_mutex_init() has failed !!"), exit(1));
		index++;
	}
	index = 0;
	while (index < data->number_of_philosophers)
	{
		data->philos[index].number = index + 1;
		data->philos[index].time_interv = data->timing;
		data->philos[index].r_fork = data->forks[index];
		data->philos[index].l_fork = (data->forks[(index + 1) % data->number_of_philosophers]);
		data->philos[index].start_time = timeofday();
		if (pthread_create(&data->philos[index].id, NULL, &routine, (void *)&data->philos[index]))
			return (ft_perror("pthread_creat() has failed !!"), exit(1));
		index++;
	}
	index = 0;
	while (index < data->number_of_philosophers)
	{
		if (pthread_join(data->philos[index].id, NULL))
			return (ft_perror("pthread_join() has failed !!"), exit(1));
		index++;
	}
}
