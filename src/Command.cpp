/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/04 16:33:57 by palucena         ###   ########.fr       */
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

void	Command::execPass(Request &rqt, SockInfo &sockInfo)
{
	if (sockInfo.checkPassword(rqt.getMsg()) == true)
		rqt.getClient()->changeStatus(AUTHENTICATED);
	else
	{
		rqt.getClient()->changeStatus(DISCONNECTED);
		Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), ERR_PASSWDMISMATCH, ":Password incorrect");
		reply.reply(rqt.getClient());
	}
}

void	Command::execNick(Request &rqt, SockInfo &sockInfo)
{
	if (sockInfo.searchNick(rqt.getMsg()) == false)
		rqt.getClient()->setNickname(rqt.getMsg());
	else
		std::cout << "nick feo" << std::endl;
}

void	Command::execUser(Request &rqt, SockInfo &sockInfo) // ✓
{
	(void)sockInfo;
	rqt.getClient()->setUsername(rqt.getMsg().substr(0, rqt.getMsg().find(' ')));
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	if (rqt.getMsg()[0] == ':')
		rqt.getClient()->setRealname(rqt.getMsg().substr(1, rqt.getMsg().size() - 1));
	else
		rqt.getClient()->setRealname(rqt.getMsg());
}

void	Command::execJoin(Request &rqt, SockInfo &sockInfo) // ✓
{
	(void)sockInfo;
	std::string test;
	test = ":" + rqt.getClient()->getNickname() + " JOIN " + rqt.getMsg() + "\r\n";
	std::cout << test;
	send(rqt.getClient()->getClientFd(), test.c_str(), test.length(), 0);
}

void	Command::execPrivmsg(Request &rqt, SockInfo &sockInfo)
{
	(void)rqt;
	(void)sockInfo;
}

void	Command::execMode(Request &rqt, SockInfo &sockInfo)
{
	(void)rqt;
	(void)sockInfo;
}

void	Command::execPart(Request &rqt, SockInfo &sockInfo)
{
	(void)rqt;
	(void)sockInfo;
}

void	Command::execInvite(Request &rqt, SockInfo &sockInfo)
{
	(void)rqt;
	(void)sockInfo;
}

void	Command::execPing(Request &rqt, SockInfo &sockInfo) // ✓
{
	Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), "PONG " + rqt.getMsg());
	reply.reply(rqt.getClient());
}
