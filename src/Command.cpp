/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:50:19 by palucena          #+#    #+#             */
/*   Updated: 2024/05/01 21:30:55 by palucena         ###   ########.fr       */
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
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_PASSWDMISMATCH, ":Password incorrect", "");
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
	{
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NONICKNAMEGIVEN, "", "");
		reply.reply(rqt.getClient(), ":No nickname given");
	}
	else if (serv.searchNick(rqt.getMsg()) == true)
	{
		if (!rqt.getClient()->getNickname().empty())
		{
			Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NICKNAMEINUSE, "", "");
			reply.reply(rqt.getClient(), ":is already in use");
		}
		else
		{
			Response reply(serv.getHostname(), rqt.getMsg(), ERR_NICKNAMEINUSE, "", "");
			reply.reply(rqt.getClient(), ":is already in use");
		}
	}
	else if (forbiddenChar(rqt.getMsg()) == true)
	{
		Response reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_ERRONEUSNICKNAME, "", "");
		reply.reply(rqt.getClient(), ":Erroneus nickname");
	}
	else
	{
		rqt.getClient()->setNickname(rqt.getMsg());
		if (rqt.getClient()->getStatus() == AUTHENTICATED)
		{
			rqt.getClient()->changeStatus(CONNECTED);
			Response reply(serv.getHostname(), rqt.getClient()->getNickname(), RPL_WELCOME, "Hi " + rqt.getClient()->getNickname() + ". Welcome to our IRC proyect", "");
			reply.reply(rqt.getClient());
			serv.joinChannel("#bot", "", rqt.getClient());
			serv.joinChannel("#general", "", rqt.getClient());
		}
	}
}

void	Command::execUser(Request &rqt, SockInfo &serv)
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
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	std::string newChannelName = rqt.getMsg();
	if (newChannelName.find(' '))
		newChannelName = newChannelName.substr(0, newChannelName.find(' '));
	if (serv.getChannelByName(newChannelName) && serv.getChannelByName(newChannelName)->getInviteMode())
	{
		Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_INVITEONLYCHAN, "", "");
		reply.reply(rqt.getClient(), newChannelName + " :Cannot join channel (+i)");
	}
	else {
		std::string	key;
		if (rqt.getMsg().find(' ') != std::string::npos)
			key = rqt.getMsg().substr(newChannelName.size() + 1, rqt.getMsg().size() - 1);
		serv.joinChannel(newChannelName, key, rqt.getClient());
	}
}

std::string	getRdnBotMsg(Client *clt)
{
	switch (std::rand() % 5)
	{
		case 0:
			return (":Hola " + clt->getNickname() + " soy un bot");
			break ;
		case 1:
			return (":Has perdido");
			break ;
		case 2:
			return (":Sabias que la superficie de Kazajistan es de 2,725 millones de km cuadrados?");
			break ;
		case 3:
			return (":En un futuro podré mantener conversaciones reales, de momento te conformas con esto");
			break ;
		case 4:
			return (":Mi creador tiene poca originalidad lo siento pero no hay mucha variedad");
			break ;
	}
	return ("");
}

void	Command::execPrivmsg(Request &rqt, SockInfo &serv)
{
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	if (rqt.getMsg().empty())
	{
		//	ERR_NORECIPIENT
		return ;
	}
	if (rqt.getMsg().find(" ") != std::string::npos)
	{
		std::string to(rqt.getMsg().substr(0, rqt.getMsg().find(" ")));
		std::string msg(rqt.getMsg().substr(rqt.getMsg().find(" ") + 1, rqt.getMsg().length() - rqt.getMsg().find(" ") + 1));

		if (msg.empty())
		{
			//	ERR_NOTEXTTOSESND
			return ;
		}
		if (to[0] == '#')
		{
			// va a un canal
			if (serv.getChannelByName(to) != NULL)
			{
				Channel *chnl = serv.getChannelByName(to);
				if (chnl->clientIsInChannel(rqt.getClient())){
						Response resp(rqt.getClient()->getNickname(), rqt.getCmd(), to + " ", msg);
						chnl->broadcastChannel(rqt.getClient(), resp, false);
						if (chnl->getName() == "#bot"){
							Response resp("Kaladin", rqt.getCmd(), to + " ", getRdnBotMsg(rqt.getClient()));
							chnl->broadcastChannel(rqt.getClient(), resp, true);
						}
				} else{
					//	ERR_NOTONCHANNEL
				}
			}
		}
		else
		{
			// va a una persona	
			if (serv.searchNick(to)){
					if (to == "Kaladin"){
						Response resp("Kaladin", rqt.getCmd(), rqt.getClient()->getNickname() + " ", ":Lo siento, pero por el momento solo puedo responder en el canal #bot");
						resp.reply(rqt.getClient());
					}
					else{
						Response resp(rqt.getClient()->getNickname(), rqt.getCmd(), to + " ", msg);
						resp.reply(serv.getClientByNick(to));
					}
			} else{
				//	ERR_NOSUCHNICK
			}
		}
	}
	else
	{
		//	ERR_NOTEXTTOSEND
	}
}

bool	checkNumber(std::string str)
{
	size_t i = 0;
	while (i != str.size() - 1)
	{
		if (std::isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}

void	Command::execMode(Request &rqt, SockInfo &serv)
{
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	if (rqt.getMsg().find(' ') == std::string::npos)
		return ;
 	std::string	ch = rqt.getMsg().substr(0, rqt.getMsg().find(' '));
	std::string	flag = rqt.getMsg().substr(ch.size() + 1, rqt.getMsg().size() - 1);
	std::string	msg;
	if (flag.find(' ') != std::string::npos)
	{
		flag = flag.substr(0, flag.find(' '));
		msg = rqt.getMsg().substr(ch.size() + flag.size() + 2, rqt.getMsg().size() - 1);
	}
	RESP_CODE	rcode;

	try
	{
		if (rqt.getMsg().empty() || flag.empty())
		{
			rcode = ERR_NEEDMOREPARAMS;
			throw CommandException(" :Not enough parameters");
		}
		if (!serv.getChannelByName(ch))
		{
			rcode = ERR_NOSUCHCHANNEL;
			throw CommandException(ch + " :No such channel");
		}
		if (!serv.getChannelByName(ch)->clientIsInChannel(rqt.getClient()))
		{
			rcode = ERR_NOTONCHANNEL;
			throw CommandException(" :You're not on that channel");
		}
		if (!serv.getChannelByName(ch)->clientIsOperator(rqt.getClient()))
		{
			rcode = ERR_CHANOPRIVSNEEDED;
			throw CommandException(" :You're not channel operator");
		}
		else if (flag.size() == 2)
		{
			if (flag == "+i") // Set Invite-only channel
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(+i) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setInviteMode(true);
			}
			else if (flag == "-i") // Remove Invite-only channel
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(-i) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setInviteMode(false);
			}
			else if (flag == "+t") // Set the restrictions of the TOPIC command to channel operators
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(+t) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setOpenTopic(false);
			}
			else if (flag == "-t") // Remove the restrictions of the TOPIC command to channel operators
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(-t) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setOpenTopic(true);
			}
			else if (flag == "+k") // Set the channel key (password)
			{
				if (msg.empty())
				{
					rcode = ERR_NEEDMOREPARAMS;
					throw CommandException(" :Not enough parameters");
				}
				serv.getChannelByName(ch)->setPassword(msg);
				serv.getChannelByName(ch)->setThereIsPasswd(true);
			}
			else if (flag == "-k") // Remove the channel key (password)
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(-k) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setPassword("");
				serv.getChannelByName(ch)->setThereIsPasswd(false);
			}
			else if (flag == "+o") // Give channel operator privilege
			{
				if (msg.empty())
				{
					rcode = ERR_NEEDMOREPARAMS;
					throw CommandException(" :Not enough parameters");
				}
				if (!serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(msg))) {
					rcode = ERR_NOSUCHNICK;
					throw CommandException(" " + msg + " :No such nick/channel");
				}
				serv.getChannelByName(ch)->addOperator(serv.getClientByNick(msg));
			}
			else if (flag == "-o") // Take channel operator privilege
			{
				if (msg.empty())
				{
					rcode = ERR_NEEDMOREPARAMS;
					throw CommandException(" :Not enough parameters");
				}
				if (!serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(msg))) {
					rcode = ERR_NOSUCHNICK;
					throw CommandException(" " + msg + " :No such nick/channel");
				}
				serv.getChannelByName(ch)->removeClientAsOperator(serv.getClientByNick(msg));
			}
			else if (flag == "+l") // Set the user limit to channel
			{
				if (!checkNumber(msg))
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(+l) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setUserLimit(atoi(msg.c_str()));
			}
			else if (flag == "-l") // Remove the user limit to channel
			{
				if (!msg.empty())
				{
					rcode = ERR_INVALIDMODEPARAM;
					throw CommandException("(-l) " + msg + " :invalid parameter");
				}
				serv.getChannelByName(ch)->setUserLimit(-1);
			}
			else
			{
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
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	if (rqt.getMsg().empty() || rqt.getMsg().find(' ') == std::string::npos || rqt.getMsg().find(':') == std::string::npos)
	{
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NEEDMOREPARAMS, "", "");
		rpl.reply(rqt.getClient(), " :Not enough parameters");
		return ;
	}

	std::string	ch = rqt.getMsg().substr(0, rqt.getMsg().find(' '));
	std::string	reason = rqt.getMsg().substr(rqt.getMsg().find(':') - 1, rqt.getMsg().size() - 1);

	if (!serv.getChannelByName(ch))
	{
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOSUCHCHANNEL, "", "");
		rpl.reply(rqt.getClient(), ch + " :No such channel");
	}
	else if (!serv.getChannelByName(ch)->clientIsInChannel(rqt.getClient()))
	{
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOTONCHANNEL, "", "");
		rpl.reply(rqt.getClient(), " :You're not on that channel");
	}
	else
	{
		serv.getChannelByName(ch)->removeClientFromChannel(rqt.getClient());
		Response partReply(rqt.getClient()->getNickname(), "", "PART ", serv.getChannelByName(ch)->getName() + reason);
		partReply.reply(rqt.getClient());
		serv.getChannelByName(ch)->broadcastChannel(rqt.getClient(), partReply, false);
	}
}

void	Command::execInvite(Request &rqt, SockInfo &serv)
{
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	RESP_CODE	rcode;

	try
	{
		if (rqt.getMsg().empty() || rqt.getMsg().find(' ') == std::string::npos)
			throw CommandException("INVITE :Not enough parameters.");

		std::string	nick = rqt.getMsg().substr(0, rqt.getMsg().find(" "));
		std::string	ch = rqt.getMsg().substr(nick.size() + 1, rqt.getMsg().size() - 1);

		if (nick.empty() || ch.empty())
		{
			rcode = ERR_NEEDMOREPARAMS;
			throw CommandException("INVITE :Not enough parameters.");
		}
		if (!serv.getChannelByName(ch)->clientIsInChannel(rqt.getClient()))
		{
			rcode = ERR_NOTONCHANNEL;
			throw CommandException(ch + " :You're not on that channel.");
		}
		if (!serv.getChannelByName(ch)->clientIsOperator(rqt.getClient()))
		{
			rcode = ERR_CHANOPRIVSNEEDED;
			throw CommandException(ch + " :You're not channel operator.");
		}
		if (!serv.searchNick(nick)) {
			rcode = ERR_NOSUCHNICK;
			throw CommandException(nick + " :No such nick/channel.");
		}
		if (serv.getChannelByName(ch)->clientIsInChannel(serv.getClientByNick(nick)))
		{
			rcode = ERR_USERONCHANNEL;
			throw CommandException(nick + ch + " :is already on channel.");
		}

		serv.joinChannel(ch, serv.getChannelByName(ch)->getPassword(), serv.getClientByNick(nick));
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), RPL_INVITING, "", "");
		rpl.reply(rqt.getClient(), nick + " " + ch);
	}
	catch (const Command::CommandException &e)
	{
		Response rpl(serv.getHostname(), rqt.getClient()->getNickname(), rcode, "", "");
		rpl.reply(rqt.getClient(), e.what());
	}
}

void	Command::execPing(Request &rqt, SockInfo &serv)
{
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
	Response reply(serv.getHostname(), "PONG", rqt.getClient()->getNickname() + " ", rqt.getMsg());
	reply.reply(rqt.getClient());
}

void Command::execTopic(Request &rqt, SockInfo &serv)
{
	if (rqt.getClient()->getStatus() != CONNECTED)
		return ;
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
	std::string restOfMsg = rqt.getMsg().substr(channelName.length(), std::string::npos);
	Channel	*ch = serv.getChannelByName(channelName);
	if (!restOfMsg.empty())
	{
		//	Cambia el topic del canal
		if (ch == NULL)
		{
			//	Si no encuentra el canal -> ERR_NOSUCHCHANNEL
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOSUCHCHANNEL, ":" + channelName + " no such channel", "");
			reply.reply(rqt.getClient());
			return ;
		}
		if (!ch->clientIsInChannel(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOTONCHANNEL, ":You are not on that channel", "");
			reply.reply(rqt.getClient());
			//	Si lo encuentra paro el cliente no esta en el canal -> ERR_NOTONCHANNEL
			return ;
		}
		if (!ch->getOpenTopic() && !ch->clientIsOperator(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_CHANOPRIVSNEEDED, ch->getName() + " :You are not channel operator", "");
			reply.reply(rqt.getClient());
			//	Si el canal requiere permisos para que se cambie el topic -> ERR_CHANOPRIVSNEEDED
			return ;
		}
		ch->setTopic(restOfMsg);
		Response JoinReply(rqt.getClient()->getNickname(), "", "TOPIC " + ch->getName(), restOfMsg);
		ch->broadcastChannel(rqt.getClient(), JoinReply, false);
		//	?? Devuelve un broadcast en el canal con el nuevo topic ??
		Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), RPL_TOPIC, ch->getName() + ch->getTopic(), "");
		reply.reply(rqt.getClient());
		return ;
	}
	else
	{
		//	Devuelve el topic que tiene ese canal
		if (ch == NULL)
		{
			//	Si no encuentra el canal -> ERR_NOSUCHCHANNEL
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOSUCHCHANNEL,  ":" + channelName + " no such channel", "");
			reply.reply(rqt.getClient());
			return ;
		}
		if (!ch->clientIsInChannel(rqt.getClient()))
		{
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), ERR_NOTONCHANNEL, ":You are not on that channel", "");
			reply.reply(rqt.getClient());
			//	Si lo encuentra paro el cliente no esta en el canal -> ERR_NOTONCHANNEL
			return ;
		}
		if (!ch->getTopic().empty()){
			// Si tiene topic el canal -> RPL_TOPIC
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), RPL_TOPIC, ch->getName() + ch->getTopic(), "");
			reply.reply(rqt.getClient());
			return ;
		}else{
			// Si no tiene topic el canal -> RPL_NOTOPIC
			Response	reply(serv.getHostname(), rqt.getClient()->getNickname(), RPL_NOTOPIC, ch->getName() + " :no topic is set", "");
			reply.reply(rqt.getClient());
			return ;
		}
	}
}
