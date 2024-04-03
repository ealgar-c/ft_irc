/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:13:59 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/03 11:22:52 by ealgar-c         ###   ########.fr       */
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
		std::string			 _name;
		std::vector<Client *> _clientsconnected;
	public:
		Channel();
		Channel(std::string);
		Channel(const Channel &);
		~Channel();
		Channel &operator=(const Channel &);
		std::string	getName() const;
		void	addClientToChannel(Client *, SockInfo &serv);
		bool	clientIsInChannel(const Client *) const;
		void	removeClientFromChannel(const Client *);
};