/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:42:17 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/14 04:22:53 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_sem(t_data *data)
{
	// printf("%p\n", data->philos);
	
	// if (sem_unlink("forks") == -1)
	// 	return (ft_perror("sem_unlink() has failed ."), 1);
	// if (sem_unlink("dead") == -1)
	// 	return (ft_perror("sem_unlink() has failed ."), 1);
	// if (sem_unlink("print") == -1)
	// 	return (ft_perror("sem_unlink() has failed ."), 1);
	// if (sem_unlink("full") == -1)
	// 	return (ft_perror("sem_unlink() has failed ."), 1);
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0700, data->philos_nb);
	if (!data->forks)
		return (ft_perror("sem_open() has failed ."), 1);
	data->dead_sem = sem_open("dead", O_CREAT | O_EXCL, 0600, 1);
	if (!data->dead_sem)
		return (ft_perror("sem_open() has failed ."), 1);
	data->write_sem = sem_open("print", O_CREAT | O_EXCL, 0600, 1);
	if (!data->write_sem) 
		return (ft_perror("sem_open() has failed ."), 1);
	data->full_sem = sem_open("full", O_CREAT | O_EXCL, 0600, data->meals_nb);
	if (!data->full_sem)
		return (ft_perror("sem_open() has failed ."), 1);
	return (0);
}

int	init_proc(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_nb);
	while (i < data->meals_nb)
		sem_wait(data->full_sem);
	sem_wait(data->dead_sem);
	i = 0;
	data->start_time = timeofday(0);
	
	while (i < data->philos_nb)
	{
		data->philos[i].number = i + 1;
		data->philos[i].meals_ate = 0;
		if (pthread_mutex_init(&data->philos[i].data_lock, NULL) == -1)
			return (ft_perror("pthread_mutex_init() has failed ."), 1);
		if (pthread_mutex_init(&data->philos[i].lsttime_lock, NULL) == -1)
			return (ft_perror("pthread_mutex_init() has failed ."), 1);
		data->philos[i].id = fork();
		if (data->philos[i].id == -1)
			return (ft_perror("fork() has failed ."), 1);
		else if (data->philos[i].id > 0)
		{
			philos_routine(&data->philos[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}
