/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:05:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/14 03:32:43 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data,0, sizeof(t_data));
	if (check_arg(av, ac, &data))
		return (1);
	// printf("%d\n", data.philos_nb);
	if (init_sem(&data))
		return (1);
	if (init_proc(&data))
		return (1);
}
