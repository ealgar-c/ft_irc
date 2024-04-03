/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:02:12 by palucena          #+#    #+#             */
/*   Updated: 2024/04/03 20:31:51 by palucena         ###   ########.fr       */
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
	this->_cmd = toCopy._cmd;
	this->_msg = toCopy._msg;
}

Request::Request(std::string cmd, Client *clt, SockInfo &sockInfo)
{
	(void)sockInfo;

//	std::cout << "[REQUESTEADO] " << cmd << "[eor]" << std::endl;

	if (cmd.find("PASS") != std::string::npos)
	{
		this->_cmd = "PASS";
		Command::execPass(cmd, clt, sockInfo);
	}
	else if (cmd.find("NICK") != std::string::npos)
	{
		this->_cmd = "NICK";
		Command::execNick(cmd, clt, sockInfo);
	}
	else if (cmd.find("USER") != std::string::npos) // ESTOY CON ESTO
	{
		this->_cmd = "USER";
		Command::execUser(cmd, clt, sockInfo);
	}
	else if (cmd.find("JOIN") != std::string::npos)
	{
		this->_cmd = "JOIN";
		Command::execJoin(cmd, clt, sockInfo);
	}
	else if (cmd.find("PRIVMSG") != std::string::npos)
	{
		this->_cmd = "PRIVMSG";
		Command::execPrivmsg(cmd, clt, sockInfo);
	}
	else if (cmd.find("WHO") != std::string::npos)
	{
		this->_cmd = "WHO";
		Command::execWho(cmd, clt, sockInfo);
	}
	else if (cmd.find("PING") != std::string::npos)
	{
		this->_cmd = "PING";
		Command::execPing(cmd, clt, sockInfo);
	}
}

Request::~Request()
{ }

Request	&Request::operator=(const Request &toCopy)
{
	(void)toCopy;
	return (*this);
}

std::string	Request::getCmd(void) const
{
	return (this->_cmd);
}

std::string	Request::getMsg(void) const
{
	return (this->_msg);
}

void	Request::setCmd(const std::string newCmd)
{
	this->_cmd = newCmd;
}

void	Request::setMsg(const std::string newMsg)
{
	this->_msg = newMsg;
}
