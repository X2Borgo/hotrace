/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:09:17 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/25 18:16:45 by alborghi         ###   ########.fr       */
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
			free(key);
			tmp->value = value;
			return (1);
		}
		*last = tmp;
		tmp = tmp->next;
	}
	return (0);
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
