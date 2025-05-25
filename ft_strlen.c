/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:20:50 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 19:51:00 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

/* size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
} */

size_t	ft_strlen(const char *str)
{
	const char	*s;
	size_t		word;

	if (!str)
		return (0);
	s = str;
	while (((uintptr_t)s & (sizeof(size_t) - 1)) == 0)
	{
		word = *(size_t *)s;
		if (((word - 0x0101010101010101UL) & ~word & 0x8080808080808080UL))
			break ;
		s += sizeof(size_t);
	}
	while (*s)
		s++;
	return (s - str);
}

int	ft_strlen_int(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (!str || str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_char_mat_len(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}
