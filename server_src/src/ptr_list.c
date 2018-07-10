/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** list fct ptr
*/

#include "server.h"

void	print_list_channels(int client_fd, data_serv_t *serv, char *cmd,
int x)
{
	char	str[512];
	char	**tab = my_str_to_wordtab(&cmd[x], ',');
	chan_t	*channel;

	for (int i = 0; tab[i]; i++) {
		channel = get_channel_by_name(serv->channels, tab[i]);
		if (channel) {
			sprintf(str, ":localhost 322 %s %d :[+nt]\r\n",
			channel->name, chained_list_len(channel->clients));
			send(client_fd, str, le(str), 0);
		}
	}
	free_tab(tab);
}

void	ptr_list(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	char	**tab = my_str_to_wordtab(cmd, ' ');
	char	str[512];
	int	len = tab_len(tab);
	int	i = 4;

	sprintf(str, ":localhost 321 %s Channel :Users  Name\r\n",
	client->nickname);
	send(client_fd, str, le(str), 0);
	while (cmd[i] == ' ')
		i += 1;
	if (len == 1)
		print_list_channel(client_fd, serv, serv->channels);
	else
		print_list_channels(client_fd, serv, cmd, i);
	sprintf(str, ":localhost 323 %s :End of LIST\r\n", client->nickname);
	send(client_fd, str, le(str), 0);
	free_tab(tab);
}