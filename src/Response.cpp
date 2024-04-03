/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:14:16 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/03 16:50:08 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Response::Response(std::string from, std::string to, std::string cmd): _from(from), _to(to), _cmd(cmd)
{
	this->_rtype = CLIENT;
	this->_endmsg = "\r\n";
}

Response::Response(std::string from, std::string to, RESP_CODE rcode, std::string cmd)
{
	this->_from = from;
	switch (rcode)
	{
	case 433:
		this->_to = "433 " + to;
		break;
	case 443:
		this->_to = "443 " + to;
		break;
	case 332:
		this->_to = "332 " + to;
		break;
	case 352:
		this->_to = "352 " + to;
		break;
	case 315:
		this->_to = "315 " + to;
		break;
	case 464:
		this->_to = "464 " + to;
	default:
		this->_to = "300 " + to;
		break;
	}
	this->_cmd = cmd;
	this->_rtype = SERVER;
	this->_endmsg = "\r\n";
}

Response::Response(const Response &toCopy)
{
	(void)toCopy;
}

Response::~Response()
{
	
}

Response &Response::operator=(const Response &toEqual)
{
	(void)toEqual;
	return (*this);
}

/* void	Response::generateResponse(std::string request)
{
	
} */

void	Response::reply(Client *clt)
{
	if (this->_rtype == SERVER)
		this->_finalResponse = ":" + this->_from + " " + this->_to + " " + this->_cmd + this->_endmsg;
	else
		this->_finalResponse = ":" + this->_from + " " + this->_cmd + this->_endmsg;
	std::cout << "response to send: " << this->_finalResponse << std::endl;
	send(clt->getClientFd(), this->_finalResponse.c_str(), this->_finalResponse.length(), 0);
}