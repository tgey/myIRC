/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct join
*/

#include "client.h"

void	join_ret(char *ret, client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 5;
	bool	good = false;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	if (!is_in(ret, " 461 ") && !is_in(ret, " 403 ") &&
	!is_in(ret, " 451 "))
		good = true;
	if (good) {
		if (cli->channel.name) {
			sprintf(str, "PART %s\r\n", cli->channel.name);
			send(serv->server_fd, str, le(str), 0);
			free(cli->channel.name);
			cli->channel.name = NULL;
		}
		cli->channel.name = strdup(&cmd[i]);
	} else
		printf(is_in(ret, " 451 ") ? "You have to register with /user"
		" AND /nick\n" : "Syntax : /join $channel\n");
}

void	fct_join(client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 5;
	char	str[512];
	char	*ret;

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "JOIN %s\r\n", &cmd[i]);
	while (cmd[i]) {
		if (cmd[i] == ',') {
			printf("You can only join 1 channel at a time\n");
			printf("/join $channel\n");
			return;
		}
		i += 1;
	}
	send(serv->server_fd, str, le(str), 0);
	ret = get_next_line(serv->server_fd);
	printf("%s\n", ret);
	join_ret(ret, cli, serv, cmd);
}
