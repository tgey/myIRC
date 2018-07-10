/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** find char * in char *
*/

#include <stdbool.h>
#include <string.h>

bool	is_in(char *str, char *sub)
{
	int	i = 0;

	while (i + strlen(sub) <= strlen(str)) {
		if (!strncmp(&str[i], sub, strlen(sub)))
			return (true);
		i += 1;
	}
	return (false);
}
