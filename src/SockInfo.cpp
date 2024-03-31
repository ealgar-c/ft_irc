/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:39 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/03/30 14:27:36 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

//	constructor
SockInfo::SockInfo(char **av){
	std::string	passwd_str(av[2]);
	this->_port = atoi(av[1]);
	this->_passwd = passwd_str;
}

//	destructor
SockInfo::~SockInfo(){}

//	methods

/**
 * @brief Creates the socket
 */
void	SockInfo::createSocket(void) // tenemos un super socket
{
	sockaddr_in	sockAddrConf;
	int	opt = 1;

	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd == -1)
		printError(ERR_SOCKCREAT);
	sockAddrConf.sin_port = htons(this->_port);
	sockAddrConf.sin_addr.s_addr = INADDR_ANY;
	sockAddrConf.sin_family = AF_INET;
	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(this->_sockfd);
		printError(ERR_SETSOCKOPT);
	}
	if (bind(this->_sockfd, (sockaddr *)&sockAddrConf, sizeof(sockAddrConf)) == -1)
	{
		close(this->_sockfd);
		printError(ERR_BINDSOCK);
	}
	if (listen(this->_sockfd, CONST_MAXSCONN) == -1)
	{
		close(this->_sockfd);
		printError(ERR_SOCKLISTEN);
	}
}

/**
 * @brief it executes a loop that is using poll (in a non-blocking way)
 * 			to read from the socket fd any POLLIN event
 */
void	SockInfo::runServ(void)
{
	std::vector<struct pollfd> fds;

	fds.push_back((struct pollfd){this->_sockfd, POLLIN, 0});
	while (poll(&fds[0], fds.size(), -1))
	{
		
	}
}