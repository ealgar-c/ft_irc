/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:14:16 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/01 22:06:59 by ealgar-c         ###   ########.fr       */
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
		case 001:
			this->_to = "001 " + to;
			break;
		case 315:
			this->_to = "315 " + to;
			break;
		case 331:
			this->_to = "331 " + to;
			break;
		case 332:
			this->_to = "332 " + to;
			break;
		case 341:
			this->_to = "341 " + to;
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
		case 401:
			this->_to = "401 " + to;
			break;
		case 403:
			this->_to = "403 " + to;
			break;
		case 411:
			this->_to = "411 " + to;
			break;
		case 412:
			this->_to = "412 " + to;
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
		case 442:
			this->_to = "442 " + to;
			break;
		case 443:
			this->_to = "443 " + to;
			break;
		case 461:
			this->_to = "461 " + to;
			break;
		case 464:
			this->_to = "464 " + to;
			break;
		case 471:
			this->_to = "471 " + to;
		case 472:
			this->_to = "472 " + to;
			break;
		case 473:
			this->_to = "473 " + to;
			break;
		case 475:
			this->_to = "475 " + to;
			break;
		case 482:
			this->_to = "482 " + to;
			break;
		case 696:
			this->_to = "696 " + to;
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

Response::~Response() {}

Response &Response::operator=(const Response &toEqual)
{
	(void)toEqual;
	return (*this);
}

void	Response::setFrom(std::string from)
{
	this->_from = from;
}

void	Response::setTo(std::string to)
{
	this->_to = to;
}

void	Response::setCmd(std::string cmd)
{
	this->_cmd = cmd;
}

void	Response::setMsg(std::string msg)
{
	this->_msg = msg;
}

void	Response::reply(Client *clt)
{
	if (this->_rtype == SERVER)
		this->_finalResponse = ":" + this->_from + " " + this->_to + " " + this->_cmd + this->_endmsg;
	else
		this->_finalResponse = ":" + this->_from + " " + this->_to + " " + this->_cmd + this->_msg + this->_endmsg;
	std::cout << "response to send: " << this->_finalResponse << std::endl;
	send(clt->getClientFd(), this->_finalResponse.c_str(), this->_finalResponse.length(), 0);
}

void	Response::reply(Client *clt, std::string msg)
{
	std::string finalMsg = ":" + this->_from + " " + this->_to + " " + msg + this->_endmsg;
	std::cout << "response to send: " << finalMsg << std::endl; // esto fuera
	send(clt->getClientFd(), finalMsg.c_str(), finalMsg.length(), 0);
}
