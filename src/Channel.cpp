/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:21:17 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/03 20:42:29 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel(): _name("Default")
{
	
}

Channel::Channel(std::string name): _name(name)
{
	
}

Channel::Channel(const Channel &toCopy): _name(toCopy.getName())
{

}

Channel::~Channel()
{

}

Channel &Channel::operator=(const Channel &toEqual)
{
	if (this != &toEqual)
	{
		this->_name = toEqual.getName();
		this->_clientsconnected = toEqual._clientsconnected;
	}
	return (*this);
}

std::string	Channel::getName() const
{
	return (this->_name);
}

std::vector<Client *>	Channel::getClientsConnected(void) const
{
	return (this->_clientsconnected);
}

void	Channel::addClientToChannel(Client *newClient, SockInfo &serv)
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsconnected.begin(); v_it != this->_clientsconnected.end(); v_it++)
	{
		if (*v_it == newClient)
		{
			Response reply(serv.getHostname(), "ealgar-c", ERR_USERONCHANNEL, ":is already on channel");
			reply.reply(newClient);
			return ;
		}
	}
	this->_clientsconnected.push_back(newClient);
	Response reply("ealgar-c", "ealgar-c", "JOIN " + this->getName());
	reply.reply(newClient);
}

bool	Channel::clientIsInChannel(const Client *clt) const
{
	for (std::vector<Client *>::const_iterator v_it = this->_clientsconnected.begin(); v_it != this->_clientsconnected.end();v_it++)
	{
		if ((*v_it) == clt)
			return true;
	}
	return false;
}

void	Channel::removeClientFromChannel(const Client *clt)
{
	int	i = 0;
	for (std::vector<Client *>::const_iterator v_it = this->_clientsconnected.begin(); v_it != this->_clientsconnected.end();v_it++)
	{
		if ((*v_it) == clt)
			break ;
		i++;
	}
	this->_clientsconnected.erase(this->_clientsconnected.begin() + i);
}