/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:42 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/01 21:57:12 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class	Client;
class	Channel;

class	SockInfo
{
	private:
		int							_sockfd;
		std::string					_passwd;
		int							_port;
		std::vector<struct pollfd>	_fds;
		std::vector<Client *>		_clients;
		std::vector<Channel *>		_channels;
		std::string					_hostname;
	public:
			SockInfo(char **);
			~SockInfo();
		std::string	getHostname(void) const;
			void	createSocket();
			void	runServ();
			void	createClient();
			void	deleteClient(Client *);
			void	readClientInfo();
			void	joinChannel(std::string, std::string, Client *clt);
			void	readRequestFromClient(Client *);
			bool	authenticate(const std::string);
			bool	searchNick(const std::string);
			Client	*getClientByNick(std::string) const;
			Channel	*getChannelByName(std::string) const;
			void	setBot(void);
};
