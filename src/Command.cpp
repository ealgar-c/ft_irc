/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/13 17:47:12 by palucena         ###   ########.fr       */
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

void	Command::execPass(Request &rqt, SockInfo &serv)
{
	if (serv.authenticate(rqt.getMsg()))
		rqt.getClient()->changeStatus(AUTHENTICATED);
	else
	{
		rqt.getClient()->changeStatus(DISCONNECTED);
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_PASSWDMISMATCH, "", ":Password incorrect");
		reply.reply(rqt.getClient());
	}
}

bool	forbiddenChar(std::string str)
{
	if (str[0] == '$' || str[0] == ':' || str[0] == '#')
		return (true);
	
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == ',' || str[i] == '*' || str[i] == '?'
			|| str[i] == '!' || str[i] == '@' || str[i] == '.')
			return (true);
	}
	return (false);
}

void	Command::execNick(Request &rqt, SockInfo &serv) // cosas de NICK(elodeon)
{
	if (rqt.getMsg().empty())
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NONICKNAMEGIVEN, "", ":No nickname given");
	else if (serv.searchNick(rqt.getMsg()) == true)
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NICKNAMEINUSE, "", ":Nickname is already in use");
	else if (forbiddenChar(rqt.getMsg()) == true)
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_ERRONEUSNICKNAME, "", ":Erroneus nickname");
	else
		rqt.getClient()->setNickname(rqt.getMsg());
}

void	Command::execUser(Request &rqt, SockInfo &serv) // ✓
{
	(void)serv;
	rqt.getClient()->setUsername(rqt.getMsg().substr(0, rqt.getMsg().find(' ')));
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	rqt.getMsg() = rqt.getMsg().substr(rqt.getMsg().find(' ') + 1, rqt.getMsg().size() - 1);
	if (rqt.getMsg()[0] == ':')
		rqt.getClient()->setRealname(rqt.getMsg().substr(1, rqt.getMsg().size() - 1));
	else
		rqt.getClient()->setRealname(rqt.getMsg());
}

void	Command::execJoin(Request &rqt, SockInfo &serv)
{
	std::string newChannelName = rqt.getMsg();
	if (newChannelName.find(' '))
		newChannelName = newChannelName.substr(0, newChannelName.find(' '));
	serv.joinChannel(newChannelName, rqt.getMsg().substr(newChannelName.size() - 1, rqt.getMsg().size() - 1), rqt.getClient());
}

void	Command::execPrivmsg(Request &rqt, SockInfo &serv)
{
	std::cout << "cmd -> " << rqt.getCmd() << " mensaje-> " << rqt.getMsg() << std::endl;
	//Response::reply(rqt.getClient())._from("")._to("")._cmd("")._msg("")._endmsg("")._finalResponse("")._rtype(ERR_NICKNAMEONUSE);
	(void)serv;
}

void	Command::execMode(Request &rqt, SockInfo &serv) // TODO: ahora esto
{
	(void)rqt;
	(void)serv;
	
	std::cout << "Mensaje recibido por MODE: " << rqt.getMsg() << ".\n";

	std::string	flag = rqt.getMsg().substr(0, rqt.getMsg().find(' '));
	std::string	msg = rqt.getMsg().substr(flag.size() - 1, rqt.getMsg().size() - 1);

	/* if (msg.empty())
		Response::reply(rqt.getClient(), " MODE :Not enough parameters"); // ERR_NEEDMOREPARAMS;
	else if (flag.size() == 2)
	{
		if (flag == "+o") // Channel operator
		{
			try
			{
				if ((rqt.getClient()))
			}
			catch (const std::exception &e)
			{
				Response::reply(rqt.getClient(), e.what());
			}
		}
		else if (flag == "+l") // Users limit
		else if (flag == "+k") // Password
		else if (flag == "+t") // Change topic
		else if (flag == "+i") // Invite only
	} */
}

void	Command::execPart(Request &rqt, SockInfo &serv)
{
	(void)rqt;
	(void)serv;
}

void	Command::execInvite(Request &rqt, SockInfo &serv) // TODO: esto es mío
{
	(void)rqt;
	(void)serv;
}

void	Command::execPing(Request &rqt, SockInfo &serv)
{
	Response reply(serv.getHostname(), rqt.getClient()->getNickname(), "PONG ", rqt.getMsg());
	reply.reply(rqt.getClient());
}
