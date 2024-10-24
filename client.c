/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:47 by alisseye          #+#    #+#             */
/*   Updated: 2024/10/24 18:37:44 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sigsend(pid_t pid, char *str)
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
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j++;
			usleep(100);
		}
		i++;
	}
	j = 0;
	while (j < 8)
	{
		kill(pid, SIGUSR2);
		j++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
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
	if (pid < 0)
	{
		ft_putstr_fd("Invalid PID\n", 1);
		return (1);
	}
	ft_sigsend(pid, str);
	return (0);
}
