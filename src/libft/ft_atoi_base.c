/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:29:15 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/03/30 21:27:03 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_a_to_i(char *str, char base, int len)
{
	long	nb;
	int		pw;
	int		unit;

	nb = 0;
	pw = 0;
	unit = 0;
	while (len - pw > 0)
	{
		if (str[len - pw - 1] > 47 && str[len - pw - 1] < 58)
			unit = str[len - pw - 1] - 48;
		else if (str[len - pw - 1] > 64 && str[len - pw - 1] < 71)
			unit = str[len - pw - 1] - 55;
		else if (str[len - pw - 1] > 96 && str[len - pw - 1] < 103)
			unit = str[len - pw - 1] - 87;
		nb = nb + unit * ft_power(base, pw);
		pw++;
	}
	return (nb);
}

int			ft_a_len(char *str, char base)
{
	int		i;
	int		ch;
	int		lt;

	i = 0;
	ch = (base < 10) ? base - 1 : 9;
	lt = (base > 10) ? base - 11 : -1;
	while ((str[i] > 47 && str[i] < 49 + ch)
			|| (str[i] > 64 && str[i] < 66 + lt)
				|| (str[i] > 96 && str[i] < 98 + lt))
		i++;
	ft_putnbr(i);
	ft_putchar('\n');
	return (i);
}

int			ft_atoi_base(char *str, char base)
{
	size_t	i;
	int		len;

	i = 0;
	if (base == 10)
		return (ft_atoi(str));
	else if (base < 2 || base > 16 || str[0] == 0)
		return (0);
	while (str[i] < 33 || str[i] > 126)
		i++;
	len = ft_a_len(str + i, base);
	return (ft_a_to_i(ft_strsub(str, i, len), base, len));
}
