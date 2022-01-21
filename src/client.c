/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:07:14 by ddordain          #+#    #+#             */
/*   Updated: 2022/01/21 17:11:11 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	termination(int signum)
{
	(void)signum;
}

static	void char_to_binary(pid_t pid, char c)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		usleep(50);
	}
}

static void	encoding_str(pid_t pid, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		char_to_binary(pid, str[i]);
		i++;
	}
	char_to_binary(pid, '\n');
	char_to_binary(pid, '\0');
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		write(2, MSG_ERR_CLT, ft_strlen(MSG_ERR_CLT));
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR2, termination);
	if (kill(pid, 0) == -1)
	{
		write(2, MSG_ERR_PID, ft_strlen(MSG_ERR_PID));
		return (EXIT_FAILURE);
	}
	encoding_str(pid, av[2]);
	return (EXIT_SUCCESS);
}