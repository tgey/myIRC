/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** client actions
*/

#include "server.h"

void	client_connection(int client_fd, data_serv_t *serv, char *host)
{
	printf("New client: %d\n", client_fd);
	if (!get_client_by_fd(serv->list, client_fd))
		ptr_connect(client_fd, serv, NULL, NULL);
	get_client_by_fd(serv->list, client_fd)->hostname = host;
}

void	sig_handler(int signal)
{
	switch (signal) {
	case SIGINT:
		printf("Sigint\n");
		break;
	case SIGQUIT:
		printf("Sigquit\n");
		break;
	case SIGTERM:
		printf("Sigterm\n");
		break;
	case SIGSEGV:
		printf("Sigsegv\n");
		break;
	default:
		printf("Other signal killing program");
		break;
	}
	exit(0);
}

void	init_sig(void)
{
	struct sigaction	sig;

	sig.sa_handler = &sig_handler;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
	sigaction(SIGTERM, &sig, 0);
	sigaction(SIGSEGV, &sig, 0);
}