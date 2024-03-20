/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:27:15 by palucena          #+#    #+#             */
/*   Updated: 2024/03/20 16:27:39 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
