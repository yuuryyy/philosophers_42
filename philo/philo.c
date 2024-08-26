/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:17:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/26 00:03:27 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f(){system("leaks philo");}

int	main(int ac, char **argv)
{
	t_data data;

	// atexit(f);
	memset(&data, 0, sizeof(t_data));
	if (is_number(argv, ac, &data))
		return (1);
	creat_threads(&data);

	
	// printf("%d ",data.time_to_die);
}
