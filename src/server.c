/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:03:33 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/04 10:38:06 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum, siginfo_t *info, void *unused)
{
	static char	c;
	static int	bit;

	(void)unused;
	bit += 1;
	if (bit == 1)
		c = '\0';
	c |= signum == SIGUSR2;
	if (bit < 8)
		c <<= 1;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	usleep(200);
	kill(info->si_pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	action;

	(void) av;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	if (ac != 1)
	{
		write(2, MSG_ERR_SRV, ft_strlen(MSG_ERR_SRV));
		return (EXIT_FAILURE);
	}
	pid = getpid();
	write(1, MSG_PID, ft_strlen(MSG_PID));
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (42)
		pause();
	return (EXIT_SUCCESS);
}
