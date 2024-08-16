/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:26:39 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/13 04:28:54 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_perror(char *str)
{
	printf("\033[31mError message : \033[0m%s\n", str);
}

int	is_number(char **argv, int ac)
{
	if (ac != 4 && ac != 5)
		return (ft_perror("invalid number of argument !!"), 0);
	
}