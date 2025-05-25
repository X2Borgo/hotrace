/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 18:41:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	free_hashmap(t_HashMap *hashmap)
{
	int			i;
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

int	main( void )
{
	t_HashMap	hashmap;

	hashmap.table = (t_HashNode **)malloc(sizeof(t_HashNode *) * SIZE);
	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	if (!parsing(&hashmap))
	{
		free_hashmap(&hashmap);
		return (1);
	}
	free_hashmap(&hashmap);
	return (0);
}
