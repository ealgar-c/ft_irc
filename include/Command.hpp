/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/16 09:31:40 by ealgar-c         ###   ########.fr       */
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
			static void	execPass(Request &rqt, SockInfo &serv); // ✓
			static void	execNick(Request &rqt, SockInfo &serv); // ✓
			static void	execUser(Request &rqt, SockInfo &serv); // ✓
			static void	execJoin(Request &rqt, SockInfo &serv); // ✓
			static void	execPrivmsg(Request &rqt, SockInfo &serv); // Enr
			static void	execMode(Request &rqt, SockInfo &serv); // Pab
			static void	execPart(Request &rqt, SockInfo &serv); // Enr
			static void	execInvite(Request &rqt, SockInfo &serv); // ✓
			static void	execPing(Request &rqt, SockInfo &serv); // ✓
			static void	execTopic(Request &rqt, SockInfo &serv); // Enr

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
