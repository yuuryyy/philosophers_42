/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:26:39 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/17 00:17:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_perror(char *str)
{
	printf("\033[31mError message : \033[0m%s\n", str);
}

int	check_chars(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] == ' ' || argv[i] == '\t')
		i++;
	if (!argv[i])
		return (ft_perror("empty argument"), 1);
	if ((argv[i] == '+' || argv[i] == '-')
		&& (argv[i + 1] > '9' || argv[i + 1] < '0'))
		return (ft_perror("invalid characters !!"), 1);
	else
		i++;
	while (argv[i] <= '9' && argv[i] >= '0')
		i++;
	while (argv[i] == ' ' || argv[i] == '\t')
		i++;
	if (argv[i] && (argv[i] != ' ' && argv[i] != '\t'))
		return (ft_perror("invalid characters !!"), 1);
	return (0);
}

int	ft_atoi(char *str)
{
	long long	i;
	int			sign;
	long long	res;
	long long	temp;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] == ' ') || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= (-1);
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = res;
		res = res * 10 + (str[i++] - '0');
		if (temp != res / 10)
			return (-1);
	}
	return (res * sign);
}

int	is_number(char **argv, int ac, t_data*data)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (ft_perror("invalid number of argument !!"), 1);
	i = 1;
	while (argv[i])
	{
		if (check_chars(argv[i]))
			return (1);
		i++;
	}
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	if (data->number_of_philosophers <= 0 || data->number_of_philosophers > 200
		|| data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60
		|| data->number_of_times_each_philosopher_must_eat < 0)
		return (ft_perror("invalid number of philos/timer !!"), 1);
	return (0);
}
