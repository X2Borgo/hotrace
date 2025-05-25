/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:00:46 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/25 14:29:39 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	ft_write(int fd, const char *str, size_t len)
{
	static char		buffer[WRITE_SIZE];
	static size_t	buffer_index = 0;

	if (len == 0)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
		return ;
	}
	if (buffer_index + len >= WRITE_SIZE)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
	}
	ft_memcpy(buffer + buffer_index, str, len);
	buffer_index += len;
}
