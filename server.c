/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:19:49 by alisseye          #+#    #+#             */
/*   Updated: 2024/10/24 18:05:17 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sighandle(int signum)
{
	static char	c = 0;
	static int	i = 0;

	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == 0)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_sighandle);
	signal(SIGUSR2, ft_sighandle);
	while (1)
		pause();
	return (0);
}
