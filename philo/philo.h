/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:20:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/21 04:27:04 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>


typedef struct s_interval
{	
	size_t			number_of_times_each_philosopher_must_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			time_to_eat;
}	t_intervals;
typedef struct s_philo
{
	size_t			start_time;
	size_t			last_meal;
	int				meals_ate;
	bool			sleeping;
	bool			thinking;
	bool			eating;
	int				number;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_t		id;
	t_intervals		time_interv;
}	t_philo;

typedef struct s_data
{

	bool			dead_flag;
	size_t			number_of_philosophers;
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	t_intervals		timing;
}	t_data;


int		is_number(char **argv, int ac, t_data *data);
void	ft_perror(char *str);
void	creat_threads(t_data *data);

#endif