/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** users fct ptr
*/

#include "server.h"

void	ptr_users(int client_fd, data_serv_t *serv, UNUSED char *cmd,
cli_t *client)
{
	char	start[512];
	char	end[512];

	sprintf(start, ":localhost 392 %s :UserID   Terminal  Host\r\n",
	client->nickname);
	sprintf(end, ":localhost 394 %s :End of users\r\n", client->nickname);
	send(client_fd, start, le(start), 0);
	print_list_client(client_fd, serv, serv->list, 393);
	send(client_fd, end, le(end), 0);
}