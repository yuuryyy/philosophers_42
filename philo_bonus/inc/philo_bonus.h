/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:23:58 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/08 00:33:59 by ychagri          ###   ########.fr       */
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
	long long		meals_ate;
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

int		check_arg(char **argv, int ac, t_data*data);

void	ft_perror(char *str);
int	init_proc(t_data *data);

//test remove if not needed
int	init_sem(t_data *data);

#endif