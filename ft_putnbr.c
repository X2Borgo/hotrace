/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:29:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/24 13:55:13 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int				len;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}
