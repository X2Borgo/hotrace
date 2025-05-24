/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 16:05:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

long long hashing(char *key)
{
	long long hash;
	int i;
	long long p_pow;

	i = 0;
	hash = 0;
	p_pow = 1;
	while (key[i] && key[i] != '\n')
	{
		if (ft_strchr(CHARS, key[i]) == NULL)
			return (-1);
		if (key[i] >= 'a' && key[i] <= 'z')
			hash = (hash + (key[i] - 'a' + 1) * p_pow) % M;
		else if (key[i] >= 'A' && key[i] <= 'Z')
			hash = (hash + (key[i] - 'A' + 27) * p_pow) % M;
		else if (key[i] >= '0' && key[i] <= '9')
			hash = (hash + (key[i] - '0' + 53) * p_pow) % M;
		else if (key[i] == '_')
			hash = (hash + ('z' - 'a' + 63) * p_pow) % M;
		else if (key[i] == ' ')
			hash = (hash + ('_' - 'a' + 64) * p_pow) % M;
		else
			return (-1);
		p_pow = (p_pow * P) % M;
		i++;
	}
	return (hash);
}

// TODO: check if the key already exists
int append_hashlist(t_longlong **hashlist, long long hash)
{
	t_longlong *new_node;
	t_longlong *tmp;

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
	t_longlong *tmp;

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
	t_longlong *tmp;

	while (hashlist)
	{
		tmp = hashlist;
		hashlist = hashlist->next;
		free(tmp);
	}
}

int	append_hashmap(t_HashNode **node, char *key, char *value)
{
	t_HashNode *tmp;
	t_HashNode *last;

	if (!key || !value)
		return (0);
	if (*node == NULL)
	{
		*node = (t_HashNode *)ft_calloc(1, sizeof(t_HashNode));
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
		while (tmp)
		{
			if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			{
				// write(STDOUT_FILENO, "key already exists, replacing value\n", 36);
				free(tmp->value);
				tmp->value = value;
				return (1);
			}
			last = tmp;
			tmp = tmp->next;
		}
		// write(STDOUT_FILENO, "adding to existing node\n", 24);
		last->next = (t_HashNode *)ft_calloc(1, sizeof(t_HashNode));
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
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
		{
			write(STDOUT_FILENO, node->key, ft_strlen(node->key));
			write(STDOUT_FILENO, ": ", 2);
			write(STDOUT_FILENO, node->value, ft_strlen(node->value));
			return (1);
		}
		node = node->next;
	}
	printf("%s: not found\n", key);
	return (0);
}

int	parsing(t_HashMap *hashmap, t_longlong **hashlist)
{
	char	buff[BUFFER_SIZE + 1];
	char	line[BUFFER_SIZE + 1];
	int		bytes;
	int		buff_i;
	long long hash;
	char *key;
	int i;
	int len;

	i = 0;
	bytes = 1;
	while (bytes > 0)
	{
		// write(STDOUT_FILENO, "reading from stdin\n", 19);
		bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			printf("error: reading from stdin\n");
			return (0);
		}
		if (bytes == 0)
			return (1);
		buff[bytes] = '\0';
		buff_i = 0;
		while (buff_i < bytes)
		{
			char *c = ft_strchr(buff + buff_i, '\n');
			if (c)
			{
				len = c - (buff + buff_i);
				if (len == 0)
				{
					buff_i++;
					i = 2;
					continue;
				}
			}
			memcpy(line, buff + buff_i, len);
			line[len] = '\0';
			if (i == 0)
			{
				// write(STDOUT_FILENO, "reading key\n", 12);
				key = ft_strdup(buff + buff_i);
				if (!key)
				{
					printf("error: memory allocation failed!\n");
					return (0);
				}
				hash = hashing(buff + buff_i);
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
				// write(STDOUT_FILENO, "adding to hashmap\n", 18);
				if (!append_hashmap(&(hashmap->table[hash]), key, ft_strdup(buff + buff_i)))
				{
					printf("error: memory allocation failed!\n");
					return (0);
				}
				i = 0;
				write(STDOUT_FILENO, hashmap->table[hash]->key, ft_strlen(hashmap->table[hash]->key));
				write(STDOUT_FILENO, ": ", 2);
				write(STDOUT_FILENO, hashmap->table[hash]->value, ft_strlen(hashmap->table[hash]->value));
				write(STDOUT_FILENO, "\n", 1);
				exit(1);
			}
			else
			{
				// write(STDOUT_FILENO, "searching\n", 10);
				hash = hashing(line);
				if (hash < 0)
				{
					printf("error: key not valid!\n");
					continue;
				}
				if (hashmap->table[hash])
					print_value(hashmap->table[hash], line);
				else
					printf("%s: not found\n", line);
			}
			buff_i += len + 1; // +1 for the newline character
			// write(STDOUT_FILENO, "cycle\n", 7);
		}
		// write(STDOUT_FILENO, "read cycle\n", 11);
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
int main( void )
{
	char *line;
	t_HashMap hashmap;
	t_longlong *hashlist;

	// Initialize the hashmap
	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	line = get_next_line(STDIN_FILENO);
	hashlist = NULL;
	if (!parsing(&hashmap, &hashlist))
	{
		free(line);
		free_hashlist(hashlist);
		return (1);
	}
	return (0);
}
