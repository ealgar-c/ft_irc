/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SockInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:34:39 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/05/08 12:33:32 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

SockInfo::SockInfo(char **av): _hostname(HOST)
{
	std::string	passwd_str(av[2]);
	this->_port = atoi(av[1]);
	this->_passwd = av[2];
}

SockInfo::~SockInfo()
{
	for (std::vector<Client *>::const_iterator v_it= this->_clients.begin(); v_it != this->_clients.end(); v_it++){
		delete *v_it;
	}
	for (std::vector<Channel *>::const_iterator v_it= this->_channels.begin(); v_it != this->_channels.end(); v_it++){
		delete *v_it;
	}
}

std::string	SockInfo::getHostname(void) const
{
	return (this->_hostname);
}

void	SockInfo::createSocket(void)
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
	this->setBot();
}

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

void	SockInfo::joinChannel(std::string newChannelName, std::string key, Client *clt)
{
	std::cout << "name of the channel to join: " << newChannelName << std::endl;
	for (std::vector<Channel *>::const_iterator v_it = this->_channels.begin(); v_it != this->_channels.end(); v_it++)
	{
		if ((*v_it)->getName() == newChannelName)
		{
			if ((*v_it)->getThereIsPasswd() && (key.empty() || key != (*v_it)->getPassword())){
				Response	reply(this->getHostname(), clt->getNickname(), ERR_BADCHANNELKEY, "", "");
				reply.reply(clt, newChannelName + " :Cannot join channel (+k)");
			}
			else if ((*v_it)->getUserLimit() >= 0 && (*v_it)->getClientsConnected().size() ==  static_cast<size_t>((*v_it)->getUserLimit()))
			{
				std::cout << "Entra\n";
				Response	reply(this->getHostname(), clt->getNickname(), ERR_CHANNELISFULL, "", "");
				reply.reply(clt, newChannelName + " :Cannot join channel (+l)");
			}
			else
				(*v_it)->addClientToChannel(clt, *this);
			return ;
		}
	}
	Channel *newChannel = new Channel(newChannelName, "");
	newChannel->addOperator(clt);
	this->_channels.push_back(newChannel);
	newChannel->addClientToChannel(clt, *this);
}

void	SockInfo::readRequestFromClient(Client *clt)
{
	int 	readfd = 0;
	char	buf[1024];

	memset(buf, 0, 1024);
	while (1)
	{
		readfd = recv(clt->getClientFd(), buf, 1024, 0);
		if (!readfd || clt->getStatus() == DISCONNECTED)
		{
			clt->changeStatus(DISCONNECTED);
			return ;
		}
		else if (readfd == -1)
			return ;
		clt->_messagebuffer.append(buf);
		if(clt->_messagebuffer.find("\n") != std::string::npos)
		{
			if (clt->_messagebuffer.find("WHO") == std::string::npos)
				std::cout << "[DEBUG] message read from client " << clt->getClientFd() << ": " << std::endl << clt->_messagebuffer << std::endl;
			std::stringstream	ss(clt->_messagebuffer);
			std::string			cmd;
			while (std::getline(ss, cmd, '\n'))
			{
				if (cmd[cmd.size() - 1] == 13) // nc
				{
					Request	rqt(cmd.substr(0, cmd.length() - 1), clt);
					rqt.reply(*this);
				}
				else
				{
					Request	rqt(cmd, clt);
					rqt.reply(*this);
				}
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
	for (std::vector<Channel *>::const_iterator v_it = this->_channels.begin(); v_it != this->_channels.end(); v_it++)
	{
		if ((*v_it)->clientIsInChannel(clt))
		{
			(*v_it)->removeClientFromChannel(clt);
			(*v_it)->broadcastNamelist(NULL, *this);
		}
	}
	this->_clients.erase(this->_clients.begin() + i);
	close(clt->getClientFd());
	delete clt;
	std::cout << "[-] Client disconnected" << std::endl;
}

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

bool	SockInfo::authenticate(const std::string toCheck)
{
	if (toCheck == this->_passwd)
		return (true);
	return (false);
}

bool	SockInfo::searchNick(const std::string str)
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i]->getNickname() == str)
			return (true);
	}
	return (false);
}

Client	*SockInfo::getClientByNick(std::string clientNick) const
{
	for(std::vector<Client *>::const_iterator v_it = this->_clients.begin(); v_it != this->_clients.end(); v_it++)
	{
		if ((*v_it)->getNickname() == clientNick)
			return (*v_it);
	}
	return (NULL);
}

Channel	*SockInfo::getChannelByName(std::string ChannelName) const
{
	for(std::vector<Channel *>::const_iterator v_it = this->_channels.begin(); v_it != this->_channels.end(); v_it++)
	{
		if ((*v_it)->getName() == ChannelName)
			return (*v_it);
	}
	return (NULL);
}

void	SockInfo::setBot(void)
{
	Client *newClient = new Client(CONNECTED, "", 1);
	newClient->setNickname("Kaladin");
	this->_clients.push_back(newClient);
	joinChannel("#bot", "", newClient);
	Channel *botch = this->getChannelByName("#bot");
	botch->setTopic(" :Vida antes que muerte, fuerza antes que debilidad, viaje antes que destino");
	botch->setOpenTopic(false);
	
}