/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:49 by alisseye          #+#    #+#             */
/*   Updated: 2024/10/30 11:32:19 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sighandle(int signum, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		i = 0;

	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			ft_putchar_fd('\n', 1);
			if (kill(info->si_pid, SIGUSR1) == -1)
				ft_putstr_fd("Failed to send feedback\n", 1);
		}
		else
			ft_putchar_fd(c, 1);
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
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
