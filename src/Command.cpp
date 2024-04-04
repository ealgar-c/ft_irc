/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/04 15:38:24 by ealgar-c         ###   ########.fr       */
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
	std::string channelName = cmd.substr(5, cmd.length() - 5);
	sockInfo.joinChannel(channelName, clt);
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
	Channel *chl = sockInfo.getChannelByName(cmd.substr(4, cmd.length() - 4));
	std::vector<Client *> clients = chl->getClientsConnected();
	for (std::vector<Client *>::const_iterator v_it = clients.begin(); v_it != clients.end(); v_it++)
	{
		Response reply(sockInfo.getHostname(), clt->getNickname(), RPL_NAMREPLY, (*v_it)->getNickname());
		reply.reply(clt);
	}
	Response reply(sockInfo.getHostname(), clt->getNickname(), RPL_ENDOFNAMES, "");
	reply.reply(clt);
}

void	Command::execPing(std::string args, Client *clt, SockInfo &sockInfo) // ✓
{
	std::string pingCode = cmd.substr(5, cmd.length() - 5);
	Response reply(sockInfo.getHostname(), clt->getNickname(), "PONG " + pingCode);
	reply.reply(clt);
}
