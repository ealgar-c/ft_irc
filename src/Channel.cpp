/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:21:17 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/10 16:51:25 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel(): _name("Default"), _passwd(""), _topic("")
{}

Channel::Channel(std::string name, std::string password): _name(name), _passwd(password), _topic("")
{
}

Channel::Channel(const Channel &toCopy): _name(toCopy.getName()), _passwd(toCopy.getPassword()), _topic(toCopy.getTopic()), _operatorClients(toCopy._operatorClients), _clientsConnected(toCopy._clientsConnected)
{}

Channel::~Channel()
{}

Channel &Channel::operator=(const Channel &toEqual)
{
	if (this != &toEqual)
	{
		this->_name = toEqual.getName();
		this->_clientsConnected = toEqual._clientsConnected;
		this->_passwd = toEqual.getPassword();
		this->_topic = toEqual.getTopic();
		this->_operatorClients = toEqual._operatorClients;
	}
	return (*this);
}

std::string	Channel::getPassword() const
{
	return (this->_passwd);
}

std::string	Channel::getTopic() const
{
	return (this->_topic);
}

std::string	Channel::getName() const
{
	return (this->_name);
}

std::vector<Client *>	Channel::getClientsConnected(void) const
{
	return (this->_clientsConnected);
}

static std::string getNameList(std::vector<Client *> cltList)
{
	std::string list = ":";

	for (std::vector<Client *>::const_iterator v_it = cltList.begin(); v_it != cltList.end(); v_it++)
	{
		list.append((*v_it)->getNickname() + " ");
	}
	return list;
}

void	Channel::addClientToChannel(Client *newClient, SockInfo &serv)
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsConnected.begin(); v_it != this->_clientsConnected.end(); v_it++)
	{
		if (*v_it == newClient)
		{
			Response reply(serv.getHostname(), newClient->getNickname(), ERR_USERONCHANNEL, "", ":is already on channel");
			reply.reply(newClient);
			return ;
		}
	}
	// comprobar contraseña
	this->_clientsConnected.push_back(newClient);
	Response JoinReply(newClient->getNickname(), "", "JOIN ", this->getName());
	Response namelist(serv.getHostname(), newClient->getNickname() + " = " + this->getName(), RPL_NAMREPLY, getNameList(this->_clientsConnected), "");
	Response endname(serv.getHostname(), newClient->getNickname(), RPL_ENDOFNAMES, "end of the list", "");
	// enviar RPL_TOPIC o RPLY_NOTOPIC
	// enviar RPL_NAMEREPLY
	JoinReply.reply(newClient);
	this->broadcastChannel(newClient, JoinReply, false);
	namelist.reply(newClient);
	endname.reply(newClient);
}

bool	Channel::clientIsInChannel(const Client *clt) const
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsConnected.begin(); v_it != this->_clientsConnected.end();v_it++)
	{
		if ((*v_it) == clt)
			return true;
	}
	return false;
}

void	Channel::removeClientFromChannel(const Client *clt)
{
	int	i = 0;
	for (std::vector<Client *>::const_iterator v_it = this->_clientsConnected.begin(); v_it != this->_clientsConnected.end();v_it++)
	{
		if ((*v_it) == clt)
			break ;
		i++;
	}
	this->_clientsConnected.erase(this->_clientsConnected.begin() + i);
}

bool	Channel::clientIsOperator(const Client *clt) const
{
	for(std::vector<Client *>::const_iterator v_it = this->_operatorClients.begin(); v_it != this->_operatorClients.end(); v_it++)
	{
		if (*v_it == clt)
			return true;
	}
	return false;
}

void	Channel::broadcastChannel(Client *newClt, Response &resp, bool itself) const
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsConnected.begin(); v_it != this->_clientsConnected.end(); v_it++)
	{
		if ((*v_it) == newClt && !itself)
			continue ;
		resp.reply((*v_it));
	}
}