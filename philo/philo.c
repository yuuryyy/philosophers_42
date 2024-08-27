/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:17:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/27 07:58:24 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// void	f(){system("leaks philo");}

int	main(int ac, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (is_number(argv, ac, &data))
		return (1);
	if (init_mutexes(&data))
		return (1);
	if (creat_threads(&data))
		return (1);
	usleep(250);
	monitor_threads(&data);
	destroy_mutexes(&data);
}
