/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** user fct ptr
*/

#include "server.h"

void	free_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

bool	error_user(int client_fd, char *cmd, cli_t *client)
{
	char	str[512];
	char	**tab;
	bool	ret = false;

	tab = my_str_to_wordtab(cmd, ' ');
	if (!ret && tab_len(tab) < 5) {
		sprintf(str, ":localhost 461 %s %s :Not enough parameters\r\n",
		client->nickname, tab[0]);
		send(client_fd, str, strlen(str), 0);
		ret = true;
	}
	if (!ret && client->user) {
		sprintf(str, ":localhost 462 :You may not reregister\r\n");
		send(client_fd, str, strlen(str), 0);
		ret = true;
	}
	free_tab(tab);
	return (ret);
}

void	ptr_user(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = le(cmd) - 1;
	char	**tab;

	if (error_user(client_fd, cmd, client))
		return;
	while (i >= 0 && cmd[i] != ':')
		i -= 1;
	tab = my_str_to_wordtab(cmd, ' ');
	client->username = strdup(tab[1]);
	client->realname = (i != -1) ? strdup(&cmd[i + 1]) : NULL;
	if (!client->realname)
		client->realname = strdup(tab[tab_len(tab) - 1]);
	if (client->nick && !client->user)
		registration_ending(client_fd, serv, client);
	client->user = true;
	free_tab(tab);
}