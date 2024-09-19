/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:42:17 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/19 02:03:03 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_sem(t_data *data)
{
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("full");
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->philos_nb);
	if (!data->forks)
		return (ft_perror("sem_open() has failed ."), 1);
	data->dead_sem = sem_open("dead", O_CREAT | O_EXCL, 0644, 1);
	if (!data->dead_sem)
		return (ft_perror("sem_open() has failed ."), 1);
	data->write_sem = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (!data->write_sem)
		return (ft_perror("sem_open() has failed ."), 1);
	if (data->meals_nb)
	{
		data->full_sem = sem_open("full", O_CREAT | O_EXCL,
				0644, data->philos_nb);
		if (!data->full_sem)
			return (ft_perror("sem_open() has failed ."), 1);
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->philos_nb);
	if (data->meals_nb)
	{
		while (++i < data->philos_nb)
		{
			if (sem_wait(data->full_sem) != 0)
				return (ft_perror("sem_wait() has failed ."), 1);
		}
	}
	if (sem_wait(data->dead_sem) != 0)
		return (ft_perror("sem_wait() has failed ."), 1);
	i = -1;
	while (++i < data->philos_nb)
	{
		data->philos[i].number = i + 1;
		data->philos[i].meals_ate = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].lsttime_lock, NULL) == -1)
			return (ft_perror("pthread_mutex_init() has failed ."), 1);
		data->philos[i].last_meal = 0;
	}
	return (0);
}

void	death_check(t_data *data)
{
	int	err;

	err = -1;
	while (1)
	{
		err = sem_wait(data->dead_sem);
		if (err == 0)
		{
			sem_post(data->full_sem);
			data->dead_flag = true;
			return ;
		}
	}
}

void	*all_ate(void *arg)
{
	t_data	*data;
	int		ate;

	data = (t_data *)arg;
	ate = 0;
	while (data->dead_flag == false)
	{
		sem_wait(data->full_sem);
		ate++;
		if (ate == data->philos_nb && data->dead_flag == false)
		{
			sem_wait(data->write_sem);
			printf(MAGENTA
				"=> %lld ms all the philos have a te at least %d times!\n",
				timeofday(data->start_time), data->meals_nb);
			sem_post(data->dead_sem);
			return (NULL);
		}
	}
	return (arg);
}

int	create_philos(t_data *data)
{
	int			i;
	pid_t		pid;
	pthread_t	satisf;

	i = -1;
	data->start_time = timeofday(0);
	while (++i < data->philos_nb)
	{
		pid = fork();
		if (pid < 0)
			return (ft_perror("fork has failed ."), 1);
		else if (pid > 0)
			data->philos[i].id = pid;
		else if (pid == 0)
			philos_routine(&data->philos[i]);
	}
	if (data->meals_nb)
	{
		pthread_create(&satisf, NULL, all_ate, (void *)data);
		pthread_detach(satisf);
	}
	death_check(data);
	kill_proc(data);
	destroy_n_free(data);
	return (0);
}
