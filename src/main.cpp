/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:13:10 by palucena          #+#    #+#             */
/*   Updated: 2024/04/01 16:50:27 by palucena         ###   ########.fr       */
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

void	signalOverride(int receivedsig)
{
	if (receivedsig == SIGINT)
	{
		std::cout << "server closed" << std::endl;
		exit (0);
	}	
}

int	main(int ac, char **av)
{
	if (ac != 3)
		printError(ERR_ARGNO);
	if (atoi(av[1]) == 0)
		printError(ERR_PORTARG);
	if (strcmp(av[2], "") == 0)
		printError(ERR_EMPTYPWD);
	SockInfo	sock(av);
	signal(SIGINT, signalOverride);
	sock.createSocket();
	std::cout << "[INFO] socket created" << std::endl;
	sock.runServ();
	return 0;
}
