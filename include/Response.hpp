/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:11:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/10 19:11:35 by palucena         ###   ########.fr       */
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
		//	STANDARD RESPONSE CONSTRUCTOR
		Response(std::string from, std::string to, std::string cmd, std::string msg);
		//	SERVER RESPONSE CONSTRUCTOR
		Response(std::string from, std::string to, RESP_CODE rcode, std::string cmd, std::string msg);
		Response(const Response &);
		~Response();
		Response &operator=(const Response &);
		void	setFrom();
		void	setTo();
		void	setCmd();
		void	setMsg();
		void	setRtype();
		void	reply(Client *clt);
		void	reply(Client *clt, Channel &, std::string);
		//	void	generateResponse(std::string);
};