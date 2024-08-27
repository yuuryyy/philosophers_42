/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:20:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/27 07:48:54 by ychagri          ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef struct s_interval
{
	int			number_of_times_each_philosopher_must_eat;
	long long	time_to_sleep;
	long long	time_to_die;
	long long	time_to_eat;
}	t_intervals;

typedef struct s_philo
{
	pthread_t		id;
	int				number;
	long long		last_meal;
	long long		meals_ate;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				full_philos;
	long long		start_time;
	int				number_of_philosophers;
	pthread_mutex_t	write;
	pthread_mutex_t	are_full;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
	t_intervals		timing;
}	t_data;

int			is_number(char **argv, int ac, t_data *data);
int			monitor_threads(t_data *data);
int			creat_threads(t_data *data);
int			init_mutexes(t_data *data);

void		write_lock(t_philo *philo, char *msg);
void		death_msg(t_data *data, int i);
void		destroy_mutexes(t_data *data);
void		fork_unlock(t_philo *philo);
void		meals_lock(t_philo *philo);
void		ft_usleep(long long time);
void		fork_lock(t_philo *philo);
void		full_msg(t_data *data);
void		ft_perror(char *str);

long long	timeofday(long long start);

#endif