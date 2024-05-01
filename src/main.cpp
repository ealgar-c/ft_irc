/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:13:10 by palucena          #+#    #+#             */
/*   Updated: 2024/05/01 21:52:25 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	printError(std::string err)
{
	std::cerr << "Error:\n\t" << err << std::endl;
	if (errno != 0)
		std::cout << " errno: " << errno << ", " << strerror(errno) << std::endl;
	exit(1);
}

void	signalOverride(int receivedsig)
{
	if (receivedsig == SIGINT)
	{
		std::cout << "server closed" << std::endl;
		exit(0);
	}
}

void	leakschecker(void)
{
	system("leaks -q ircserv");
}

int	main(int ac, char **av)
{
	atexit(leakschecker);
	if (ac != 3)
		printError(ERR_ARGNO);
	if (atoi(av[1]) == 0)
		printError(ERR_PORTARG);
	if (strcmp(av[2], "") == 0)
		printError(ERR_EMPTYPWD);
	SockInfo sock(av);
	signal(SIGINT, signalOverride);
	std::srand(std::time(NULL));
	sock.createSocket();
	std::cout << "[INFO] socket created" << std::endl;
	sock.runServ();
	return 0;
}
