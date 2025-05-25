/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:18:17 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/25 17:59:20 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	reading(char *buff, int len, int offset)
{
	int	bytes;

	bytes = read(STDIN_FILENO, buff + offset, len - offset);
	if (bytes < 0)
	{
		write(2, "error: reading from stdin\n", 26);
		return (-1);
	}
	if (bytes == 0)
		return (0);
	bytes += offset;
	buff[bytes] = '\0';
	return (bytes);
}

int	init_len(char *line, char *buff, int *buff_i, char *c)
{
	int	len;

	len = c - (buff + *buff_i);
	if (len == 0)
		return (*buff_i += 1, 0);
	ft_memcpy(line, buff + *buff_i, len);
	line[len] = '\0';
	return (len);
}

int	handle_cases(t_cases *data, char *line)
{
	if (*(data->i) == 0)
	{
		if (!case_key(line, data->key, data->hash))
			return (-1);
		*(data->i) = 1;
	}
	else if (*(data->i) == 1)
	{
		if (!append_hashmap(&(data->hashmap->table[*(data->hash)]),
				*(data->key), ft_strdup(line)))
			return (write(2, "error: memory allocation failed!\n", 33), -1);
		*(data->i) = 0;
	}
	else
	{
		*(data->hash) = hashing(line);
		if (*(data->hash) < 0)
			return (line_message(line, ": key not valid\n"), 1);
		if (data->hashmap->table[*(data->hash)])
			print_value(data->hashmap->table[*(data->hash)], line);
		else
			return (line_message(line, ": not found\n"), 1);
	}
	return (1);
}

int	buff_cycle(t_cases *input_case, char *buff, int *buff_i, int bytes)
{
	char	line[BUFFER_SIZE + 1];
	char	*c;
	int		len;

	c = ft_strchr(buff + *buff_i, '\n');
	if (c)
	{
		len = init_len(line, buff, buff_i, c);
		if (len == 0)
		{
			if (*(input_case->i) == 1 && *(input_case->key))
			{
                free(*(input_case->key));
                *(input_case->key) = NULL;
            }
			*(input_case->i) = 2;
			return (0);
		}
		if (handle_cases(input_case, line) < 0)
			return (-1);
		*buff_i += len + 1;
	}
	else
	{
		ft_memcpy(buff, buff + *buff_i, bytes - *buff_i);
		return (2);
	}
	return (1);
}

int	byte_cycle(t_data *data, char *buff, t_HashMap *hashmap)
{
	data->bytes = reading(buff, BUFFER_SIZE, data->offset);
	if (data->bytes < 0)
		return (-1);
	if (data->bytes == 0)
		return (0);
	data->buff_i = 0;
	while (data->buff_i < data->bytes)
	{
		data->ret = buff_cycle(&(t_cases){&data->i, buff + data->buff_i,
				hashmap, &data->key, &data->hash}, buff,
				&data->buff_i, data->bytes);
		if (data->ret < 0)
			return (-1);
		else if (data->ret == 2)
		{
			data->offset = data->bytes - data->buff_i;
			break ;
		}
	}
	return (1);
}
