/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:12:32 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 11:12:16 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	case_key(char *line, t_longlong **hashlist, char **key, long long *hash)
{
	*key = ft_strdup(line);
	if (!*key)
	{
		printf("error: memory allocation failed!\n");
		return (0);
	}
	*hash = hashing(line);
	if (*hash < 0)
	{
		printf("error: key not valid!\n");
		return (0);
	}
	if (!append_hashlist(hashlist, *hash))
	{
		printf("error: memory allocation failed!\n");
		return (0);
	}
	return (1);
}

int	reading(char *buff, int len, int offset)
{
	int	bytes;

	bytes = read(STDIN_FILENO, buff + offset, len - offset);
	if (bytes < 0)
	{
		printf("error: reading from stdin\n");
		return (-1);
	}
	if (bytes == 0)
		return (0);
	bytes += offset;
	buff[bytes] = '\0';
	return (bytes);
}

int	init_len(char *line, char *buff, int buff_i, char *c)
{
	int len;

	len = c - (buff + buff_i);
	if (len == 0)
	{
		// i = 2;
		buff_i++;
		// continue ;
		return (0);
	}
	ft_memcpy(line, buff + buff_i, len);
	line[len] = '\0';
	return (len);
}

int	handle_cases(t_cases input_case)
{
	if (*(input_case.i) == 0)
	{
		if (!case_key(input_case.line, input_case.hashlist,
				input_case.key, &input_case.hash))
			return (-1);
		*(input_case.i) = 1;
	}
	else if (*(input_case.i) == 1)
	{
		if (!append_hashmap(&(input_case.hashmap->table[input_case.hash]),
				*(input_case.key), ft_strdup(input_case.line)))
			return (printf("error: memory allocation failed!\n"), -1);
		*(input_case.i) = 0;
	}
	else
	{
		input_case.hash = hashing(input_case.line);
		if (input_case.hash < 0)
			return (printf("error: key not valid!\n"), 1);
		if (input_case.hashmap->table[input_case.hash])
			print_value(input_case.hashmap->table[input_case.hash],
				input_case.line);
		else
			printf("%s: not found\n", input_case.line);
	}
	return (1);
}

int	parsing(t_HashMap *hashmap, t_longlong **hashlist)
{
	char		buff[BUFFER_SIZE + 1];
	char		line[BUFFER_SIZE + 1];
	long long	hash;
	int			bytes;
	int			buff_i;
	char		*key;
	int			i;
	int			len;
	char		*c;
	int			offset;

	i = 0;
	bytes = 1;
	offset = 0;
	hash = 0;
	while (bytes > 0)
	{
		bytes = reading(buff, BUFFER_SIZE, offset);
		if (bytes < 0)
			return (0);
		if (bytes == 0)
			return (1);
		buff_i = 0;
		while (buff_i < bytes)
		{
			c = ft_strchr(buff + buff_i, '\n');
			if (c)
			{
				len = init_len(line, buff, buff_i, c);
				if (len == 0)
				{
					buff_i++;
					continue;
				}
				if (handle_cases((t_cases){&i, line, hashlist, hashmap,
					&key, hash}) < 0)
					return (-1);
				buff_i += len + 1;
			}
			else
			{
				ft_memcpy(buff, buff + buff_i, bytes - buff_i);
				offset = bytes - buff_i;
				buff_i = bytes;
			}
		}
	}
	return (1);
}
