/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:13:59 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/15 17:58:22 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Client;
class Response;
class SockInfo;

class Channel
{
	private:
		std::string				_name;
		std::string				_passwd;
		bool					_openTopic;
		std::string				_topic;
		bool					_inviteMode;
		std::vector<Client *>	_operatorClients;
		std::vector<Client *>	_clientsConnected;
	public:
		Channel();
		Channel(std::string, std::string);
		Channel(const Channel &);
		~Channel();
		Channel &operator=(const Channel &);
		std::string	getName() const;
		std::string	getPassword() const;
		bool		getOpenTopic() const;
		std::string	getTopic() const;
		bool		getInviteMode() const;
		void		setInviteMode(bool);
		std::vector<Client *>	getClientsConnected(void) const;
		void	addClientToChannel(Client *, SockInfo &serv);
		bool	clientIsInChannel(const Client *) const;
		void	removeClientFromChannel(const Client *);
		bool	clientIsOperator(const Client *) const;
		void	addOperator(Client *);
		void	broadcastChannel(Client *, Response &, bool) const;
};
