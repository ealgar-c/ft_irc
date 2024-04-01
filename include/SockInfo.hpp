/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:42 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/01 17:11:45 by ealgar-c         ###   ########.fr       */
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
	public:
		//	constructor
			SockInfo(char **);
		//	destructor
			~SockInfo();
		//	overloads
		//	getters
		//	methods
			void	createSocket();
			void    runServ();
			void	createClient();
			void	deleteClient(Client *);
			void	readClientInfo();
			void	readRequestFromClient(Client *);
};