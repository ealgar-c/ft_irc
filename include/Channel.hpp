/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:13:59 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/01 19:22:30 by ealgar-c         ###   ########.fr       */
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
		bool					_thereIsPasswd;
		std::string				_passwd;
		bool					_openTopic;
		std::string				_topic;
		bool					_inviteMode;
		int						_userLimit;
		std::vector<Client *>	_operatorClients;
		std::vector<Client *>	_clientsConnected;
	public:
		Channel();
		Channel(std::string, std::string);
		Channel(const Channel &);
		~Channel();
		Channel &operator=(const Channel &);
		std::string	getName() const;
		bool		getThereIsPasswd() const;
		void		setThereIsPasswd(bool);
		std::string	getPassword() const;
		void		setPassword(std::string);
		bool		getOpenTopic() const;
		void		setOpenTopic(bool);
		std::string	getTopic() const;
		void		setTopic(std::string);
		bool		getInviteMode() const;
		void		setInviteMode(bool);
		int			getUserLimit() const;
		void		setUserLimit(int);
		std::vector<Client *>	getClientsConnected(void) const;
		void	addClientToChannel(Client *, SockInfo &serv);
		bool	clientIsInChannel(const Client *) const;
		void	removeClientFromChannel(const Client *);
		bool	clientIsOperator(const Client *) const;
		void	removeClientAsOperator(const Client *);
		void	addOperator(Client *);
		void	broadcastChannel(Client *, Response &, bool) const;
		void	broadcastNamelist(Client *, SockInfo &) const;
};
