/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct msg
*/

#include "client.h"

void	msg_file(UNUSED client_t *cli, UNUSED data_serv_t *serv,
UNUSED char *cmd)
{
	printf("We are not handling this function\n");
}

void	msg_perso(UNUSED client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 4;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "PRIVMSG %s\r\n", &cmd[i]);
	send(serv->server_fd, str, le(str), 0);
}

void	msg_to_channel(client_t *cli, data_serv_t *serv, char *msg)
{
	char	str[512];

	if (!cli->channel.name) {
		printf("You are not on any channel\n");
		printf("Please join one before typing message\n");
		return;
	}
	sprintf(str, "/msg %s :%s", cli->channel.name, msg);
	msg_perso(cli, serv, str);
}

void	fct_msg(client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 4;
	char	**tab;

	while (cmd[i] == ' ')
		i += 1;
	tab = my_str_to_wordtab(&cmd[i], ' ');
	if (!tab || tab_len(tab) < 2) {
		printf("Syntax : /msg $nickname $message\n");
		printf("OR Syntax : /msg $channel $nickname $file\n");
		return;
	}
	if (tab[0][0] == '#')
		msg_file(cli, serv, cmd);
	else
		msg_perso(cli, serv, cmd);
	for (int x = 0; tab[x]; x++)
		free(tab[x]);
	free(tab);
}
