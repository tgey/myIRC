/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** utils
*/

#include <stdbool.h>

bool	is_special(char c)
{
	char	*special = "-[]\\`^{}";

	for (int i = 0; special[i]; i++) {
		if (special[i] == c)
			return (true);
	}
	return (false);
}

bool	is_letter(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

bool	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}