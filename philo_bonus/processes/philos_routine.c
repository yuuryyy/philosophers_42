/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:59:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/19 02:06:18 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*monitoring(void *arg)
{
	t_philo		*philo;
	long long	time_since_last_meal;	

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->lsttime_lock);
		time_since_last_meal = timeofday(0) - philo->last_meal;
		if (time_since_last_meal > philo->data->timing.time_to_die)
		{
			dead_action(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->lsttime_lock);
		usleep(100);
	}
	return (NULL);
}

void	philos_routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_mutex_lock(&philo->lsttime_lock);
	philo->last_meal = timeofday(0);
	pthread_mutex_unlock(&philo->lsttime_lock);
	if (philo->number % 2 == 0)
		usleep(philo->data->philos_nb * 20);
	pthread_create(&thread, NULL, monitoring, (void *)philo);
	pthread_detach(thread);
	while (1)
	{
		take_forks(philo);
		print_msg(philo, EATING);
		pthread_mutex_lock(&philo->lsttime_lock);
		philo->last_meal = timeofday(0);
		pthread_mutex_unlock(&philo->lsttime_lock);
		ft_usleep(philo->data->timing.time_to_eat);
		put_forks(philo);
		philo->meals_ate++;
		meals_check(philo);
		print_msg(philo, THINKING);
		resting(philo);
	}
}
