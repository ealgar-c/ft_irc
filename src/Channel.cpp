/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:21:17 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/24 17:31:38 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Channel::Channel(): _name("Default"), _thereIsPasswd(false), _passwd(""), _openTopic(false), _topic(""), _inviteMode(false), _userLimit(-1)
{}

Channel::Channel(std::string name, std::string password): _name(name), _thereIsPasswd(false), _passwd(password), _openTopic(true), _topic(""), _inviteMode(false), _userLimit(-1)
{}

Channel::Channel(const Channel &toCopy): _name(toCopy.getName()), _thereIsPasswd(toCopy._thereIsPasswd), _passwd(toCopy.getPassword()), _openTopic(toCopy._openTopic), _topic(toCopy.getTopic()), _inviteMode(toCopy.getInviteMode()), _userLimit(toCopy._userLimit), _operatorClients(toCopy._operatorClients), _clientsConnected(toCopy._clientsConnected)
{}

Channel::~Channel()
{}

Channel &Channel::operator=(const Channel &toEqual)
{
	if (this != &toEqual)
	{
		this->_name = toEqual.getName();
		this->_thereIsPasswd = toEqual.getThereIsPasswd();
		this->_clientsConnected = toEqual._clientsConnected;
		this->_passwd = toEqual.getPassword();
		this->_openTopic = toEqual.getOpenTopic();
		this->_topic = toEqual.getTopic();
		this->_inviteMode = toEqual.getInviteMode();
		this->_operatorClients = toEqual._operatorClients;
		this->_userLimit = toEqual.getUserLimit();
	}
	return (*this);
}

std::string	Channel::getPassword() const
{
	return (this->_passwd);
}

void	Channel::setPassword(std::string str)
{
	this->_passwd = str;
}

bool	Channel::getOpenTopic() const
{
	return (this->_openTopic);
}

void	Channel::setOpenTopic(bool toSet)
{
	this->_openTopic = toSet;
}

std::string	Channel::getTopic() const
{
	return (this->_topic);
}

void	Channel::setTopic(std::string newTopic)
{
	this->_topic = newTopic;
}

std::string	Channel::getName() const
{
	return (this->_name);
}

bool	Channel::getThereIsPasswd() const
{
	return (this->_thereIsPasswd);
}

void	Channel::setThereIsPasswd(bool toSet)
{
	this->_thereIsPasswd = toSet;
}

bool	Channel::getInviteMode() const
{
	return (this->_inviteMode);
}

void	Channel::setInviteMode(bool toSet)
{
	this->_inviteMode = toSet;
}

int	Channel::getUserLimit() const
{
	return (this->_userLimit);
}

void	Channel::setUserLimit(int nb)
{
	this->_userLimit = nb;
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
	if (this->_operatorClients.size() == 0)
		this->_operatorClients.push_back(newClient);
	this->_clientsConnected.push_back(newClient);
	Response JoinReply(newClient->getNickname(), "", "JOIN ", this->getName());
	Response namelist(serv.getHostname(), newClient->getNickname() + " = " + this->getName(), RPL_NAMREPLY, getNameList(this->_clientsConnected), "");
	Response endname(serv.getHostname(), newClient->getNickname(), RPL_ENDOFNAMES, "end of the list", "");
	// enviar RPL_TOPIC o RPLY_NOTOPIC
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

void	Channel::removeClientAsOperator(const Client *clt)
{
	int	i = 0;
	for (std::vector<Client *>::const_iterator v_it = this->_operatorClients.begin(); v_it != this->_operatorClients.end();v_it++)
	{
		if ((*v_it) == clt)
			break ;
		i++;
	}
	this->_operatorClients.erase(this->_operatorClients.begin() + i);
}

void	Channel::addOperator(Client *clt)
{
	if (!this->clientIsOperator(clt))
		this->_operatorClients.push_back(clt);
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