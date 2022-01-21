/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:01:56 by ddordain          #+#    #+#             */
/*   Updated: 2022/01/21 17:01:27 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define  _GNU_SOURCE

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include "../libft/include/libft.h"

# define MSG_ERR_SRV "Sorry, but no argument is expected after ./server\n"
# define MSG_PID "The PID of the server is:\n"
# define MSG_ERR_CLT "Sorry, inputs must be expressed as: \
\n ./client <PID of the server> <A single string>\n"
# define MSG_ERR_PID "Please insert a valid PID\n"

#endif