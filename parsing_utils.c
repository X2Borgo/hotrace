/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:20:02 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/25 18:37:21 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	case_key(char *line, char **key, long long *hash)
{
	*key = ft_strdup(line);
	if (!*key)
	{
		write(2, "error: memory allocation failed!\n", 33);
		return (0);
	}
	*hash = hashing(line);
	if (*hash < 0)
	{
		write(2, "error: key not valid!\n", 22);
		return (0);
	}
	return (1);
}

void	line_message(char *line, char *message)
{
	write(1, line, ft_strlen(line));
	write(1, message, ft_strlen(message));
}

int	parsing(t_HashMap *hashmap)
{
	char		buff[BUFFER_SIZE + 1];
	t_data		data;
	int			ret;

	data = (t_data){0, 1, 0, 0, 0, 0, NULL};
	while (data.bytes > 0)
	{
		ret = byte_cycle(&data, buff, hashmap);
		if (ret < 0)
		{
			if (data.i == 1 && data.key)
				free(data.key);
			return (0);
		}
	}
	if (data.i == 1 && data.key)
		free(data.key);
	return (1);
}

int	print_value(t_HashNode *node, char *key)
{
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			write(STDOUT_FILENO, node->value, ft_strlen(node->value));
			write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		node = node->next;
	}
	write(1, key, ft_strlen(key));
	write(1, ": not found\n", 12);
	return (0);
}
