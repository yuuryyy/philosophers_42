/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:20:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/24 06:49:44 by ychagri          ###   ########.fr       */
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


# define fork "has taken a fork"
# define eating "is eating"
# define sleeping "is sleeping"
# define thinking "is thinking"

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

typedef struct s_interval
{	
	int			number_of_times_each_philosopher_must_eat;
	int			time_to_sleep;
	long long			time_to_die;
	int			time_to_eat;
}			  t_intervals;

typedef struct 	s_philo
{
	pthread_t		id;
	int				number;

	long long					last_meal;
	long long					meals_ate;
	pthread_mutex_t			l_fork;
	pthread_mutex_t			*r_fork;
	struct s_data			*data;
}				t_philo;

typedef struct s_data
{
	int				full_philos;
	long long		start_time;
	int				number_of_philosophers;
	pthread_mutex_t	write;
	pthread_mutex_t	are_full;
	t_philo			*philos;
	t_intervals		timing;
}	t_data;


int		is_number(char **argv, int ac, t_data *data);
void	ft_perror(char *str);
int	creat_threads(t_data *data);

#endif