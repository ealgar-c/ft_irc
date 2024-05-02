/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:02:12 by palucena          #+#    #+#             */
/*   Updated: 2024/05/02 16:13:13 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Request::Request()
{
	this->_cmd.clear();
	this->_msg.clear();
}

Request::Request(const Request &toCopy)
{
	this->_cmd = toCopy.getCmd();
	this->_msg = toCopy.getMsg();
	this->_client = toCopy.getClient();
}

Request::Request(std::string cmd, Client *clt)
{
	this->_client = clt;

	if (cmd.find("PASS") != std::string::npos)
	{
		this->_cmd = "PASS";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("NICK") != std::string::npos)
	{
		this->_cmd = "NICK";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("USER") != std::string::npos)
	{
		this->_cmd = "USER";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("JOIN") != std::string::npos)
	{
		this->_cmd = "JOIN";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("PRIVMSG") != std::string::npos)
	{
		this->_cmd = "PRIVMSG";
		this->_msg = cmd.substr(8, cmd.size() - 1);
	}
	else if (cmd.find("MODE") != std::string::npos)
	{
		this->_cmd = "MODE";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("INVITE") != std::string::npos)
	{
		this->_cmd = "INVITE";
		this->_msg = cmd.substr(7, cmd.size() - 1);
	}
	else if (cmd.find("KICK") != std::string::npos)
	{
		this->_cmd = "KICK";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("PART") != std::string::npos)
	{
		this->_cmd = "PART";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("TOPIC") != std::string::npos)
	{
		this->_cmd = "TOPIC";
		this->_msg = cmd.substr(6, cmd.size() - 1);
	}
	else if (cmd.find("PING") != std::string::npos)
	{
		this->_cmd = "PING";
		this->_msg = cmd.substr(5, cmd.size() - 1);
	}
	else if (cmd.find("TOPIC") != std::string::npos)
	{
		this->_cmd = "TOPIC";
		this->_msg = cmd.substr(6, cmd.size() - 1);
	}
}

Request::~Request() {}

Request &Request::operator=(const Request &toCopy)
{
	(void)toCopy;
	return (*this);
}

void	Request::reply(SockInfo &sockInfo)
{
	if (this->_cmd == "PASS")
		Command::execPass(*this, sockInfo);
	else if (this->_cmd == "NICK")
		Command::execNick(*this, sockInfo);
	else if (this->_cmd == "USER")
		Command::execUser(*this, sockInfo);
	else if (this->_cmd == "JOIN")
		Command::execJoin(*this, sockInfo);
	else if (this->_cmd == "PRIVMSG")
		Command::execPrivmsg(*this, sockInfo);
	else if (this->_cmd == "MODE")
		Command::execMode(*this, sockInfo);
	else if (this->_cmd == "PART")
		Command::execPart(*this, sockInfo);
	else if (this->_cmd == "INVITE")
		Command::execInvite(*this, sockInfo);
	else if (this->_cmd == "PING")
		Command::execPing(*this, sockInfo);
	else if (this->_cmd == "TOPIC")
		Command::execTopic(*this, sockInfo);
}

std::string	Request::getCmd(void) const
{
	return (this->_cmd);
}

std::string	Request::getMsg(void) const
{
	return (this->_msg);
}

Client	*Request::getClient(void) const
{
	return (this->_client);
}

void	Request::setCmd(const std::string newCmd)
{
	this->_cmd = newCmd;
}

void	Request::setMsg(const std::string newMsg)
{
	this->_msg = newMsg;
}

void	Request::setClient(Client *clt)
{
	this->_client = clt;
}
