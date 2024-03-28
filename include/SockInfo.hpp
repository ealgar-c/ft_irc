/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:42 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/03/28 18:49:30 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class	SockInfo
{
	private:
		int			_sockfd;
		std::string	_passwd;
		int			_port;
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
};