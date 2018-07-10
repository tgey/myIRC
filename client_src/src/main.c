/*
** EPITECH PROJECT, 2018
** main client
** File description:
** PSU_myIRC_2017
*/

#include "client.h"

char	*clear_ending_spaces(char *str)
{
	while (le(str) > 0 && str[le(str) - 1] == ' ')
		str[le(str) - 1] = 0;
	return (str);
}

int	my_command(client_t *cli, data_serv_t *serv, char *buf)
{
	char 	**tab;

	buf = clear_crlf(buf);
	buf = clear_ending_spaces(buf);
	tab = my_str_to_wordtab(buf, ' ');
	if (!tab || tab_len(tab) == 0)
		return (0);
	for (unsigned int i = 0; cli->cmds[i].name; i++) {
		if (strcmp(cli->cmds[i].name, tab[0]) == 0) {
			launch_command(cli, serv, buf, i);
			return (0);
		}
	}
	if (tab[0][0] == '/')
		printf("421 \"%s\": Unknown command\n", tab[0]);
	else if (check_if_connected(cli) == 1)
		return (0);
	else
		msg_to_channel(cli, serv, buf);
	return (0);
}

int	iterate_epoll(client_t *cli, data_serv_t *serv, int n)
{
	char	*line = NULL;

	if (cli->events[n].data.fd == 0) {
		line = get_next_line(0);
		if (line == NULL) {
			free(line);
			return (0);
		}
		if (strlen(line) > 0 && my_command(cli, serv, line) == -1)
			return (-1);
		free(line);
	} else {
		line = get_next_line(cli->events[n].data.fd);
		if (line)
			printf("%s\n", line);
		free(line);
	}
	return (1);
}

int	loop_epoll(client_t *cli, data_serv_t *serv)
{
	char	*line = NULL;
	int	event_count;
	int	ret = 1;

	setbuf(stdout, NULL);
	while (1) {
		event_count = epoll_wait(cli->epoll_fd, cli->events, 2, 0);
		for (int n = 0; n < event_count && ret == 1; n++)
			ret = iterate_epoll(cli, serv, n);
		if (ret != 1)
			return (ret);
	}
	free(line);
	return (0);
}

int	main(void)
{
	client_t		*client;
	data_serv_t		*serv;

	client = malloc(sizeof(client_t));
	serv = malloc(sizeof(data_serv_t));
	init_sig();
	init_epoll(client);
	init_new_client(client);
	printf("Welcome on our IRC, connect to a server\n");
	if (loop_epoll(client, serv) == -1)
		return (-1);
	return (0);
}
