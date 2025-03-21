/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:49 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/21 21:06:44 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	allocate_buff(int signum, siginfo_t *info, char **buff)
{
	static unsigned int	size = 0;
	static unsigned int	i = 0;

	if (signum == SIGUSR1)
		size |= (1 << i);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_exit(buff, "Failed to send feedback");
	i++;
	if (i == 32)
	{
		*buff = malloc(size + 1);
		if (!*buff)
		{
			ft_putendl_fd("Error: malloc failed", 2);
			exit(1);
		}
		i = 0;
		while (i <= size)
			(*buff)[i++] = 0;
		i = 0;
		size = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_exit(buff, "Failed to send feedback");
	}
}

static void	ft_sighandle(int signum, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		i = 0;
	static int		idx = 0;
	static char		*buff = NULL;

	(void)context;
	if (!buff)
	{
		allocate_buff(signum, info, &buff);
		return ;
	}
	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i != 8)
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_exit(&buff, "Failed to send feedback");
	if (i == 8)
	{
		handle_char(&c, &buff, info, &idx);
		i = 0;
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
