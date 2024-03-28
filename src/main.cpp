/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:13:10 by palucena          #+#    #+#             */
/*   Updated: 2024/03/28 16:32:39 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	printError(std::string err)
{
	std::cerr << "Error:\n\t" << err << std::endl;
	if (errno != 0)
		std::cout << " errno: " << errno << ", "<< strerror(errno) << std::endl;
	exit(1);
}

int	main(int ac, char **av) // pablo te puedo pasar muchas cosas pero ponme los corchetes bien
{
	if (ac != 3)
		printError(ERR_ARGNO);
	if (atoi(av[1]) == 0)
		printError(ERR_PORTARG);
	if (strcmp(av[2], "") == 0)
		printError(ERR_EMPTYPWD);
	SockInfo	sock(av);
	sock.createSocket();
	std::cout << "socket created" << std::endl;
	return 0;
}
