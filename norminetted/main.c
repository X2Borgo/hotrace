/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:33:24 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 16:03:53 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	g_char_values[256] = {0};

int	main( void )
{
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	t_HashMap	hashmap;
	t_longlong	*hashlist;

	hashmap.table = (t_HashNode **)malloc(sizeof(t_HashNode *) * SIZE);
	ft_memset(hashmap.table, 0, sizeof(t_HashNode *) * SIZE);
	hashlist = NULL;
	init_hash_lookup();
	if (!parsing(&hashmap, &hashlist))
	{
		free_hashlist(hashlist);
		return (1);
	}
	ft_write(1, "", 0);
	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_taken = (end.tv_sec - start.tv_sec) + 
	(end.tv_nsec - start.tv_nsec) / 1e9;
	fprintf(stderr, "Execution time: %.9f seconds\n", time_taken);
	return (0);
}
