/*
** EPITECH PROJECT, 2018
** irc
** File description:
** epoll handler
*/

#include "server.h"

void	registration_ending(int client_fd, UNUSED data_serv_t *serv,
cli_t *client)
{
	char	str[512];

	sprintf(str, ":localhost 001 %s :Welcome to the IRC\r\n"
	":localhost 002 %s :Your host is irc.theo.thomas.eu\r\n"
	":localhost 003 %s :This server was created \r\n",
	client->nickname, client->nickname, client->nickname);
	send(client_fd, str, strlen(str), 0);
}

void	incoming_client(data_serv_t *serv, int epoll_fd)
{
	struct	sockaddr_in	s_in_c;
	socklen_t	s_in_s = sizeof(struct sockaddr_in);
	int	client_fd = accept(serv->server_fd,
	(struct sockaddr *)&s_in_c, &s_in_s);
	struct	epoll_event ev;

	if (client_fd == -1) {
		perror("accept()");
		return;
	}
	memset(&ev, 0, sizeof(struct epoll_event));
	ev.events = EPOLLIN | EPOLLERR;
	ev.data.fd = client_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
		perror("epoll_ctl()");
		return;
	}
	client_connection(client_fd, serv, inet_ntoa(s_in_c.sin_addr));
}

void	epoll_loop(data_serv_t *serv, int event_count, int epoll_fd)
{
	for (int n = 0; n < event_count; n++) {
		if (serv->events[n].data.fd == serv->server_fd)
			incoming_client(serv, epoll_fd);
		else
			loop_client(serv, n, serv->events[n].data.fd);
	}
}

void	epoll_handling(data_serv_t *serv, int epoll_fd)
{
	int	running = true;
	int	event_count;

	while (running) {
		event_count = epoll_wait(epoll_fd, serv->events, 32, 0);
		if (event_count == -1)
			break;
		epoll_loop(serv, event_count, epoll_fd);
	}
}

void	manage_epoll(data_serv_t *serv)
{
	struct epoll_event	event;
	int			epoll_fd = epoll_create(32);

	if (epoll_fd == -1) {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return;
	}
	memset(&event, 0, sizeof(struct epoll_event));
	event.events = EPOLLIN;
	event.data.fd = serv->server_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv->server_fd, &event)) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return;
	}
	epoll_handling(serv, epoll_fd);
	if (close(epoll_fd))
		fprintf(stderr, "Failed to close epoll file descriptor\n");
}
