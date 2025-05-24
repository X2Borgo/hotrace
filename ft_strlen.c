/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:20:50 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 09:40:49 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	ft_strlen(const char *str)
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
