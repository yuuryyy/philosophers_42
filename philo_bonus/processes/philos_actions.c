/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:11:26 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/11 23:09:09 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print_msg(t_philo *philo, char *msg)
{
	sem_wait(philo->data->write_sem);
	printf("=> %lld ms philo %d %s.\n", timeofday(philo->data->start_time), philo->number, msg);
	sem_post(philo->data->write_sem);
}

void	take_forks(t_philo *philo)
{
	fprintf(stderr,"<<%p>>\n",philo->data->forks);
	sem_wait(philo->data->forks);
	print_msg(philo, FORK);
	sem_wait(philo->data->forks);
	print_msg(philo, FORK);
}
void	put_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	meals_check(t_philo *philo)
{
	if (philo->data->meals_nb && philo->data->meals_nb == philo->meals_ate)
		sem_post(philo->data->full_sem);
}

void	resting(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	ft_usleep(philo->data->timing.time_to_sleep);
}
