/*
** EPITECH PROJECT, 2018
** IRC
** File description:
** PSU_myIRC_2017
*/

#include "client.h"

void	init_epoll(client_t *client)
{
	struct epoll_event	events;

	client->epoll_fd = epoll_create(2);
	memset(&events, 0, sizeof(struct epoll_event));
	events.events = POLLIN;
	events.data.fd = 0;
	if (epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, 0, &events) != 0) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(client->epoll_fd);
		return ;
	}
}

void	init_new_client(client_t *client)
{
	client->nickname = NULL;
	client->connected = 0;
	client->channel.name = NULL;
	client->client_fd = -1;
	client->serv_ip = NULL;
	client->nick = false;
	client->user = false;
	init_cmds(client);
}