/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** connect fct ptr
*/

#include "server.h"

void	ptr_connect(int client_fd, data_serv_t *serv, UNUSED char *cmd,
cli_t *client)
{
	char	fd[12];
	cli_t	*new_cli = empty_client();

	if (!client) {
		new_cli->fd = client_fd;
		sprintf(fd, "%d", client_fd);
		new_cli->nickname = my_strcat("nick", fd);
		insert_chained_list(serv->list, new_cli);
		serv->to_send[0] = 0;
	} else {
		free(new_cli);
	}
}