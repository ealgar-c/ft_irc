/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:39 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/04/02 13:44:44 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

//	constructor
SockInfo::SockInfo(char **av){
	std::string	passwd_str(av[2]);
	this->_port = atoi(av[1]);
	this->_passwd = passwd_str;
}

//	destructor
SockInfo::~SockInfo()
{
	for (std::vector<Client *>::const_iterator v_it= this->_clients.begin(); v_it != this->_clients.end(); v_it++)
	{
		delete *v_it;
	}
	
}

//	methods

/**
 * @brief Creates the socket
 */
void	SockInfo::createSocket(void) // tenemos un super socket
{
	sockaddr_in	sockAddrConf;
	int	opt = 1;

	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd == -1)
		printError(ERR_SOCKCREAT);
	sockAddrConf.sin_port = htons(this->_port);
	sockAddrConf.sin_addr.s_addr = INADDR_ANY;
	sockAddrConf.sin_family = AF_INET;
	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(this->_sockfd);
		printError(ERR_SETSOCKOPT);
	}
	if (bind(this->_sockfd, (sockaddr *)&sockAddrConf, sizeof(sockAddrConf)) == -1)
	{
		close(this->_sockfd);
		printError(ERR_BINDSOCK);
	}
	if (listen(this->_sockfd, CONST_MAXSCONN) == -1)
	{
		close(this->_sockfd);
		printError(ERR_SOCKLISTEN);
	}
	Channel *general = new Channel("#general");
	this->_channels.push_back(general);
}

/**
 * @brief accepts the connection of new clients
 */
void	SockInfo::createClient()
{
	sockaddr_in	clientAddr;
	socklen_t	socklen = sizeof(clientAddr);
	int newconnection;

	newconnection = accept(this->_sockfd, (sockaddr *)&clientAddr, &socklen);
	if (newconnection == -1)
		printError("");
	fcntl(newconnection, F_SETFL, O_NONBLOCK);
	struct in_addr	clientInetInfo;
	clientInetInfo.s_addr = clientAddr.sin_addr.s_addr;
	Client *newClient = new Client(UNKNOWN, inet_ntoa(clientInetInfo), newconnection);
	this->_clients.push_back(newClient);
	this->_fds.push_back((struct pollfd){newconnection, POLLIN | POLLOUT, 0});
	std::cout << "[+] New client connected with fd " << newconnection << std::endl;
}

void	SockInfo::readClientInfo(void)
{
	std::vector<Client *>::const_iterator v_it = this->_clients.begin();
	while (v_it != this->_clients.end())
		v_it++;
	v_it--;
	std::cout << "[DEBUG] Client info:\n" << "\tstatus -> " << (*v_it)->getStatus() << std::endl << "\tip -> " << (*v_it)->getIp() << std::endl << "\tclient fd -> " << (*v_it)->getClientFd() << std::endl;
	std::cout << "[DEBUG] There are currently " << this->_clients.size() << " clients." << std::endl;
}

void	SockInfo::readRequestFromClient(Client *clt)
{
	int 	readed = 0;
	char	buf[1024];

	memset(buf, 0, 1024);
	while (1)
	{
		readed = recv(clt->getClientFd(), buf, 1024, 0);
		if (!readed)
		{
			std::cout << "[-] Client disconnected" << std::endl;
			clt->changeStatus(DISCONNECTED);
			return ;
		}
		else if (readed < 0)
			printError("");
		clt->_messagebuffer.append(buf);
		if(clt->_messagebuffer.find("\n") != std::string::npos)
		{
			std::cout << "[DEBUG] message readed from client " << clt->getClientFd() << ": " << clt->_messagebuffer << std::endl;
			if (clt->_messagebuffer.find("JOIN") != std::string::npos)
			{
				int i = clt->_messagebuffer.find("JOIN");
				clt->_messagebuffer.erase(0, i);
				std::string test;
				test = ":ealgar-c " + clt->_messagebuffer + "\r\n";
				std::cout << test;
				send(clt->getClientFd(), test.c_str(), test.length(), 0);
			}
			clt->_messagebuffer.clear();
			return ;
		}
	}
}

static Client	*searchClient(std::vector<Client *>clients, int fd)
{
	for(std::vector<Client *>::const_iterator v_it= clients.begin(); v_it != clients.end(); v_it++)
	{
		if ((*v_it)->getClientFd() == fd)
			return (*v_it);
	}
	return (NULL);
}

void	SockInfo::deleteClient(Client *clt)
{
	int i = 0;
	for (std::vector<struct pollfd>::const_iterator v_it = this->_fds.begin();v_it != this->_fds.end(); v_it++)
	{
		if ((*v_it).fd == clt->getClientFd())
			break;
		i++;
	}
	this->_fds.erase(this->_fds.begin() + i);
	i = 0;
	for (std::vector<Client *>::const_iterator v_it = this->_clients.begin();v_it != this->_clients.end(); v_it++)
	{
		if (*v_it == clt)
			break;
		i++;
	}
	this->_clients.erase(this->_clients.begin() + i);
	delete clt;
}

/**
 * @brief it executes a loop that is using poll (in a non-blocking way)
 * 			to read from the socket fd any POLLIN event
 */
void	SockInfo::runServ(void)
{
	this->_fds.push_back((struct pollfd){this->_sockfd, POLLIN, 0});
	while (poll(&this->_fds[0], this->_fds.size(), -1) > 0)
	{
		for (size_t i = 0; i != this->_fds.size(); i++)
		{
			if (this->_fds[i].fd == this->_sockfd && this->_fds[i].revents & POLLIN)
			{
				this->createClient();
				this->readClientInfo();
			}
			else if (this->_fds[i].revents & POLLIN)
				this->readRequestFromClient(searchClient(this->_clients, this->_fds[i].fd));
		}
		for (std::vector<struct pollfd>::const_iterator v_it = this->_fds.begin(); v_it != this->_fds.end(); v_it++)
		{
			if (searchClient(this->_clients, v_it->fd) && searchClient(this->_clients, v_it->fd)->getStatus() == DISCONNECTED)
			{
				this->deleteClient(searchClient(this->_clients, v_it->fd));
				v_it = this->_fds.begin();
			}
		}
	}
}
