/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:27:15 by palucena          #+#    #+#             */
/*   Updated: 2024/03/30 14:20:40 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/************************
 _    ___________  _____ 
| |  |_   _| ___ \/  ___|
| |    | | | |_/ /\ `--. 
| |    | | | ___ \ `--. \
| |____| |_| |_/ //\__/ /
\_____|___/\____/ \____/ 
************************/
# include <sys/socket.h>   // Para socket, setsockopt, getsockname, getaddrinfo, freeaddrinfo, bind, connect, listen, accept, recv, send
# include <netinet/in.h>   // Para htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa
# include <arpa/inet.h>    // Para inet_addr, inet_ntoa
# include <netdb.h>        // Para getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
# include <unistd.h>       // Para close
# include <signal.h>       // Para signal, sigaction
# include <sys/types.h>    // Para fcntl, lseek
# include <sys/stat.h>     // Para fstat
# include <fcntl.h>        // Para fcntl
# include <poll.h>         // Para poll
# include <cstring>
# include <iostream>
# include <cstdlib>
# include <cerrno>
# include <vector>

/************************************
 _____ _____ _   _ _____ _____ _____ 
/  __ \  _  | \ | /  ___|_   _/  ___|
| /  \/ | | |  \| \ `--.  | | \ `--. 
| |   | | | | . ` |`--. \ | |  `--. \
| \__/\ \_/ / |\  /\__/ / | | /\__/ /
 \____/\___/\_| \_|____/  \_/ \____/ 
************************************/
# define CONST_MAXSCONN 5
# define ERR_ARGNO "Number of arguments incorrect."
# define ERR_PORTARG "The received port is incorrect."
# define ERR_EMPTYPWD "An empty password is invalid."
# define ERR_SOCKCREAT "Error creating the socket."
# define ERR_SETSOCKOPT "Error while setting socket options."
# define ERR_BINDSOCK "Error binding socket."
# define ERR_SOCKLISTEN "Error trying to listen from the socket."

/*******************************************
 _____ _      ___  _____ _____ _____ _____ 
/  __ \ |    / _ \/  ___/  ___|  ___/  ___|
| /  \/ |   / /_\ \ `--.\ `--.| |__ \ `--. 
| |   | |   |  _  |`--. \`--. \  __| `--. \
| \__/\ |___| | | /\__/ /\__/ / |___/\__/ /
 \____|_____|_| |_|____/\____/\____/\____/
*******************************************/
# include "SockInfo.hpp"

/******************************************************
______ _   _ _   _ _____ _____ _____ _____ _   _ _____ 
|  ___| | | | \ | /  __ \_   _|_   _|  _  | \ | /  ___|
| |_  | | | |  \| | /  \/ | |   | | | | | |  \| \ `--. 
|  _| | | | | . ` | |     | |   | | | | | | . ` |`--. \
| |   | |_| | |\  | \__/\ | |  _| |_\ \_/ / |\  /\__/ /
\_|    \___/\_| \_/\____/ \_/  \___/ \___/\_| \_|____/
******************************************************/

/*****************************
  __  __   _   ___ _  _   ___ 
 |  \/  | /_\ |_ _| \| | / __|
 | |\/| |/ _ \ | || .` || (__ 
 |_|  |_/_/ \_\___|_|\_(_)___|
*****************************/

//	prints an error in the stderr and exits the program with error code 1
void	printError(std::string err);