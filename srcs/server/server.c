/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:49 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/17 16:56:23 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_message(char **buff, siginfo_t *info, int *idx)
{
	ft_putendl_fd(*buff, 1);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_putendl_fd("Failed to send feedback", 2);
	free(*buff);
	*buff = NULL;
	*idx = 0;
}

static void	allocate_buff(int signum, char **buff)
{
	static unsigned int	size = 0;
	static unsigned int	i = 0;

	if (signum == SIGUSR1)
		size |= (1 << i);
	i++;
	if (i == 32)
	{
		*buff = malloc(sizeof(char) * size + 1);
		if (!*buff)
		{
			ft_putendl_fd("Error: malloc failed", 2);
			exit(1);
		}
		(*buff)[0] = 0;
		i = 0;
		while (i < size)
			(*buff)[i++] = 0;
		i = 0;
		size = 0;
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
		allocate_buff(signum, &buff);
		return ;
	}
	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (!c)
			send_message(&buff, info, &idx);
		else
			buff[idx++] = c;
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
