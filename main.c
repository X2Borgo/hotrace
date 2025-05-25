/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 14:23:02 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	g_char_values[256];

void	init_hash_lookup(void)
{
	int	i;

	ft_memset(g_char_values, 0, sizeof(g_char_values));
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

long long	hashing(char *key)
{
	long long		hash;
	long long		p_pow;
	int				char_val;
	unsigned char	*ukey;

	hash = 0;
	p_pow = 1;
	ukey = (unsigned char *)key;
	while (*ukey && *ukey != '\n')
	{
		char_val = g_char_values[*ukey];
		if (char_val == 0)
			return (-1);
		hash = (hash + char_val * p_pow) % M;
		p_pow = (p_pow * P) % M;
		ukey++;
	}
	return (hash);
}

// long long	hashing(char *key)
// {
// 	long long	hash;
// 	int			i;
// 	long long	p_pow;

// 	i = 0;
// 	hash = 0;
// 	p_pow = 1;
// 	while (key[i] && key[i] != '\n')
// 	{
// 		if (key[i] >= 'a' && key[i] <= 'z')
// 			hash = (hash + (key[i] - 'a' + 1) * p_pow) % M;
// 		else if (key[i] >= 'A' && key[i] <= 'Z')
// 			hash = (hash + (key[i] - 'A' + 27) * p_pow) % M;
// 		else if (key[i] >= '0' && key[i] <= '9')
// 			hash = (hash + (key[i] - '0' + 53) * p_pow) % M;
// 		else if (key[i] == '_')
// 			hash = (hash + 63 * p_pow) % M;
// 		else if (key[i] == ' ')
// 			hash = (hash + 64 * p_pow) % M;
// 		else
// 			return (-1);
// 		p_pow = (p_pow * P) % M;
// 		i++;
// 	}
// 	return (hash);
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;

	__asm__ volatile (
		// Save registers we'll modify
		"push %%rcx\n"
		// Main comparison loop
		"1:\n"
		"movzbl (%0), %%eax\n" // Load byte from s1 into eax
		"movzbl (%1), %%ecx\n" // Load byte from s2 into ecx
		"incq %0\n"// Increment s1 pointer
		"incq %1\n"// Increment s2 pointer
		"testb %%al, %%al\n"// Check if we reached end of s1
		"je 2f\n"// If zero, exit loop
		"cmpb %%cl, %%al\n"// Compare bytes
		"je 1b\n"// If equal, continue loop
		// Exit point - compute difference
		"2:\n"
		"subl %%ecx, %%eax\n"// Compute difference
		"pop %%rcx\n"// Restore rcx
		: "=&S"(s1), "=&D"(s2), "=&a"(result)
		: "0"(s1), "1"(s2)
		: "memory", "cc");
	return (result);
}

/* int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
} */

t_longlong	*append_hashlist(t_longlong **hashlist, t_longlong *tail,
							long long hash)
{
	t_longlong	*new_node;

	new_node = (t_longlong *)malloc(sizeof(t_longlong));
	if (!new_node)
		return (NULL);
	new_node->hash = hash;
	new_node->next = NULL;
	if (!*hashlist)
	{
		*hashlist = new_node;
		return (new_node);
	}
	tail->next = new_node;
	return (new_node);
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

int	existing_nodes(t_HashNode *node, char *key, char *value, t_HashNode **last)
{
	t_HashNode	*tmp;

	tmp = node;
	*last = tmp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		*last = tmp;
		tmp = tmp->next;
	}
	return (0);
}

t_HashNode	*create_hash_node(char *key, char *value)
{
	t_HashNode	*node;

	node = (t_HashNode *)malloc(sizeof(t_HashNode));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

int	append_hashmap(t_HashNode **node, char *key, char *value)
{
	t_HashNode	*last;

	if (!key || !value)
		return (0);
	if (*node == NULL)
	{
		*node = create_hash_node(key, value);
		if (!*node)
			return (0);
	}
	else
	{
		if (existing_nodes(*node, key, value, &last))
			return (1);
		last->next = create_hash_node(key, value);
		if (!last->next)
			return (0);
		last = last->next;
	}
	return (1);
}

int	print_value(t_HashNode *node, char *key)
{
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			ft_write(STDOUT_FILENO, node->value, ft_strlen(node->value));
			ft_write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		node = node->next;
	}
	ft_write(1, key, ft_strlen(key));
	ft_write(1, ": not found\n", 12);
	return (0);
}

int	main( void )
{
	struct timespec	start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
	t_HashMap	hashmap;
	t_longlong	*hashlist;

	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	hashlist = NULL;
	init_hash_lookup();
	if (!parsing(&hashmap, &hashlist))
	{
		free_hashlist(hashlist);
		return (1);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_taken = (end.tv_sec - start.tv_sec) + 
	(end.tv_nsec - start.tv_nsec) / 1e9;
	fprintf(stderr, "Execution time: %.9f seconds\n", time_taken);
	return (0);
}
