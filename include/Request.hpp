/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:38:51 by palucena          #+#    #+#             */
/*   Updated: 2024/04/01 16:43:32 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class Request {
	private:
	public:
		// Constructors
			Request();
			Request(const Request &);

		// Destructor
			~Request();

		// Operator overload
			Request	&operator=(const Request &);
};
