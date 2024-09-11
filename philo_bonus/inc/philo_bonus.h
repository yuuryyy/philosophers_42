/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:23:58 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/11 20:31:13 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "is dead"

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
	long long	time_to_sleep;
	long long	time_to_die;
	long long	time_to_eat;
}	t_intervals;


typedef struct s_philo
{
	pid_t			id;
	int				number;
	long long		last_meal;
	int				meals_ate;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	lsttime_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				full_philos;
	int				meals_nb;
	long long		start_time;
	int				philos_nb;
	t_philo			*philos;
	t_intervals		timing;
	sem_t			*forks;
	sem_t			*dead_sem;
	sem_t			*full_sem;
	sem_t			*write_sem;
}	t_data;

int			check_arg(char **argv, int ac, t_data*data);
int			init_proc(t_data *data);
int			init_sem(t_data *data);

void		print_msg(t_philo *philo, char *msg);
void		philos_routine(t_philo *philo);
void		meals_check(t_philo *philo);
void		dead_action(t_philo *philo);
void		take_forks(t_philo *philo);
void		ft_usleep(long long time);
void		put_forks(t_philo *philo);

void		resting(t_philo *philo);
void		ft_perror(char *str);

long long	timeofday(long long start);


#endif