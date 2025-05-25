/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:11:28 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/25 15:56:04 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (s[i] != ch && s[i] != '\0')
		i++;
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}
