/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/04 15:24:14 by palucena         ###   ########.fr       */
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
			static void	execPass(std::string args, Client *clt, SockInfo &sockInfo); // Falta expulsión
			static void	execNick(std::string args, Client *clt, SockInfo &sockInfo); // ✓
			static void	execUser(std::string args, Client *clt, SockInfo &sockInfo); // ✓
			static void	execJoin(std::string args, Client *clt, SockInfo &sockInfo); // ✓
			static void	execPrivmsg(std::string args, Client *clt, SockInfo &sockInfo); // Enr
			static void	execMode(std::string args, Client *clt, SockInfo &sockInfo); // Pab
			static void	execPart(std::string args, Client *clt, SockInfo &sockInfo);
			static void	execPing(std::string args, Client *clt, SockInfo &sockInfo); // ✓
			// TODO: Una función para ejecutar cada comando
};
