/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:42:48 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/21 20:57:12 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_exit(char **buff, char *error)
{
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	ft_putendl_fd(error, 2);
	exit(1);
}

static void	send_message(char **buff, siginfo_t *info, int *idx)
{
	ft_putendl_fd(*buff, 1);
	if (*buff)
		free(*buff);
	*buff = NULL;
	*idx = 0;
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_exit(buff, "Failed to send feedback");
}

void	handle_char(char *c, char **buff, siginfo_t *info, int *idx)
{
	if (!*c)
	{
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_exit(buff, "Failed to send feedback");
		send_message(buff, info, idx);
	}
	else
	{
		(*buff)[(*idx)++] = *c;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_exit(buff, "Failed to send feedback");
	}
	*c = 0;
}
