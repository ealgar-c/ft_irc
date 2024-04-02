/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:02:12 by palucena          #+#    #+#             */
/*   Updated: 2024/04/02 13:58:30 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Request::Request()
{ }

Request::Request(const Request &toCopy)
{
	(void)toCopy;
}

Request::Request(const std::string &cmd)
{
	
}

Request	&Request::operator=(const Request &toCopy)
{
	(void)toCopy;
	return (*this);
}

Request::~Request()
{ }
