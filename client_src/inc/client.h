/*
** EPITECH PROJECT, 2018
** client.h
** File description:
** myFTP
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

//main.c
int	my_command(client_t *cli, data_serv_t *serv, char *buf);
int	loop_epoll(client_t *client, data_serv_t *serv);

//init.c
void	init_cmd(client_t *client);
int	init_socket(int, const char *, data_serv_t *, client_t *);
void	init_new_client(client_t *client);
int	init_sin_serv(data_serv_t *serv, int port, const char *ip);
void	init_epoll(client_t *client);

//my_str_to_wordtab.c
char	**my_str_to_wordtab(char *s, char c);
char	**put_in(char *s, char **tab, char c, int a);
int	nb_char(char *s, char c);
int	nb_words(char *s, char c);
char	*my_strncpy(char *dest, char *src, int n);

//cmd.c
int	check_if_connected(client_t *cli);
int	connect_to_server(client_t *cli, data_serv_t *serv, char **args);
int	change_nickname(client_t *client, data_serv_t *serv, char **args);
int	send_message(client_t *client, data_serv_t *serv, char **args);
int	list_channels(client_t *client, data_serv_t *serv, char **args);

//cmd_bis.c
int	join_channel(client_t *client, data_serv_t *serv, char **args);
int	names_channel(client_t *client, data_serv_t *serv, char **args);
int	leave_channel(client_t *client, data_serv_t *serv, char **args);
int	display_users(client_t *client, data_serv_t *serv, char **args);
int	my_quit(client_t *client, data_serv_t *serv, char **args);

//cmd_end.c
int	change_user(client_t *client, data_serv_t *serv, char **args);

//utils.c
int	le(char *str);
bool	crlf(char *str);
char	*clear_crlf(char *str);
int	tab_len(char **tab);

//command_launcher.c
void	send_message_channel(client_t *cli, data_serv_t *serv, char *buf);
int	launch_command(client_t *cli, data_serv_t *serv, char *, int i);

//str_cmd.c
void	init_cmds(client_t *);

//fct_server.c
void	fct_server(client_t *, data_serv_t *, char *);

//fct_join.c
void	fct_join(client_t *, data_serv_t *, char *);

//fct_list.c
void	fct_list(client_t *, data_serv_t *, char *);

//fct_msg.c
void	fct_msg(client_t *, data_serv_t *, char *);
void	msg_to_channel(client_t *cli, data_serv_t *serv, char *msg);

//fct_names.c
void	fct_names(client_t *, data_serv_t *, char *);

//fct_nick.c
void	fct_nick(client_t *, data_serv_t *, char *);

//fct_part.c
void	fct_part(client_t *, data_serv_t *, char *);

//fct_quit.c
void	fct_quit(client_t *, data_serv_t *, char *);

//fct_user.c
void	fct_user(client_t *, data_serv_t *, char *);

//fct_users.c
void	fct_users(client_t *, data_serv_t *, char *);

#endif /* !CLIENT_H_ */
