/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 19:01:30 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/05 03:56:42 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_stack(int n)
{
	char	a[12];
	char	*a_str;
	size_t	l_n;
	size_t	i;

	i = 0;
	ft_bzero(a, 12);
	while (i < 12)
		a[i++] = '\0';
	i = 0;
	l_n = ft_ilen(n);
	if (n < 0)
	{
		a[i] = '-';
		while (++i < l_n)
			a[i] = 10 - (n / ft_power(10, l_n - i - 1) % 10) + 38;
	}
	while (i < l_n)
	{
		a[i] = ((n / ft_power(10, l_n - i - 1)) % 10) + 48;
		i++;
	}
	a[i] = 0;
	a_str = a;
	return (a_str);
}
