/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:11:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/01 19:15:16 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ft_irc.hpp"

class Request;

class Response
{
	private:
/* 		std::string	_from;
		std::string	_to;
		std::string	_cmd; */
		//const std::string	_end = "\r\n";
		std::string	_finalResponse;
		void	reply(void) const;
	public:
		Response(std::string from, std::string to, std::string cmd);
		Response(const Response &);
		~Response();
		Response &operator=(const Response &);
		//	void	generateResponse(std::string);
};