/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:42 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/01 18:43:11 by palucena         ###   ########.fr       */
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
		// Constructor
			SockInfo(char **);
		// Destructor
			~SockInfo();
		// Overloads
		// Getters
		// Methods
			void	createSocket();
			void    runServ();
			void	createClient();
			void	readClientInfo();
			void	readRequestFromClient(Client *);
};
