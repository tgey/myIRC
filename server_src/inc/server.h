/*
** EPITECH PROJECT, 2018
** server.h
** File description:
** myFTP
*/

#ifndef SERVER_H_
#define SERVER_H_

#ifndef	UNUSED
#define UNUSED	__attribute__((unused))
#endif

#ifndef CNI
#define CNI	(client->nickname)
#endif

#ifndef CUS
#define CUS	(client->username)
#endif

#ifndef CHO
#define CHO	(client->hostname)
#endif

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
#include <dirent.h>
#include <signal.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <errno.h>

typedef struct	client_s	client_t;
typedef struct	data_serv_s	data_serv_t;
typedef struct	channel_s	channel_t;
typedef struct	cmd_s		cmd_t;
typedef struct	client_cmd_s	client_cmd_t;

typedef struct	cli_s		cli_t;
typedef struct	chan_s		chan_t;
typedef struct	chained_s	chained_t;
typedef struct	chained_list_s	chained_list_t;
typedef struct	cmd_ptr_s	cmd_ptr_t;

struct	cmd_ptr_s
{
	char	*name;
	void	(*func)(int, struct data_serv_s *, char *, cli_t *);
};

struct	chained_s
{
	void		*data;
	bool		last;
	chained_t	*next;
};

struct	chained_list_s
{
	chained_t	*first;
	void	(*del)(void *list, void *);
	void	(*destroy)(void *list);
};

struct	cli_s
{
	char	*username;
	char	*nickname;
	char	*realname;
	char	*hostname;
	char	*servername;
	int	fd;
	bool	last;
	char	*channel;
	chained_list_t	*channels;
	bool	user;
	bool	nick;
};

struct	chan_s
{
	char		*name;
	chained_list_t	*clients;
};

struct	cmd_s
{
	char	*name;
	int	(*func)(struct client_s *, struct data_serv_s *, char **);
};

struct	client_cmd_s
{
	char	*name;
	void	(*func)(struct client_s *, struct data_serv_s *, char *);
};

typedef struct	serv_cmd_s
{
	char	*name;
	int	(*func)(int client_fd, struct data_serv_s *,  char **);
}		serv_cmd_t;

struct	channel_s
{
	char			*name;
	struct	client_s	*list_users;
	int			channel_id;
	char			**historic;
};

struct	client_s
{
	int			epoll_fd;
	struct epoll_event	events[2];
	int			connected;
	char			*nickname;
	char			*serv_ip;
	int			client_fd;
	char			to_send[4096];
	client_cmd_t		*cmds;
	channel_t		channel;
	bool	user;
	bool	nick;
};


struct	data_serv_s
{
	struct epoll_event	events[32];
	struct sockaddr_in	s_in_server;
	struct sockaddr_in	s_in_client;
	int			server_fd;
	int			client_fd;
	char			to_send[4096];
	serv_cmd_t		*cmd;
	socklen_t		s_in_size;
	chained_list_t		*channels;
	chained_list_t		*list;
};

// main.c
int	check_args(int, char **);
int	manage_client(int, struct sockaddr_in, data_serv_t *);
int	loop_client(data_serv_t *, int, int);
void	init_server_cmd(data_serv_t *serv);
int	remove_client(data_serv_t *serv, int client_fd);
void	get_command(int client_fd, data_serv_t *serv, char *buf);

//init.c
int	get_listen_client(data_serv_t *);
int	get_server(data_serv_t *, int);
int	init_server_socket(int, data_serv_t *);
void	init_serv_struct(data_serv_t *serv);

//get_next_line.c
char	*get_next_line(int);
char	*my_ccat(char *src, char *dest);
char	*my_strcat(char *src, char *dest);
char	**tab_add_line(char **tab, char *str);

//my_str_to_wordtab.c
char	**my_str_to_wordtab(char *s, char c);
char	**put_in(char *s, char **tab, char c, int a);
int	nb_char(char *s, char c);
int	nb_words(char *s, char c);
char	*my_strncpy(char *dest, char *src, int n);

//epoll_handling.c
void	manage_epoll(data_serv_t *);
void	registration_ending(int, data_serv_t *, cli_t *);

//chained_client.c
void	delete_client_fd(void *list, void *fd);
void	print_list_client(int fd, data_serv_t *serv, void *list, int code);
cli_t	*empty_client(void);
cli_t	*get_client_by_fd(void *list, int fd);
cli_t	*get_client_by_nickname(void *list, char *nick);

//chained_channel.c
void	delete_channel_ptr(void *, void *);
void	print_list_channel(int, data_serv_t *, void *list);
chan_t	*empty_channel(char *);
chan_t	*get_channel_by_name(void *list, char *name);

//chained_list.c
int	chained_list_len(chained_list_t *list);
chained_list_t	*init_chained_list(void (*del)(void *, void *),
	void (*destroy)(void *));
void	insert_chained_list(chained_list_t *list, void *data);
void	delete_chained_list(chained_list_t *list, int index);

//list_killer.c
void	kill_client_list(chained_list_t *list);
void	destroy_client_list(void *list);
void	destroy_channel_list(void *list);

//quit.c
void	check_if_last(chained_list_t *users, chained_list_t *chans, char *);
void	delete_client_all(data_serv_t *serv, int fd);
void	send_cmd_quit(int client_fd, data_serv_t *serv, char **tab);
bool	removing_client(data_serv_t *serv, int client_fd, int i);

//utils.c
int	le(char *str);
bool	crlf(char *str);
char	*clear_crlf(char *str);
int	tab_len(char **tab);

//finder.c
bool	is_in(char *str, char *sub);

//msg.c
void	send_to_user(int client_fd, data_serv_t *serv, char *msg,
char *nick);
void	send_in_channel(int client_fd, data_serv_t *serv, char *msg);

//char_type.c
bool	is_letter(char c);
bool	is_number(char c);
bool	is_special(char c);

//list_part.c
void	print_list_elem(int, data_serv_t *, char **, chained_t *);
void	clear_client_part(cli_t *client);
bool	join_checker(data_serv_t *serv, char **args, cli_t *client);

//client.c
void	client_connection(int client_fd, data_serv_t *serv, char *host);
void	init_sig(void);

//channel_tell.c
void	tell_channel(cli_t *, data_serv_t *, char *, char *);
void	tell_once_all_channel(cli_t *, data_serv_t *, char *);
void	tell_channel_others(cli_t *, chan_t *, char *);

//ptr_connect.c
void	ptr_connect(int, data_serv_t *, char *, cli_t *);

//ptr_nick.c
void	ptr_nick(int, data_serv_t *, char *, cli_t *);

//ptr_user.c
void	ptr_user(int, data_serv_t *, char *, cli_t *);
void	free_tab(char **tab);

//ptr_users.c
void	ptr_users(int, data_serv_t *, char *, cli_t *);

//ptr_not_registered.c
void	ptr_not_registered(int, data_serv_t *, char *, cli_t *);

//ptr_list.c
void	ptr_list(int, data_serv_t *, char *, cli_t *);

//ptr_quit.c
void	ptr_quit(int, data_serv_t *, char *, cli_t *);

//ptr_join.c
void	ptr_join(int, data_serv_t *, char *, cli_t *);

//ptr_part.c
void	ptr_part(int, data_serv_t *, char *, cli_t *);

//ptr_names.c
void	ptr_names(int, data_serv_t *, char *, cli_t *);
void	names_chan(int, data_serv_t *, char *, cli_t *);
void	end_of_names(int, data_serv_t *, char *, cli_t *);

//ptr_privmsg.c
void	ptr_privmsg(int, data_serv_t *, char *, cli_t *);

#endif /* !SERVER_H_ */
