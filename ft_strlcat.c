/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:44:15 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 10:02:37 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] != '\0')
		j++;
	if (j >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (i + j < size - 1 && src[i] != '\0')
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i + j);
}
