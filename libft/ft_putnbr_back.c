/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 05:46:04 by jguyet            #+#    #+#             */
/*   Updated: 2015/12/02 05:52:54 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

void	ft_putnbr_back(long int n)
{
	long int len;
	long int tmp;

	len = 1;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	tmp = n;
	while ((tmp = tmp / 10))
		len = len * 10;
	tmp = n;
	while (len)
	{
		ft_putchar((char)((tmp / len) + '0'));
		tmp = tmp % len;
		len = len / 10;
	}
	ft_putchar('\n');
}
