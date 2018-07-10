/*
** EPITECH PROJECT, 2018
** main server
** File description:
** PSU_myFTP_2017
*/

#include "server.h"

int check_args(int ac, char **av)
{
	unsigned int i = 0;

	if (ac != 2) {
		printf("USAGE: ./server port\n");
		return (-1);
	} else if (strcmp(av[1], "-help") == 0) {
		printf("USAGE: ./server port\n");
		exit (0);
	}
	while (i < strlen(av[1])) {
		if (!isdigit(av[1][i])) {
			printf("USAGE: ./server port\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	remove_client(data_serv_t *serv, int client_fd)
{
	int	i = 0;
	bool	rem = false;

	if (errno != EWOULDBLOCK) {
		while (i < 32 && !rem) {
			rem = removing_client(serv, client_fd, i);
			i++;
		}
	}
	return (0);
}

int	loop_client(data_serv_t *serv, int fdi, int client_fd)
{
	char *buf = NULL;

	buf = get_next_line(serv->events[fdi].data.fd);
	if (!buf)
		remove_client(serv, client_fd);
	else {
		buf = clear_crlf(buf);
		get_command(client_fd, serv, buf);
		free(buf);
	}
	return (0);
}

int	main(int ac, char **av)
{
	data_serv_t *serv;
	int port = 0;

	if (check_args(ac, av) == -1)
		return (84);
	serv = malloc(sizeof(data_serv_t));
	port = atoi(av[1]);
	init_serv_struct(serv);
	init_server_socket(port, serv);
	manage_epoll(serv);
	close(serv->server_fd);
	free(serv);
	return (0);
}
