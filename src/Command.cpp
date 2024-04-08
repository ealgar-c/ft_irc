/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/08 16:32:16 by ealgar-c         ###   ########.fr       */
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
		Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), ERR_PASSWDMISMATCH, "", ":Password incorrect");
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
	sockInfo.joinChannel(rqt.getMsg(), rqt.getClient());
}

void	Command::execPrivmsg(Request &rqt, SockInfo &sockInfo)
{
	std::cout << "cmd -> " << rqt.getCmd() << " mensaje-> " << rqt.getMsg() << std::endl;
	//Response::reply(rqt.getClient())._from("")._to("")._cmd("")._msg("")._endmsg("")._finalResponse("")._rtype(ERR_NICKNAMEONUSE);
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

/* void	Command::execWho(Request &rqt, SockInfo &sockInfo)
{
	Channel *chl = sockInfo.getChannelByName(rqt.getMsg());
	std::vector<Client *> clients = chl->getClientsConnected();
	for (std::vector<Client *>::const_iterator v_it = clients.begin(); v_it != clients.end(); v_it++)
	{
		Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), RPL_NAMREPLY, (*v_it)->getNickname());
		reply.reply(rqt.getClient());
	}
	Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), RPL_ENDOFNAMES, "");
	reply.reply(rqt.getClient());
} */

void	Command::execPing(Request &rqt, SockInfo &sockInfo) // ✓
{
	Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), "PONG ", rqt.getMsg());
	reply.reply(rqt.getClient());
}
