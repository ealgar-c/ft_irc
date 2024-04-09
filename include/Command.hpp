/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/09 11:59:33 by palucena         ###   ########.fr       */
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
			static void	execPass(Request &rqt, SockInfo &sockInfo); // ✓
			static void	execNick(Request &rqt, SockInfo &sockInfo); // ✓
			static void	execUser(Request &rqt, SockInfo &sockInfo); // ✓
			static void	execJoin(Request &rqt, SockInfo &sockInfo); // ✓
			static void	execPrivmsg(Request &rqt, SockInfo &sockInfo); // Enr
			static void	execMode(Request &rqt, SockInfo &sockInfo); // Pab
			static void	execPart(Request &rqt, SockInfo &sockInfo);
			static void	execInvite(Request &rqt, SockInfo &sockInfo);
			static void	execPing(Request &rqt, SockInfo &sockInfo); // ✓
			// TODO: Una función para ejecutar cada comando
};
