/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/04 15:33:52 by palucena         ###   ########.fr       */
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

void	Command::execPass(std::string args, Client *clt, SockInfo &sockInfo)
{
	if (sockInfo.checkPassword(args) == true)
		clt->changeStatus(AUTHENTICATED);
	else
	{
		clt->changeStatus(DISCONNECTED);
		Response reply(sockInfo.getHostname(), clt->getNickname(), ERR_PASSWDMISMATCH, ":Password incorrect");
		reply.reply(clt);
	}
}

void	Command::execNick(std::string args, Client *clt, SockInfo &sockInfo)
{
	if (sockInfo.searchNick(args) == false)
		clt->setNickname(args);
	else
		std::cout << "nick feo" << std::endl;
}

void	Command::execUser(std::string args, Client *clt, SockInfo &sockInfo) // ✓
{
	(void)clt;
	(void)sockInfo;
	clt->setUsername(args.substr(0, args.find(' ')));
	args = args.substr(args.find(' ') + 1, args.size() - 1);
	args = args.substr(args.find(' ') + 1, args.size() - 1);
	args = args.substr(args.find(' ') + 1, args.size() - 1);
	if (args[0] == ':')
		clt->setRealname(args.substr(1, args.size() - 1));
	else
		clt->setRealname(args);
}

void	Command::execJoin(std::string args, Client *clt, SockInfo &sockInfo) // ✓
{
	(void)sockInfo;
	std::string test;
	test = ":" + clt->getNickname() + " JOIN " + args + "\r\n";
	std::cout << test;
	send(clt->getClientFd(), test.c_str(), test.length(), 0);
}

void	Command::execPrivmsg(std::string args, Client *clt, SockInfo &sockInfo)
{
	(void)args;
	(void)clt;
	(void)sockInfo;
}

void	Command::execMode(std::string args, Client *clt, SockInfo &sockInfo)
{
	(void)args;
	(void)clt;
	(void)sockInfo;
}

void	Command::execPart(std::string args, Client *clt, SockInfo &sockInfo)
{
	(void)args;
	(void)clt;
	(void)sockInfo;
}

void	Command::execPing(std::string args, Client *clt, SockInfo &sockInfo) // ✓
{
	Response reply(sockInfo.getHostname(), clt->getNickname(), "PONG " + args);
	reply.reply(clt);
}
