/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:42:17 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/15 23:16:14 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_sem(t_data *data)
{
	sem_t	*err;

	err = (sem_t *)0;
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("full");
	sem_unlink("forks");
	err = data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->philos_nb);
	if (err == SEM_FAILED)
		return (ft_perror("sem_open() has failed ."), 1);
	err = data->dead_sem = sem_open("dead", O_CREAT | O_EXCL, 0644, 1);
	if (err == SEM_FAILED)
		return (ft_perror("sem_open() has failed ."), 1);
	err = data->write_sem = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (err == SEM_FAILED)
		return (ft_perror("sem_open() has failed ."), 1);
	// printf("heere <<%p>>\n",data->full_sem);
	if (data->meals_nb)
	{
		err = data->full_sem = sem_open("full", O_CREAT | O_EXCL, 0644, data->philos_nb);
		if (err == SEM_FAILED)
			return (ft_perror("sem_open() has failed ."), 1);	
	}
	// printf("heere <<%p>>\n",data->full_sem);
	return (0);
}

int	init_proc(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_nb);
	printf("heere <<%p>>\n",data->full_sem);
	printf("heere <<%d>>\n",sem_wait(data->full_sem));
	if (data->meals_nb)
	{
		while (sem_wait(data->full_sem) == 0 && i < data->philos_nb)
			i++;
	}
	if (sem_wait(data->dead_sem) != 0)
		return (ft_perror("sem_wait() has failed ."), 1);
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
