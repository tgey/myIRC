/*
** EPITECH PROJECT, 2018
** irc
** File description:
** get_next_line
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server.h"

char	**tab_add_line(char **tab, char *str)
{
	char	**new = malloc(sizeof(char *) * (tab_len(tab) + 2));
	int	i = 0;

	while (tab[i]) {
		new[i] = calloc(sizeof(char), le(tab[i]) + 1);
		new[i] = strcat(new[i], tab[i]);
		free(tab[i]);
		i += 1;
	}
	new[i] = calloc(sizeof(char), le(str) + 1);
	new[i] = strcat(new[i], str);
	new[i + 1] = NULL;
	free(tab);
	return (new);
}

char	*my_strcat(char *src, char *dest)
{
	char	*ret = calloc(sizeof(char), strlen(src) + strlen(dest) + 1);
	int	i = 0;
	int	j = 0;

	if (ret == NULL)
		return (NULL);
	while (src[i]) {
		ret[i] = src[i];
		i += 1;
	}
	while (dest[j]) {
		ret[i + j] = dest[j];
		j += 1;
	}
	return (ret);
}

char	*my_ccat(char *src, char *dest)
{
	char	*ret = calloc(sizeof(char), strlen(src) + strlen(dest) + 2);
	int	i = 0;
	int	j = 0;

	if (ret == NULL)
		return (NULL);
	while (src[i]) {
		ret[i] = src[i];
		i += 1;
	}
	while (dest[j]) {
		ret[i + j] = dest[j];
		j += 1;
	}
	free(src);
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*str = calloc(sizeof(char), 1);
	char	buf[2];
	int	len = 1;

	buf[0] = 0;
	buf[1] = 0;
	while (len > 0 && buf[0] != '\n') {
		len = read(fd, buf, 1);
		if (len > 0 && buf[0] != '\n')
			str = my_ccat(str, buf);
	}
	if (strlen(str) == 0 && len == 0) {
		free(str);
		return (NULL);
	}
	return (str);
}
