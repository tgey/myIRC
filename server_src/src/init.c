/*
** EPITECH PROJECT, 2018
** init
** File description:
** PSU_myIRC
*/

#include "server.h"

int	get_listen_client(data_serv_t *serv)
{
	if (listen(serv->server_fd, 42) == -1) {
		printf("listen NOK\n");
		close(serv->server_fd);
		return (-1);
	}
	return (0);
}

int	get_server(data_serv_t *serv, int proto)
{
	serv->server_fd = socket(AF_INET, SOCK_STREAM, proto);
	if (serv->server_fd == -1)
		return (-1);
	if (bind(serv->server_fd, (const struct sockaddr *)&serv->s_in_server,
	sizeof(serv->s_in_server)) == -1) {
		printf("bind NOK\n");
		close(serv->server_fd);
		return (-1);
	}
	return (0);
}

int	init_server_socket(int port, data_serv_t *serv)
{
	struct protoent 	*pe;

	memset(&serv->s_in_server, 0, sizeof(struct sockaddr_in));
	serv->s_in_server.sin_family = AF_INET;
	serv->s_in_server.sin_port = htons(port);
	serv->s_in_server.sin_addr.s_addr = INADDR_ANY;
	pe = getprotobyname("TCP");
	if (!pe)
		return (-1);
	if (get_server(serv, pe->p_proto) == -1 ||
		get_listen_client(serv) == -1)
		return (-1);
	return (0);
}

void	init_server_cmd(data_serv_t *serv)
{
	init_sig();
	serv->cmd = NULL;
}

void	init_serv_struct(data_serv_t *serv)
{
	init_server_cmd(serv);
	serv->list = init_chained_list(&delete_client_fd,
	&destroy_client_list);
	serv->channels = init_chained_list(&delete_channel_ptr,
	&destroy_channel_list);
}