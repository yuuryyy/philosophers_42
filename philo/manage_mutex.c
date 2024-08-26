/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_locks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:14:57 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/26 04:22:45 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	index;

	index = 0;
	if (pthread_mutex_init(&data->write, NULL))
		return(ft_perror("pthread_mutex_init() has failed !!"), 1);
	if (pthread_mutex_init(&data->are_full, NULL))
		return(ft_perror("pthread_mutex_init() has failed !!"), 1);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return(ft_perror("pthread_mutex_init() has failed !!"), 1);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (ft_perror("failed to allocate philos !!"), 1);
	while (index < data->number_of_philosophers)
	{
		data->philos[index].number = index + 1;
		data->philos[index].meals_ate = 0;
		data->philos[index].r_fork = NULL;
		data->philos[index].data = data;
		if (pthread_mutex_init(&data->philos[index].l_fork, NULL))
			return (ft_perror("pthread_mutex_init() has failed !!"), 1);
		data->philos[index].r_fork = &data->philos[(index + 1) % data->number_of_philosophers].l_fork;
		index++;
	}
	return (0);
}

void	write_lock(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	printf("=> %llu ms philo %d %s.\n", timeofday(philo->data->start_time), philo->number, msg);
	pthread_mutex_unlock(&philo->data->write);
}

void	fork_lock(t_philo *philo)
{
		pthread_mutex_lock(&philo->l_fork);
		write_lock(philo, fork);
		pthread_mutex_lock(philo->r_fork);
		write_lock(philo, fork);
}

void	fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	meals_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->are_full);
	philo->data->full_philos++;
	pthread_mutex_unlock(&philo->data->are_full);
}
