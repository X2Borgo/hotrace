/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 10:50:15 by alborghi         ###   ########.fr       */
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

void	free_hashmap(t_HashMap *hashmap, t_longlong *hashlist)
{
	t_HashNode	*tmp;
	t_longlong	*tmp_hash;
	t_HashNode	*to_free;
	
	if (!hashmap || !hashlist)
		return ;
	tmp_hash = hashlist;
	while (tmp_hash)
	{
		tmp = hashmap->table[tmp_hash->hash];
		while (tmp)
		{
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->key);
			free(to_free->value);
			free(to_free);
		}
		tmp_hash = tmp_hash->next;
	}
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
