/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:45:11 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/01 21:51:14 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client::Client() {}

Client::Client(C_STATUS status, std::string ip, int clientfd) : _status(status), _ip(ip), _clientfd(clientfd)
{
	this->_messagebuffer.clear();
}

Client::~Client() {}

Client	&Client::operator=(const Client &toEqual)
{
	if (this != &toEqual)
	{
		this->_clientfd = toEqual.getClientFd();
		this->_ip = toEqual.getIp();
		this->_status = toEqual.getStatus();
	}
	return (*this);
}

C_STATUS	Client::getStatus(void) const
{
	return (this->_status);
}

std::string	Client::getNickname(void) const
{
	return (this->_nickname);
}

void	Client::setNickname(const std::string str)
{
	this->_nickname = str;
}

std::string	Client::getUsername(void) const
{
	return (this->_username);
}

void	Client::setUsername(const std::string str)
{
	this->_username = str;
}

std::string	Client::getRealname(void) const
{
	return (this->_realname);
}

void	Client::setRealname(const std::string str)
{
	this->_realname = str;
}

std::string	Client::getIp(void) const
{
	return (this->_ip);
}

int	Client::getClientFd(void) const
{
	return (this->_clientfd);
}

void	Client::changeStatus(C_STATUS newStatus)
{
	this->_status = newStatus;
}
