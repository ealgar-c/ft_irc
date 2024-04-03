/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/03 19:55:07 by ealgar-c         ###   ########.fr       */
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

void	Command::execPass(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	if (sockInfo.checkPassword(cmd.substr(5, cmd.size())) == true)
		clt->changeStatus(AUTHENTICATED);
	else
	{
		clt->changeStatus(DISCONNECTED);
		Response reply(sockInfo.getHostname(), "ealgar-c", ERR_PASSWDMISMATCH, ":Password incorrect");
		reply.reply(clt);
	}
}

void	Command::execNick(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	std::string	newNick = cmd.substr(5, cmd.size() - 1);

	if (sockInfo.searchNick(newNick) == false)
		clt->setNickname(newNick);
	else
		std::cout << "nnick feo" << std::endl;
}

void	Command::execUser(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)cmd;
	(void)clt;
	(void)sockInfo;
}

void	Command::execConn(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)cmd;
	(void)clt;
	(void)sockInfo;
}

void	Command::execJoin(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)sockInfo;
	std::string test;
	test = ":" + clt->getNickname() + " " + cmd + "\r\n";
	std::cout << test;
	send(clt->getClientFd(), test.c_str(), test.length(), 0);
}

void	Command::execPrivmsg(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)cmd;
	(void)clt;
	(void)sockInfo;
}

void	Command::execWho(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)cmd;
	(void)clt;
	(void)sockInfo;
}

void	Command::execPing(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	std::string pingCode = cmd.substr(5, cmd.length() - 5);
	Response reply(sockInfo.getHostname(), clt->getNickname(), "PONG " + pingCode§§);
	reply.reply(clt);
}
