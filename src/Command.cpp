/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/16 07:54:16 by ealgar-c         ###   ########.fr       */
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
	(void)sockInfo;
	//std::string dest = ;
/* 	std::string dest;
	if (rqt.getMsg().find("#") != std::string::npos)
		dest = rqt.getMsg().substr(rqt.getMsg().find("#"), rqt.getMsg().find(" ") - rqt.getMsg().find("#"));
	else
		dest = rqt.getMsg().substr(rqt.getMsg().find(" " + 1), rqt.getMsg().find(" ") - rqt.getMsg().find("#"));
	std::string finalMsg = rqt.getMsg().erase(0, dest.length() + 1);
	std::cout << "dest -> (" << dest << ")" << std::endl;
	std::cout << "final -> (" << finalMsg << ")" << std::endl;
	Response resp(rqt.getClient()->getNickname(), rqt.getCmd(), dest + " ", finalMsg);
	sockInfo.getChannelByName(dest)->broadcastChannel(rqt.getClient(), resp, false); */
}

void	Command::execMode(Request &rqt, SockInfo &serv) // TODO: ahora esto
{
	std::cout << "Mensaje recibido por MODE: " << rqt.getMsg() << ".\n"; // esto fuera

	std::string	ch = rqt.getMsg().substr(0, rqt.getMsg().find(' '));
	std::string	flag = rqt.getMsg().substr(ch.size() - 1, rqt.getMsg().find(' '));
	std::string	msg = rqt.getMsg().substr(ch.size() + flag.size() - 2, rqt.getMsg().size() - 1);
	RESP_CODE	rcode;

	try
	{
		if (rqt.getMsg().empty() || flag.empty()) {
			rcode = ERR_NEEDMOREPARAMS;
			throw CommandException(" :Not enough parameters");
		}
		if (!serv.getChannelByName(ch)) {
			rcode = ERR_NOSUCHCHANNEL;
			throw CommandException(ch + " :No such channel");
		}
		if (!serv.getChannelByName(ch)->clientIsInChannel(rqt.getClient())) {
			rcode = ERR_NOTONCHANNEL;
			throw CommandException(" :You're not on that channel");
		}
		if (!serv.getChannelByName(ch)->clientIsOperator(rqt.getClient())) {
			rcode = ERR_CHANOPRIVSNEEDED;
			throw CommandException(" :You're not channel operator");
		}
		else if (flag.size() == 2)
		{
			if (flag == "+i") {
				if (serv.getChannelByName(ch)->getInviteMode() == false)
					serv.getChannelByName(ch)->setInviteMode(true);
				else
					serv.getChannelByName(ch)->setInviteMode(false);
			}
			else if (flag == "+t") {} // Change topic
			else if (flag == "+k") {} // Password
			else if (flag == "+o") {} // Channel operator
			else if (flag == "+l") {} // Users limit
			else {
				rcode = ERR_UNKNOWNMODE;
				throw CommandException(" :is unknown mode char to me");
			}
		}
	}
	catch (const std::exception &e)
	{
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), rcode, "", "");
		rpl.reply(rqt.getClient(), e.what());
	}
}

void	Command::execPart(Request &rqt, SockInfo &serv)
{
	(void)rqt;
	(void)sockInfo;
}

void	Command::execInvite(Request &rqt, SockInfo &sockInfo)
{
	(void)rqt;
	(void)serv;
	
	std::cout << "Mensaje recibido por INVITE: " << rqt.getMsg() << ".\n";

	RESP_CODE	rcode;

	try
	{
		if (rqt.getMsg().empty())
			throw CommandException("INVITE :Not enough parameters.");

		std::string	nick = rqt.getMsg().substr(0, rqt.getMsg().find(" "));
		std::string	ch = rqt.getMsg().substr(nick.size() - 1, rqt.getMsg().size() - 1);

		if (nick.empty() || ch.empty()) {
			rcode = ERR_NEEDMOREPARAMS;
			throw CommandException("INVITE :Not enough parameters.");
		}
		if (!serv.getChannelByName(ch)->clientIsInChannel(rqt.getClient())) {
			rcode = ERR_NOTONCHANNEL;
			throw CommandException(ch + " :You're not on that channel.");
		}
		if (!serv.getChannelByName(ch)->clientIsOperator(rqt.getClient())) {
			rcode = ERR_CHANOPRIVSNEEDED;
			throw CommandException(ch + " :You're not channel operator.");
		}
		if (!serv.searchNick(nick)) {
			rcode = ERR_NOSUCHNICK;
			throw CommandException(nick + " :No such nick/channel.");
		}
		if (serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(nick))) {
			rcode = ERR_USERONCHANNEL;
			throw CommandException(nick + ch + " :is already on channel.");
		}

		serv.joinChannel(ch, serv.getChannelByName(ch)->getPassword(), serv.getClientByNick(nick));
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), RPL_INVITING, "", "");
		rpl.reply(rqt.getClient(), nick + " " + ch);
	}
	catch (const Command::CommandException &e) {
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), rcode, "", "");
		rpl.reply(rqt.getClient(), e.what());
	}
}

void	Command::execPing(Request &rqt, SockInfo &sockInfo) // ✓
{
	Response reply(sockInfo.getHostname(), rqt.getClient()->getNickname(), "PONG ", rqt.getMsg());
	reply.reply(rqt.getClient());
}
