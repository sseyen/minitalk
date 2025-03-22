/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:47 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/22 09:58:29 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal_received = 0;

void	wait_feedback(void)
{
	int	timeout;

	timeout = 10000;
	while (!g_signal_received && timeout--)
		usleep(100);
	if (!g_signal_received)
	{
		ft_putendl_fd("Timeout: No confirmation received", 2);
		exit(1);
	}
	g_signal_received = 0;
}

static void	feedback(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		g_signal_received = 1;
}

static void	sigsend(pid_t pid, char *str)
{
	int		i;
	int		j;

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
			wait_feedback();
			usleep(50);
		}
		i++;
	}
	send_stop(pid);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	if (!validate_input(pid, str))
		return (1);
	sa.sa_sigaction = &feedback;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigsend(pid, str);
	ft_putendl_fd("Message sent successfully!", 1);
	return (0);
}
