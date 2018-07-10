/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** launch commands
*/

#include "server.h"

const cmd_ptr_t ptrs[] = {
	{"CONNECT", &ptr_connect},
	{"NICK", &ptr_nick},
	{"USER", &ptr_user},
	{"USERS", &ptr_users},
	{"LIST", &ptr_list},
	{"QUIT", &ptr_quit},
	{"JOIN", &ptr_join},
	{"NAMES", &ptr_names},
	{"PART", &ptr_part},
	{"PRIVMSG", &ptr_privmsg},
	{NULL, NULL}
};

void	unknown_command(int client_fd, cli_t *client, char *cmd)
{
	char	str[512];

	sprintf(str, ":localhost 421 %s %s :Unknown command\r\n",
	client->nickname, cmd);
	send(client_fd, str, le(str), 0);
}

void	is_unknown(char *buf, int client_fd, char **tab, cli_t *client)
{
	if (le(buf) == 1 && buf[0] == ' ')
		unknown_command(client_fd, client, "");
	if (tab) {
		unknown_command(client_fd, client, tab[0]);
		free_tab(tab);
	}
}

char	**empty_command(char **tab)
{
	if (tab && tab_len(tab) == 0) {
		free_tab(tab);
		tab = NULL;
	}
	return (tab);
}

void	get_command(int client_fd, data_serv_t *serv, char *buf)
{
	char	**tab = my_str_to_wordtab(buf, ' ');
	cli_t	*client = get_client_by_fd(serv->list, client_fd);

	printf("received by server : %s\n", buf);
	tab = empty_command(tab);
	for (int i = 0; ptrs[i].name; i++) {
		if ((!client->nick || !client->user) && tab &&
		strcmp("NICK", tab[0]) && strcmp("USER", tab[0]) &&
		!strcmp(ptrs[i].name, tab[0]) && strcmp("QUIT", tab[0])) {
			ptr_not_registered(client_fd, serv, buf, client);
			free_tab(tab);
			return;
		} else if (tab && !strcmp(ptrs[i].name, tab[0])) {
			ptrs[i].func(client_fd, serv, buf, client);
			free_tab(tab);
			return;
		}
	}
	is_unknown(buf, client_fd, tab, client);
}
