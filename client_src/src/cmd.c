/*
** EPITECH PROJECT, 2018
** commands file
** File description:
** PSU_myIRC_2017
*/

#include "client.h"

int	check_if_connected(client_t *cli)
{
	if (cli->connected != 1)
	{
		printf("You aren't connected to any server !\n");
		printf("Please enter the following command :\n");
		printf("/server $host[:$port]\n");
		return (-1);
	}
	return (0);
}
