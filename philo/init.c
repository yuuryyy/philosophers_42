/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:21:31 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/24 06:53:16 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timeofday(long long start)
{
	struct timeval	tval;

	if (gettimeofday(&tval, NULL))
		return (ft_perror("gettimeofday() has failed !!"), exit (1), 0);
	return (((tval.tv_sec * 1000) + (tval.tv_usec / 1000)) - start);
}

void	write_lock(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d %s.\n", timeofday(philo->data->start_time)  ,philo->number, msg);
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
	if (philo->number % 2) {
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	ft_usleep(size_t time)
{
	long long start;

	start = timeofday(0);
	while (timeofday(start) < (long long)time)
		usleep(100);
}

void	monitor_threads(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(500);
		if (timeofday(data->philos[i].last_meal ) > data->timing.time_to_die)
		{
			pthread_mutex_lock(&data->write);
			printf(MAGENTA"%llu ms %d died", timeofday(data->start_time) , data->philos[i].number);
			return ;
		}
		else if (data->full_philos == data->number_of_philosophers)
			return ;
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
}

void	meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->are_full);
	philo->data->full_philos++;
	pthread_mutex_unlock(&philo->data->are_full);
}

void	routine(void *philo)
{
	t_philo	*tmp = philo;
	tmp->last_meal = timeofday(0);

	if (tmp->number % 2)
		usleep(250);
	while (1)
	{
		fork_lock(tmp);
		write_lock(tmp, eating);
		tmp->last_meal = timeofday(0);
		//ft_usleep(tmp->data->timing.time_to_eat);
		usleep(tmp->data->timing.time_to_eat * 1000);
		fork_unlock(tmp);
		tmp->meals_ate++;
		if (tmp->data->timing.number_of_times_each_philosopher_must_eat &&
			(tmp->meals_ate == tmp->data->timing.number_of_times_each_philosopher_must_eat))
			meals(tmp);
		write_lock(tmp, sleeping);
		usleep(tmp->data->timing.time_to_sleep * 1000);
		// ft_usleep(tmp->data->timing.time_to_sleep);
		write_lock(tmp, thinking);
	}
}

int	creat_threads(t_data *data)
{
	int	index;

	index = 0;
	data->full_philos = 0; // mutex
	if (pthread_mutex_init(&data->write, NULL))
		return(ft_perror("pthread_mutex_init() has failed !!"), 1);
	if (pthread_mutex_init(&data->are_full, NULL))
		return(ft_perror("pthread_mutex_init() has failed !!"), 1);

	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (ft_perror("failed to allocate philos !!"), 1);

	while (index < data->number_of_philosophers)
	{
		data->philos[index].number = index + 1;
		// data->philos[index].time_interv = data->timing; 
		data->philos[index].meals_ate = 0;
		data->philos[index].r_fork = NULL;
		data->philos[index].data = data;
		if (pthread_mutex_init(&data->philos[index].l_fork, NULL))
			return (ft_perror("pthread_mutex_init() has failed !!"), 1);
		// printf("philo %d == %p addrr of left fork \n",data->philos[index].number, &data->philos[index].l_fork);
		data->philos[index].r_fork = &data->philos[(index + 1) % data->number_of_philosophers].l_fork;
		// printf("philo %d == %p addrr of right fork \n\n", data->philos[index].number, data->philos[index].r_fork);
		index++;
	}



	index = 0;
	data->start_time = timeofday(0);
	while (index < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[index].id, NULL, (void *)&routine, (void *)&data->philos[index]))
			return (ft_perror("pthread_creat() has failed !!"), 1);
		index++;
	}

	index = 0;
	while (index < data->number_of_philosophers)
	{ 
		// freee
		if (pthread_detach(data->philos[index].id))
			return (ft_perror("pthread_detach() has failed !!"), 1);
		index++;
	}
	usleep(250);
	monitor_threads(data);
	return (0);
}
