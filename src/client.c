/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:07:14 by ddordain          #+#    #+#             */
/*   Updated: 2023/01/07 14:34:57 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** This function is a signal handler for the SIGUSR2 signal.
** It does nothing but sleep for a short period of time.
*/
static void termination(int signum)
{
	(void)signum; // Unused parameter
	usleep(150);  // Sleep for 150 microseconds
}

/*
** This function encodes a single character as a series of SIGUSR1 and SIGUSR2 signals,
** with the value of each signal representing a bit in the character's binary representation.
*/
static void char_to_binary(pid_t pid, char c)
{
	char bit;

	bit = 8; // Each character is 8 bits
	while (bit--)
	{
		// Send a SIGUSR2 signal if the current bit is 1, otherwise send a SIGUSR1 signal
		if (c >> bit & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause(); // Wait for a signal before sending the next one
	}
}

/*
** This function encodes a string as a series of SIGUSR1 and SIGUSR2 signals
** by calling the char_to_binary function for each character in the string.
*/

static void encoding_str(pid_t pid, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		char_to_binary(pid, str[i]);
		i++;
	}
	char_to_binary(pid, '\n'); // Add a newline character after the string
	char_to_binary(pid, '\0'); // Add a null terminator after the newline
}

/*
** The main function is the entry point of the program.
** It expects two command-line arguments: the PID of the process to which the message should be sent,
** and the message to be sent.
*/
int main(int ac, char **av)
{
	pid_t pid;

	if (ac != 3) // Check if the correct number of arguments were provided
	{
		write(2, MSG_ERR_CLT, ft_strlen(MSG_ERR_CLT)); // Print error message to stderr
		return (EXIT_FAILURE);						   // Return failure code
	}
	pid = ft_atoi(av[1]);		  // Convert the PID from a string to an integer
	signal(SIGUSR2, termination); // Set up a signal handler for the SIGUSR2 signal
	if (kill(pid, 0) == -1)		  // Check if the process with the provided PID exists
	{
		write(2, MSG_ERR_PID, ft_strlen(MSG_ERR_PID)); // Print error message to stderr
		return (EXIT_FAILURE);						   // Return failure code
	}
	encoding_str(pid, av[2]); // Encode the message and send it to the receiving process
	return (EXIT_SUCCESS);	  // Return success code
}