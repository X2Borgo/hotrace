/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:44:34 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 10:03:54 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

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

char	*ft_strnchr(const char *s, int c, size_t len)
{
	size_t			i;
	unsigned char	ch;

	if (!s)
		return (NULL);
	i = 0;
	ch = (unsigned char)c;
	while (i < len && s[i] != ch && s[i])
		i++;
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}
