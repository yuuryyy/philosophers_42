/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:05:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/15 00:31:25 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	// sem_t	*sem;
	// pid_t	pid;
	// sem = sem_open("semmm", O_CREAT , 1);
	// pid = fork();
	// if (pid > 0)
	// {
	// 	if (sem_wait(sem) == 0)
	// 		printf("child here\n");
	// 	sem_post(sem);
	// 	// while (1);
	// }
	// else
	// {
	// 	// sleep(1);
	// 	if (sem_wait(sem) == 0)
	// 	{
	// 		printf("parent here\n");
	// 		sem_post(sem);
			
	// 	}
	// }
	
	memset(&data,0, sizeof(t_data));
	if (check_arg(av, ac, &data))
		return (1);
	if (init_sem(&data))
		return (1);
	if (init_proc(&data))
	printf("<<<<%p>>>>\n", data.dead_sem);
		return (1);
}
