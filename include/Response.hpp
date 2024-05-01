/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:11:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/01 21:57:04 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Request;
class Client;

enum RESP_CODE;
enum RESP_TYPE;

class Response
{
	private:
		std::string	_from;
		std::string	_to;
		std::string	_cmd;
		std::string _msg;
		std::string	_endmsg;
		std::string	_finalResponse;
		RESP_TYPE	_rtype;
	public:
		Response(std::string from, std::string to, std::string cmd, std::string msg);
		Response(std::string from, std::string to, RESP_CODE rcode, std::string cmd, std::string msg);
		Response(const Response &);
		~Response();
		Response &operator=(const Response &);
		void	setFrom(std::string);
		void	setTo(std::string);
		void	setCmd(std::string);
		void	setMsg(std::string);
		void	reply(Client *clt);
		void	reply(Client *, std::string);
};