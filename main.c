/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 17:57:10 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	g_char_values[256] = {0};

int	main( void )
{
	t_HashMap	hashmap;

	hashmap.table = (t_HashNode **)malloc(sizeof(t_HashNode *) * SIZE);
	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	init_hash_lookup();
	if (!parsing(&hashmap))
	{
		ft_write(1, "", 0);
		free_hashmap(&hashmap);
		return (1);
	}
	ft_write(1, "", 0);
	free_hashmap(&hashmap);
	return (0);
}
