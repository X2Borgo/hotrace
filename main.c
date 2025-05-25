/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 09:55:06 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

long long	hashing(char *key)
{
	long long	hash;
	int			i;
	long long	p_pow;

	i = 0;
	hash = 0;
	p_pow = 1;
	while (key[i] && key[i] != '\n')
	{
		if (key[i] >= 'a' && key[i] <= 'z')
			hash = (hash + (key[i] - 'a' + 1) * p_pow) % M;
		else if (key[i] >= 'A' && key[i] <= 'Z')
			hash = (hash + (key[i] - 'A' + 27) * p_pow) % M;
		else if (key[i] >= '0' && key[i] <= '9')
			hash = (hash + (key[i] - '0' + 53) * p_pow) % M;
		else if (key[i] == '_')
			hash = (hash + 63 * p_pow) % M;
		else if (key[i] == ' ')
			hash = (hash + 64 * p_pow) % M;
		else
			return (-1);
		p_pow = (p_pow * P) % M;
		i++;
	}
	return (hash);
}

// TODO: check if the key already exists
int	append_hashlist(t_longlong **hashlist, long long hash)
{
	t_longlong	*new_node;
	t_longlong	*tmp;

	new_node = (t_longlong *)malloc(sizeof(t_longlong));
	if (!new_node)
		return (0);
	new_node->hash = hash;
	new_node->next = NULL;
	if (!*hashlist)
	{
		*hashlist = new_node;
		return (1);
	}
	tmp = *hashlist;
	while (tmp->next)
	{
		if (tmp->hash == hash)
		{
			free(new_node);
			return (1);
		}
		tmp = tmp->next;
	}
	tmp->next = new_node;
	return (1);
}

void	free_hashmap(char **hashmap, t_longlong *hashlist)
{
	t_longlong	*tmp;

	tmp = hashlist;
	while (tmp)
	{
		free(hashmap[tmp->hash]);
		tmp = tmp->next;
	}
	free(hashmap);
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

int	append_hashmap(t_HashNode **node, char *key, char *value)
{
	t_HashNode	*tmp;
	t_HashNode	*last;
	size_t		key_len;

	if (!key || !value)
		return (0);
	if (*node == NULL)
	{
		*node = (t_HashNode *)malloc(sizeof(t_HashNode));
		if (!*node)
			return (0);
		(*node)->key = key;
		(*node)->value = value;
		(*node)->next = NULL;
	}
	else
	{
		tmp = *node;
		last = tmp;
		key_len = ft_strlen(key);
		while (tmp)
		{
			if (ft_strncmp(tmp->key, key, key_len) == 0)
			{
				free(tmp->value);
				tmp->value = value;
				return (1);
			}
			last = tmp;
			tmp = tmp->next;
		}
		last->next = (t_HashNode *)malloc(sizeof(t_HashNode));
		if (!last->next)
			return (0);
		last = last->next;
		last->key = key;
		last->value = value;
		last->next = NULL;
	}
	return (1);
}

int	print_value(t_HashNode *node, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (node)
	{
		if (ft_strncmp(node->key, key, key_len) == 0)
		{
			write(STDOUT_FILENO, node->value, ft_strlen(node->value));
			write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		node = node->next;
	}
	printf("%s: not found\n", key);
	return (0);
}

// non viene gestito il caso dell'ultima riga senza new line per ogni lettura
int	parsing(t_HashMap *hashmap, t_longlong **hashlist)
{
	char		buff[BUFFER_SIZE + 1];
	char		line[BUFFER_SIZE + 1];
	int			bytes;
	int			buff_i;
	long long	hash;
	char		*key;
	int			i;
	int			len;
	char		*c;
	int			offset;

	i = 0;
	bytes = 1;
	offset = 0;
	while (bytes > 0)
	{
		// bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		bytes = read(STDIN_FILENO, buff + offset, BUFFER_SIZE - offset);
		// ft_putnbr(bytes);
		if (bytes < 0)
		{
			printf("error: reading from stdin\n");
			return (0);
		}
		if (bytes == 0)
			return (1);
		bytes += offset;
		buff[bytes] = '\0';
		buff_i = 0;
		while (buff_i < bytes)
		{
			c = ft_strchr(buff + buff_i, '\n');
			if (c)
			{
				len = c - (buff + buff_i);
				if (len == 0)
				{
					buff_i++;
					i = 2;
					continue ;
				}
				memcpy(line, buff + buff_i, len);
				line[len] = '\0';
				if (i == 0)
				{
					key = ft_strdup(line);
					if (!key)
					{
						printf("error: memory allocation failed!\n");
						return (0);
					}
					hash = hashing(line);
					if (hash < 0)
					{
						printf("error: key not valid!\n");
						return (0);
					}
					if (!append_hashlist(hashlist, hash))
					{
						printf("error: memory allocation failed!\n");
						return (0);
					}
					i = 1;
				}
				else if (i == 1)
				{
					if (!append_hashmap(&(hashmap->table[hash]), key,
							ft_strdup(line)))
					{
						printf("error: memory allocation failed!\n");
						return (0);
					}
					i = 0;
				}
				else
				{
					hash = hashing(line);
					if (hash < 0)
					{
						printf("error: key not valid!\n");
						continue ;
					}
					if (hashmap->table[hash])
						print_value(hashmap->table[hash], line);
					else
						printf("%s: not found\n", line);
				}
				buff_i += len + 1;
			}
			else
			{
				memcpy(buff, buff + buff_i, bytes - buff_i);
				offset = bytes - buff_i;
				buff_i = bytes;
				break ;
			}
		}
	}
	return (1);
}

// while (line && ft_strncmp(line, "\n", 2))
	// {
	// 	if (!i)
	// 	{
	// 		hash = hashing(line);
			// printf("%lld\n", hash);
			// write(STDOUT_FILENO, line, ft_strlen(line));
			// write(STDOUT_FILENO, ": ", 2);
			// ft_putnbr(hash);
			// write(STDOUT_FILENO, "\n", 1);
	// 		if (hash < 0)
	// 		{
	// 			printf("error: key not valid!\n");
	// 			free(line);
				// free_hashmap(hashmap, hashlist);
	// 			free_hashlist(hashlist);
	// 			return (1);
	// 		}
	// 		append_hashlist(&hashlist, hash);
	// 		key = line;
	// 	}
	// 	else
	// 	{
	// 		append_hashmap(&(hashmap.table[hash]), key, line);
			// printf("%s", line);
	// 	}
	// 	i++;
	// 	i %= 2;
	// 	line = get_next_line(STDIN_FILENO);
	// }
int	main( void )
{
	t_HashMap	hashmap;
	t_longlong	*hashlist;

	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	hashlist = NULL;
	if (!parsing(&hashmap, &hashlist))
	{
		free_hashlist(hashlist);
		return (1);
	}
	return (0);
}
