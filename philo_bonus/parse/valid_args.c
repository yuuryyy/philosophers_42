/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:23:54 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/17 05:10:44 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	ft_perror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, "\033[31mError message : \033[0m", 26);
	write(2, str, i);
	write(2, "\n", 1);
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

size_t	ft_atoi(char *str)
{
	size_t	i;
	int		sign;
	size_t	res;
	size_t	temp;

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

int	check_arg(char **argv, int ac, t_data *data)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (ft_perror("invalid number of argument !!"), 1);
	i = 0;
	while (argv[++i])
	{
		if (check_chars(argv[i]))
			return (1);
	}
	data->philos_nb = ft_atoi(argv[1]);
	data->timing.time_to_die = ft_atoi(argv[2]);
	data->timing.time_to_eat = ft_atoi(argv[3]);
	data->timing.time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
		data->meals_nb
			= ft_atoi(argv[5]);
	else
		data->meals_nb = 0;
	if (data->philos_nb <= 0 || data->philos_nb > 200
		|| data->timing.time_to_die < 60 || data->timing.time_to_eat < 60
		|| data->timing.time_to_sleep < 60
		|| data->meals_nb < 0)
		return (ft_perror("invalid number of philos/timer !!"), 1);
	return (0);
}