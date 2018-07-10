/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** cmd with str
*/

#include "client.h"

void	init_cmds(client_t *client)
{
	static client_cmd_t	cmd[] = {
		{"/server", &fct_server},
		{"/nick", &fct_nick},
		{"/list", &fct_list},
		{"/join", &fct_join},
		{"/part", &fct_part},
		{"/users", &fct_users},
		{"/msg", &fct_msg},
		{"/names", &fct_names},
		{"/user", &fct_user},
		{"/quit", &fct_quit},
		{NULL, NULL}};
	client->cmds = cmd;
}