/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:56:26 by palucena          #+#    #+#             */
/*   Updated: 2024/05/01 21:56:07 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Command
{
	public:
			Command();
			Command(const Command &);
			~Command();
			Command	&operator=(const Command &);
			static void	execPass(Request &, SockInfo &);
			static void	execNick(Request &, SockInfo &);
			static void	execUser(Request &, SockInfo &);
			static void	execJoin(Request &, SockInfo &);
			static void	execPrivmsg(Request &, SockInfo &);
			static void	execMode(Request &, SockInfo &);
			static void	execPart(Request &, SockInfo &);
			static void	execInvite(Request &, SockInfo &);
			static void	execTopic(Request &, SockInfo &);
			static void	execPing(Request &, SockInfo &);
		class CommandException: public std::exception
		{
			private:
				std::string	_msg;
			public:
				CommandException(const std::string &str): _msg(str){}
				virtual const char *what() const throw() {
					return (this->_msg.c_str());
				}
				virtual ~CommandException() throw() {}
		};
};
