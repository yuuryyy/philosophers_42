/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:59:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/11 22:26:08 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"


void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->lsttime_lock);
		if (timeofday(philo->last_meal) > philo->data->timing.time_to_die)
			dead_action(philo);
		pthread_mutex_unlock(&philo->lsttime_lock);
	}
	return (NULL);
}

void	philos_routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitoring, (void *)philo);
	pthread_detach(thread);
	pthread_mutex_lock(&philo->lsttime_lock);
	philo->last_meal = timeofday(0);
	pthread_mutex_unlock(&philo->lsttime_lock);
	if (philo->number % 2 == 0)
		usleep(philo->data->philos_nb * 20);
	while (1)
	{
		take_forks(philo);
		print_msg(philo, EATING);
		philo->last_meal = timeofday(0);
		ft_usleep(philo->data->timing.time_to_eat);
		put_forks(philo);
		philo->meals_ate++;
		meals_check(philo);
		print_msg(philo, THINKING);
		resting(philo);
	}
}










