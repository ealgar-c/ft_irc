/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/03 18:56:44 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Command::Command()
{ }

Command::Command(const Command &toCopy)
{
	(void)toCopy;
}

Command::~Command()
{ }

Command	&Command::operator=(const Command &toCopy)
{
	(void)toCopy;
	return (*this);
}

void	execPass(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	if (sockInfo.checkPassword(cmd.substr(5, cmd.size())) == true)
		clt->changeStatus(AUTHENTICATED);
	else
	{
		clt->changeStatus(DISCONNECTED);
		std::cout << clt->getNickname() << ": Wrong password" << std::endl;
	}
}

static void	execNick(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}

static void	execUser(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}

static void	execConn(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}

static void	execJoin(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	this->_cmd = "JOIN";
	std::string test;
	test = ":palucena " + cmd + "\r\n";
	std::cout << test;
	send(clt->getClientFd(), test.c_str(), test.length(), 0);
}

static void	execPrivmsg(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}

static void	execWho(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}

static void	execPing(std::string cmd, Client *clt, SockInfo &sockInfo);
{
	(void)cmd;
	(void)clt;
	(void)SockInfo;
}
