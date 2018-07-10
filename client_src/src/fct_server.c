/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** server fct
*/

#include "client.h"

void	set_epoll_on_connect(data_serv_t *serv, client_t *cli)
{
	struct epoll_event	event;

	memset(&event, 0, sizeof(struct epoll_event));
	event.events = POLLIN;
	event.data.fd = serv->server_fd;
	if (epoll_ctl(cli->epoll_fd, EPOLL_CTL_ADD,
	serv->server_fd, &event) != 0) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(cli->epoll_fd);
		return;
	}
}

void	try_connect(char *port, const char *ip, data_serv_t *serv,
client_t *cli)
{
	struct	addrinfo	c_in = {0};
	struct	addrinfo	*fill;

	c_in.ai_family = AF_UNSPEC;
	c_in.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(ip, port ? port : "6667", &c_in, &fill))
		return;
	serv->server_fd = socket(fill->ai_family, fill->ai_socktype,
	fill->ai_protocol);
	if (serv->server_fd != -1 &&
	connect(serv->server_fd, fill->ai_addr, fill->ai_addrlen) != -1)
		cli->connected = 1;
	else {
		printf("error connect\n");
		close(serv->server_fd);
		freeaddrinfo(fill);
		return;
	}
	freeaddrinfo(fill);
	set_epoll_on_connect(serv, cli);
}

void	fct_server(client_t *client, data_serv_t *serv, char *cmd)
{
	int	i = 7;
	char	**tab;

	while (cmd[i] == ' ')
		i += 1;
	tab = my_str_to_wordtab(&cmd[i], ':');
	if (!tab || tab_len(tab) < 1 || tab_len(tab) > 2) {
		printf("Syntax : /server $host[:$port]\r\n");
		return;
	}
	if (client->connected == 1) {
		printf("You are already connected to a server\n");
		return;
	}
	if (tab_len(tab) == 2)
		try_connect(tab[1], tab[0], serv, client);
	else
		try_connect(NULL, tab[0], serv, client);
}
