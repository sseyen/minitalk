/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:47 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/17 15:30:41 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_message_received = 0;

static void	feedback(int signum)
{
	if (signum == SIGUSR1)
	{
		g_message_received = 1;
		ft_putendl_fd("Message received", 1);
	}
}

static void	sigsend(pid_t pid, char *str, int delay)
{
	int		i;
	int		j;

	send_blen(pid, ft_strlen(str), delay);
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
			usleep(delay);
		}
		i++;
	}
	send_stop(pid, delay);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;

	if (argc != 3)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	if (!validate_input(pid, str))
		return (1);
	signal(SIGUSR1, feedback);
	sigsend(pid, str, 200);
	while (g_message_received == 0)
		pause();
	return (0);
}
