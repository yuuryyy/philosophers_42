/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:05:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/08 00:36:55 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data,0, sizeof(t_data));
	check_arg(av, ac, &data);
	init_sem(&data);
	init_proc(&data);
}