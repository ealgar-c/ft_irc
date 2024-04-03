/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/03 18:55:34 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Command
{
	public:
		// Constructors
			Command();
			Command(const Command &);

		// Destructor
			~Command();

		// Operator overload
			Command	&operator=(const Command &);

		// Member functions
			static void	execPass(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execNick(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execUser(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execConn(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execJoin(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execPrivmsg(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execWho(std::string cmd, Client *clt, SockInfo &sockInfo);
			static void	execPing(std::string cmd, Client *clt, SockInfo &sockInfo);
			// TODO: Una función para ejecutar cada comando
};
