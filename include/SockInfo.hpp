/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:42 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/01 14:40:49 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Client;

class	SockInfo
{
	private:
		int							_sockfd;
		std::string					_passwd;
		int							_port;
		std::vector<struct pollfd>	_fds;
		std::vector<Client *>			_clients;
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
			void	readClientInfo();
			void	readRequestFromClient(Client *);
};