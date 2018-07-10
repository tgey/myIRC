##
## EPITECH PROJECT, 2018
## myirc
## File description:
## makefile
##

NAMESRV	=	server

NAMECLI	=	client

SRCSRV	=	server_src/src/main.c			\
		server_src/src/init.c			\
		server_src/src/epoll_handling.c		\
		server_src/src/command_launcher.c	\
		server_src/src/chained_client.c		\
		server_src/src/chained_channel.c	\
		server_src/src/channel_tell.c		\
		server_src/src/list_killer.c		\
		server_src/src/chained_list.c		\
		server_src/src/quit.c			\
		server_src/src/msg.c			\
		server_src/src/list_part.c		\
		server_src/src/client.c			\
		server_src/src/ptr_connect.c		\
		server_src/src/ptr_nick.c		\
		server_src/src/ptr_user.c		\
		server_src/src/ptr_users.c		\
		server_src/src/ptr_list.c		\
		server_src/src/ptr_quit.c		\
		server_src/src/ptr_join.c		\
		server_src/src/ptr_names.c		\
		server_src/src/ptr_part.c		\
		server_src/src/ptr_privmsg.c		\
		server_src/src/ptr_not_registered.c	\
		utils/get_next_line.c			\
		utils/finder.c				\
		utils/char_type.c			\
		client_src/src/utils.c			\
		client_src/src/my_str_to_wordtab.c

SRCCLI	=	client_src/src/main.c		\
		client_src/src/cmd.c		\
		client_src/src/sig.c	\
		client_src/src/init.c		\
		client_src/src/utils.c		\
		client_src/src/command_launcher.c	\
		utils/get_next_line.c		\
		utils/finder.c		\
		client_src/src/my_str_to_wordtab.c	\
		client_src/src/fct_server.c	\
		client_src/src/fct_join.c	\
		client_src/src/fct_list.c	\
		client_src/src/fct_msg.c	\
		client_src/src/fct_names.c	\
		client_src/src/fct_nick.c	\
		client_src/src/fct_part.c	\
		client_src/src/fct_quit.c	\
		client_src/src/fct_user.c	\
		client_src/src/fct_users.c	\
		client_src/src/str_cmd.c

OBJSRV	=	$(SRCSRV:.c=.o)

OBJCLI	=	$(SRCCLI:.c=.o)

CFLAGS	=	-W -Wextra -Wall -I./server_src/inc -I./client_src/inc -g3

all:	$(NAMESRV) $(NAMECLI)

$(NAMESRV): $(OBJSRV)
	gcc -o $(NAMESRV) $(OBJSRV)

$(NAMECLI): $(OBJCLI)
	gcc -o $(NAMECLI) $(OBJCLI)

clean:
	rm -f $(OBJSRV)
	rm -f $(OBJCLI)

fclean:	clean
	rm -f $(NAMESRV)
	rm -f $(NAMECLI)

re:	fclean all

.PHONY:	all clean fclean re
