/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:55:12 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/21 19:25:11 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

// Client utils
int		validate_input(pid_t pid, char *str);
void	ft_kill(int pid, int sig);
void	wait_feedback(void);
void	send_stop(int pid);
void	send_blen(int pid, int len);

// Server utils
void	ft_exit(char **buff, char *error);
void	handle_char(char *c, char **buff, siginfo_t *info, int *idx);

#endif