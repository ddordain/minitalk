# Minitalk

The purpose of this project is to code a small data exchange program using UNIX
signals.

The client uses SIGUSR1 and SIGUSR2 to depict each bit of each char. The server
can recode the SIGUSR1 and SIGUSR2 signals received as the 8 bits of a character
and then deduce which character was sent by the client.