/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/15 14:25:57 by palucena         ###   ########.fr       */
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
			static void	execPart(Request &rqt, SockInfo &sockInfo); // Enr
			static void	execInvite(Request &rqt, SockInfo &sockInfo); // ✓
			static void	execPing(Request &rqt, SockInfo &sockInfo); // ✓

		// Exception
		class CommandException: public std::exception {
			private:
				std::string	_msg;
			public:
				CommandException(const std::string &str): _msg(str) {}
				virtual const char *what() const throw() {
					return (this->_msg.c_str());
				}
				virtual ~CommandException() throw() {}
		};
};
