/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:38:51 by palucena          #+#    #+#             */
/*   Updated: 2024/04/04 15:08:26 by palucena         ###   ########.fr       */
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
		// Constructors
			Request();
			Request(const Request &);
			Request(std::string, Client *);

		// Destructor
			~Request();

		// Operator overload
			Request	&operator=(const Request &);

		// Members
			void		reply(SockInfo &);
			std::string	getCmd(void) const;
			std::string	getMsg(void) const;
			void		setCmd(const std::string);
			void		setMsg(const std::string);
};
