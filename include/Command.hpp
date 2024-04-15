/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/04/15 20:28:44 by palucena         ###   ########.fr       */
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
			static void	execPass(Request &, SockInfo &); // ✓
			static void	execNick(Request &, SockInfo &); // ✓
			static void	execUser(Request &, SockInfo &); // ✓
			static void	execJoin(Request &, SockInfo &); // ✓
			static void	execPrivmsg(Request &, SockInfo &); // Enr
			static void	execMode(Request &, SockInfo &); // ✓
			static void	execPart(Request &, SockInfo &); // Enr
			static void	execInvite(Request &, SockInfo &); // ✓
			static void	execTopic(Request &, SockInfo &); // Enr
			static void	execPing(Request &, SockInfo &); // ✓

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
