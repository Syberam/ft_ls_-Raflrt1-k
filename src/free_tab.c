/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:49:47 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/05/23 04:10:05 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void		ft_free_tab_str(char **args)
{
	size_t	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (args[i][0])
			free(args[i]);
		i++;
	}
	free(args);
}
