/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:21:17 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/09 17:28:52 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel(): _name("Default"), _passwd(""), _topic("")
{}

Channel::Channel(std::string name, std::string password): _name(name), _passwd(password), _topic("")
{}

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

void	Channel::addClientToChannel(Client *newClient, SockInfo &serv)
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsConnected.begin(); v_it != this->_clientsConnected.end(); v_it++)
	{
		if (*v_it == newClient)
		{
		//	if ()
			Response reply(serv.getHostname(), newClient->getNickname(), ERR_USERONCHANNEL, "", ":is already on channel");
			reply.reply(newClient);
			return ;
		}
	}
	// comprobar contraseña
	if (this->_operatorClients.size() == 0)
		this->_operatorClients.push_back(newClient);
	this->_clientsConnected.push_back(newClient);
	Response reply(newClient->getNickname(), "", "JOIN ", this->getName());
	// enviar RPL_NAMEREPLY
	// enviar RPL_TOPIC o RPLY_NOTOPIC
	reply.reply(newClient);
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
