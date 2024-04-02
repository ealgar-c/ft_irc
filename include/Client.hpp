/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:04:00 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/02 17:12:13 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

enum C_STATUS;

class Client
{
	private:
		C_STATUS	_status;
		std::string	_nickname;
		std::string	_ip;
		int			_clientfd;
	public:
		Client();
		Client(C_STATUS, std::string, int);
		~Client();
		Client &operator=(const Client &);
		std::string	_messagebuffer;
		C_STATUS	getStatus(void) const;
		std::string	getIp(void) const;
		int			getClientFd(void) const;
		void		changeStatus(C_STATUS);
};