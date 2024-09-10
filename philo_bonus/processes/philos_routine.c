/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:59:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/10 23:53:58 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"


void	monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
}

void	philos_routine(t_philo *philo)
{
	pthread_t	*thread;

	pthread_create(thread, NULL, monitoring, (void *)philo);
	sem_wait(philo->data->lock_data);
	philo->last_meal = timeofday(0);
	sem_post(philo->data->lock_data);
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
		
	}
}










