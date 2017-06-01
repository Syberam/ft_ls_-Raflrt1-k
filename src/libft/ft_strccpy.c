/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:17:07 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/02/11 20:19:01 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strccpy(char *dst, const char *src, int c)
{
	int		i;

	i = 0;
	if (!ft_strchr(src, c))
		dst = ft_strcpy(dst, src);
	else
	{
		while (src[i] != 0 && src[i] != c)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (dst);
}
