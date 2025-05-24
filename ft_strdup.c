/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:58:34 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 09:44:14 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = (char *)ft_calloc(len, sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*str_dup_till_charset(const char *str, const char *charset)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && !ft_strchr(charset, str[i]))
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}
