/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:38:51 by palucena          #+#    #+#             */
/*   Updated: 2024/05/01 21:56:36 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class Request {
	private:
		std::string	_cmd;
		std::string	_msg;
		Client		*_client;
	public:
			Request();
			Request(const Request &);
			Request(std::string, Client *);
			~Request();
			Request	&operator=(const Request &);
			std::string	getCmd(void) const;
			std::string	getMsg(void) const;
			Client		*getClient(void) const;
			void		setCmd(const std::string);
			void		setMsg(const std::string);
			void		setClient(Client *);
			void		reply(SockInfo &);
};
