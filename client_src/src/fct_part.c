/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct part
*/

#include "client.h"

void	part_ret(char *ret, client_t *cli, UNUSED data_serv_t *serv,
UNUSED char *cmd)
{
	bool	good = false;

	if (!is_in(ret, " 461 ") && !is_in(ret, " 403 ") &&
	!is_in(ret, " 442 ") && !is_in(ret, " 451 "))
		good = true;
	if (good) {
		free(cli->channel.name);
		cli->channel.name = NULL;
	} else
		printf(is_in(ret, " 451 ") ? "You have to register with /user"
		" AND /nick\n" : "Syntax : /part $channel\n");
}

void	fct_part(client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 5;
	char	str[512];
	char	*ret;

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "PART %s\r\n", &cmd[i]);
	send(serv->server_fd, str, le(str), 0);
	ret = get_next_line(serv->server_fd);
	printf("%s\n", ret);
	part_ret(ret, cli, serv, cmd);
}
