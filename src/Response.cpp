/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:14:16 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/10 19:29:36 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Response::Response(std::string from, std::string to, std::string cmd, std::string msg): _from(from), _to(to), _cmd(cmd), _msg(msg), _rtype(CLIENT)
{
	this->_endmsg = "\r\n";
}

Response::Response(std::string from, std::string to, RESP_CODE rcode, std::string cmd, std::string msg):_from(from), _cmd(cmd), _msg(msg)
{
	switch (rcode)
	{
	case 315:
		this->_to = "315 " + to;
		break;
	case 332:
		this->_to = "332 " + to;
		break;
	case 352:
		this->_to = "352 " + to;
		break;
	case 353:
		this->_to = "353 " + to;
		break;
	case 366:
		this->_to = "366 " + to;
		break;
	case 431:
		this->_to = "431 " + to;
		break;
	case 432:
		this->_to = "432 " + to;
		break;
	case 433:
		this->_to = "433 " + to;
		break;
	case 443:
		this->_to = "443 " + to;
		break;
	case 464:
		this->_to = "464 " + to;
		break;
	case 475:
		this->_to = "475 " + to;
		break;
	default:
		this->_to = "300 " + to;
		break;
	}
	this->_endmsg = "\r\n";
	this->_rtype = SERVER;
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
		this->_finalResponse = ":" + this->_from + " " + this->_to + this->_cmd + this->_msg + this->_endmsg;
	std::cout << "response to send: " << this->_finalResponse << std::endl; // esto fuera
	send(clt->getClientFd(), this->_finalResponse.c_str(), this->_finalResponse.length(), 0);
}

void	Response::reply(Client *clt, Channel &ch, std::string msg)
{
	std::string	finalMsg = clt->getNickname() + " " + ch.getName() + " :" + msg;
	std::cout << "response to send: " << this->_finalResponse << std::endl; // esto fuera
	send(clt->getClientFd(), finalMsg.c_str(), finalMsg.length(), 0);
}
