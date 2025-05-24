/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:06:20 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 15:26:00 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, (char *) s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (join);
}

char	*ft_strjoin_free_1_2(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, (char *) s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free((char *)s1);
	free((char *)s2);
	return (join);
}

char	*ft_strjoin_free_1(char const *s1, char const *s2)
{
	char	*join;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		join = ft_strdup(s1);
		free((char *)s1);
		return (join);
	}
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, (char *) s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free((char *)s1);
	return (join);
}

char	*ft_strjoin_free_2(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, (char *) s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free((char *)s2);
	return (join);
}
