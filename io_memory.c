/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:21:36 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/25 17:54:44 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	ft_write(int fd, const char *str, size_t len)
{
	static char		buffer[WRITE_SIZE];
	static size_t	buffer_index = 0;

	if (len == 0)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
		return ;
	}
	if (buffer_index + len >= WRITE_SIZE)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
	}
	ft_memcpy(buffer + buffer_index, str, len);
	buffer_index += len;
}

void	free_hashmap(t_HashMap *hashmap)
{
	int i;
	t_HashNode	*tmp;
	t_HashNode	*to_free;

	if (!hashmap)
		return ;
	i = 0;
	while (i < SIZE)
	{
		tmp = hashmap->table[i];
		while (tmp)
		{
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->key);
			free(to_free->value);
			free(to_free);
		}
		i++;
	}
	free(hashmap->table);
}

void	free_hashlist(t_longlong *hashlist)
{
	t_longlong	*tmp;

	while (hashlist)
	{
		tmp = hashlist;
		hashlist = hashlist->next;
		free(tmp);
	}
}

void	init_hash_lookup(void)
{
	int	i;

	i = 'a';
	while (i <= 'z')
	{
		g_char_values[i] = i - 'a' + 1;
		i++;
	}
	i = 'A';
	while (i <= 'Z')
	{
		g_char_values[i] = i - 'A' + 27;
		i++;
	}
	i = '0';
	while (i <= '9')
	{
		g_char_values[i] = i - '0' + 53;
		i++;
	}
	g_char_values['_'] = 63;
	g_char_values[' '] = 64;
}
