/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:49 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/22 09:55:33 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_char(char *c, siginfo_t *info)
{
	if (*c == '\0')
	{
		write(1, "\n", 1);
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putendl_fd("Error: failed to send feedback", 2);
	}
	else
	{
		write(1, c, 1);
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putendl_fd("Error: failed to send feedback", 2);
	}
}

static void	ft_sighandle(int signum, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		i = 0;

	(void)context;
	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i != 8)
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putendl_fd("Error: failed to send feedback", 2);
	if (i == 8)
	{
		handle_char(&c, info);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = &ft_sighandle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
