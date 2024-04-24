/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/04/23 17:37:36 by ealgar-c         ###   ########.fr       */
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

void	Command::execNick(Request &rqt, SockInfo &serv)
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
	if (serv.getChannelByName(newChannelName) && serv.getChannelByName(newChannelName)->getInviteMode()) {
		Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_INVITEONLYCHAN, "", "");
		reply.reply(rqt.getClient(), newChannelName + " :Cannot join channel (+i)");
	}
	else
		serv.joinChannel(newChannelName, rqt.getMsg().substr(newChannelName.size() - 1, rqt.getMsg().size() - 1), rqt.getClient());
}

void	Command::execPrivmsg(Request &rqt, SockInfo &serv)
{
	std::cout << "cmd -> " << rqt.getCmd() << " mensaje-> " << rqt.getMsg() << std::endl;
	(void)serv;
	if (rqt.getMsg().find(" ") != std::string::npos)
	{
		std::string to(rqt.getMsg().substr(0, rqt.getMsg().find(" ")));
		std::string msg(rqt.getMsg().substr(rqt.getMsg().find(" ") + 1, rqt.getMsg().length() - rqt.getMsg().find(" ") + 1));
		std::cout << "se ha recibido el mensaje ->" << msg << "<- enviado para ->" << to << "<-" << std::endl;
	}
	/*
	
		RESPUESTAS QUE DAR ->
			ERR_NORECIPIENT                 ERR_NOTEXTTOSEND (no hay msg)
        	ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL (no tienes permisos para mandar msgs?)
        	ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
        	ERR_NOSUCHNICK (esa persona no existe)
        	RPL_AWAY (Esta persona se ha ido (creo) pero eso no tenemos q hacerlo)

	*/
	/* 
	std::string dest;
	if (rqt.getMsg().find("#") != std::string::npos)
		dest = rqt.getMsg().substr(rqt.getMsg().find("#"), rqt.getMsg().find(" ") - rqt.getMsg().find("#"));
	else
		dest = rqt.getMsg().substr(rqt.getMsg().find(" " + 1), rqt.getMsg().find(" ") - rqt.getMsg().find("#"));
	std::string finalMsg = rqt.getMsg().erase(0, dest.length() + 1);
	std::cout << "dest -> (" << dest << ")" << std::endl;
	std::cout << "final -> (" << finalMsg << ")" << std::endl;
	Response resp(rqt.getClient()->getNickname(), rqt.getCmd(), dest + " ", finalMsg);
	sockInfo.getChannelByName(dest)->broadcastChannel(rqt.getClient(), resp, false);
	*/
}

bool	checkNumber(std::string str)
{
	size_t i = 0;
	while (i != str.length())
	{
		if (std::isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}

void	Command::execMode(Request &rqt, SockInfo &serv)
{
 	std::string	ch = rqt.getMsg().substr(0, rqt.getMsg().find(' '));
	std::string	flag = rqt.getMsg().substr(ch.size() + 1, rqt.getMsg().size() - 1);
	flag = flag.substr(0, flag.find(' '));
	std::string	msg = rqt.getMsg().substr(ch.size() + flag.size() + 2, rqt.getMsg().size() - 1);
	RESP_CODE	rcode;

	std::cout << "Mensaje de MODE: ." << rqt.getMsg() << "." << std::endl;
	std::cout << "ch: ." << ch << "." << std::endl;
	std::cout << "flag: ." << flag << "." << std::endl;
	std::cout << "msg: ." << msg << "." << std::endl;

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
			if (flag == "+i")
				serv.getChannelByName(ch)->setInviteMode(true);
			else if (flag == "-i")
				serv.getChannelByName(ch)->setInviteMode(false);
			else if (flag == "+t")
				serv.getChannelByName(ch)->setOpenTopic(true);
			else if (flag == "-t")
				serv.getChannelByName(ch)->setOpenTopic(false);
			else if (flag == "+k") {
				if (msg.empty()) {
					rcode = ERR_NEEDMOREPARAMS;
					throw CommandException(" :Not enough parameters");
				}
				serv.getChannelByName(ch)->setPassword(msg);
				serv.getChannelByName(ch)->setThereIsPasswd(true);
			}
			else if (flag == "-k") {
				serv.getChannelByName(ch)->setPassword("");
				serv.getChannelByName(ch)->setThereIsPasswd(false);
			}
			else if (flag == "+o") {
				if (!serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(msg))) {
					rcode = ERR_NOSUCHNICK;
					throw CommandException(" " + msg + " :No such nick/channel");
				}
				serv.getChannelByName(ch)->addOperator(serv.getClientByNick(msg));
			}
			else if (flag == "-o") {
				if (!serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(msg))) {
					rcode = ERR_NOSUCHNICK;
					throw CommandException(" " + msg + " :No such nick/channel");
				}
				serv.getChannelByName(ch)->removeClientAsOperator(serv.getClientByNick(msg));
			}
			else if (flag == "+l") {
				if (!checkNumber(msg)) {
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(+l) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setUserLimit(atoi(msg.c_str()));
			}
			else if (flag == "-l")
				serv.getChannelByName(ch)->setUserLimit(-1);
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
	(void)serv;
}

void	Command::execInvite(Request &rqt, SockInfo &serv)
{
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

void	execTopic(Request &rqt, SockInfo &serv)
{
	(void)rqt;
	(void)serv;
}

void	Command::execPing(Request &rqt, SockInfo &serv)
{
	Response reply(serv.getHostname(), "PONG", rqt.getClient()->getNickname() + " ", rqt.getMsg());
	reply.reply(rqt.getClient());
}

void Command::execTopic(Request &rqt, SockInfo &serv)
{
	(void)rqt;
	(void)serv;
	std::cout << "msg received ->" << rqt.getMsg() << "<- en la pos " << rqt.getMsg().find("#") << std::endl;
	if (rqt.getMsg().empty())
	{
		// Si no hay msg -> ERR_NEEDMOREPARAMS
				
	}
	std::string channelName;
	if (rqt.getMsg().find("#") == 0)
		channelName = rqt.getMsg().substr(rqt.getMsg().find("#"), rqt.getMsg().find(" ") - rqt.getMsg().find("#"));
	else{
		// Error (no se cual)
		return ;
	}
	std::cout << "el channel name es ->" << channelName << std::endl;
	std::string restOfMsg = rqt.getMsg().substr(channelName.length(), std::string::npos);
	Channel	*ch = serv.getChannelByName(channelName);
	if (!restOfMsg.empty())
	{
		//	Cambia el topic del canal
		if (ch == NULL)
		{
			//	Si no encuentra el canal -> ERR_NOSUCHCHANNEL
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOSUCHCHANNEL, "", "");
			reply.reply(rqt.getClient());
			return ;
		}
		if (!ch->clientIsInChannel(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOTONCHANNEL, "", "");
			reply.reply(rqt.getClient());
			//	Si lo encuentra paro el cliente no esta en el canal -> ERR_NOTONCHANNEL
			return ;
		}
		if (!ch->getOpenTopic() && !ch->clientIsOperator(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_CHANOPRIVSNEEDED, "", "");
			reply.reply(rqt.getClient());
			//	Si el canal requiere permisos para que se cambie el topic -> ERR_CHANOPRIVSNEEDED
			return ;
		}
		ch->setTopic(restOfMsg);
		Response JoinReply(serv.getHostname(), "", "TOPIC " + ch->getName(), restOfMsg);
		ch->broadcastChannel(rqt.getClient(), JoinReply, true);
		//	?? Devuelve un broadcast en el canal con el nuevo topic ??
	}
	else
	{
		//	Devuelve el topic que tiene ese canal
		if (ch == NULL)
		{
			//	Si no encuentra el canal -> ERR_NOSUCHCHANNEL
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOSUCHCHANNEL, "", "");
			reply.reply(rqt.getClient());
			return ;
		}
		if (!ch->clientIsInChannel(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOTONCHANNEL, "", "");
			reply.reply(rqt.getClient());
			//	Si lo encuentra paro el cliente no esta en el canal -> ERR_NOTONCHANNEL
			return ;
		}
		if (!ch->getTopic().empty()){
			// Si tiene topic el canal -> RPL_TOPIC
		}else{
			// Si no tiene topic el canal -> RPL_NOTOPIC
		}
	}
}
