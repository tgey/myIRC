/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** not_registered fct ptr
*/

#include "server.h"

void	ptr_not_registered(int client_fd, UNUSED data_serv_t *serv,
UNUSED char *cmd, UNUSED cli_t *client)
{
	char	str[512];

	sprintf(str, ":localhost 451 :You have not registered\r\n");
	send(client_fd, str, strlen(str), 0);
}