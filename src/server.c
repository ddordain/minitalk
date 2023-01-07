/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:03:33 by ddordain          #+#    #+#             */
/*   Updated: 2023/01/07 14:44:41 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** This function is a signal handler for the SIGUSR1 and SIGUSR2 signals.
** It receives each signal sent by the client and decodes it as a bit in a character.
** The character is then printed to stdout when all 8 bits have been received.
*/
static void handler(int signum, siginfo_t *info, void *unused)
{
	static char c;	// The character being received
	static int bit; // The current bit being processed

	(void)unused; // Unused parameter
	bit += 1;	  // Increment the current bit
	if (bit == 1)
		c = '\0';			// Reset c to null character if this is the first bit
	c |= signum == SIGUSR2; // OR c with 1 if the signal is SIGUSR2
	if (bit < 8)
		c <<= 1;  // Left-shift c by 1 if there are more bits to receive
	if (bit == 8) // If all 8 bits have been received
	{
		write(1, &c, 1); // Print c to stdout
		bit = 0;		 // Reset the current bit
	}
	usleep(200);				 // Sleep for 200 microseconds
	kill(info->si_pid, SIGUSR2); // Send a SIGUSR2 signal to the client to indicate that the server is ready for the next bit
}

/*
** The main function is the entry point of the program.
** It expects no command-line arguments.
*/
int main(int ac, char **av)
{
	pid_t pid;				 // The PID of the current process
	struct sigaction action; // Struct containing information about the signal handler

	(void)av;					   // Unused parameter
	sigemptyset(&action.sa_mask);  // Initialize the signal set to the empty set
	action.sa_flags = SA_SIGINFO;  // Set the SA_SIGINFO flag in the sa_flags field
	action.sa_sigaction = handler; // Set the signal handler function
	if (ac != 1)				   // Check if any command-line arguments were provided
	{
		write(2, MSG_ERR_SRV, ft_strlen(MSG_ERR_SRV)); // Print error message to stderr
		return (EXIT_FAILURE);						   // Return failure code
	}
	pid = getpid();						   // Get the PID of the current process
	write(1, MSG_PID, ft_strlen(MSG_PID)); // Print message to stdout
	ft_putnbr_fd(pid, 1);				   // Print the PID to stdout
	write(1, "\n", 1);					   // Print a newline to stdout
	sigaction(SIGUSR1, &action, NULL);	   // Set up the signal handler for the SIGUSR1 signal
	sigaction(SIGUSR2, &action, NULL);	   // Set up the signal handler for the SIGUSR2 signal
	while (42)							   // Infinite loop
		pause();						   // Wait for a signal
	return (EXIT_SUCCESS);
}