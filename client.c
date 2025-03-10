/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:47 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 15:58:18 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(1);
	}
}

void	ft_sigsend(int pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (j < 8)
		{
			if (str[i] & (1 << j))
				ft_kill(pid, SIGUSR1);
			else
				ft_kill(pid, SIGUSR2);
			j++;
			usleep(300);
		}
		i++;
	}
	j = 0;
	while (j < 8)
	{
		ft_kill(pid, SIGUSR2);
		j++;
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
	{
		ft_putstr_fd("Wrong number of arguments\n", 1);
		return (1);
	}
	str = argv[2];
	if (ft_strlen(str) == 0)
	{
		ft_putstr_fd("Empty string\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 1);
		return (1);
	}
	ft_sigsend(pid, str);
	return (0);
}
