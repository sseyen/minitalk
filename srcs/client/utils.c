/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:12:54 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/22 09:58:17 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	validate_input(pid_t pid, char *str)
{
	if (ft_strlen(str) == 0)
	{
		ft_putendl_fd("Empty string", 2);
		return (0);
	}
	if (pid < 0)
	{
		ft_putendl_fd("Invalid PID", 2);
		return (0);
	}
	return (1);
}

void	ft_kill(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putendl_fd("Error", 2);
		exit(1);
	}
}

void	send_stop(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_kill(pid, SIGUSR2);
		wait_feedback();
		usleep(50);
		i++;
	}
}
