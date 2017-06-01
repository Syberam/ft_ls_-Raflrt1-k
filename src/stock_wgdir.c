/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_wgdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:00:57 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/05/31 01:06:45 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

t_opt	*ft_wrg_dir(t_opt *options, char *new_wrg)
{
	char		**wg_dir_reall;
	size_t		i;

	if (!options->wg_dir)
	{
		options->wg_dir = (char **)ft_memalloc(sizeof(char *) * 2);
		options->wg_dir[0] = ft_strdup(new_wrg);
		options->wg_dir[1] = 0;
	}
	else if (1 == 1 + (i = 0))
	{
		while (options->wg_dir[i] != 0)
			i++;
		wg_dir_reall = (char **)ft_memalloc(sizeof(char *) * (i + 2));
		i = 0;
		while (options->wg_dir[++i - 1])
			wg_dir_reall[i - 1] = options->wg_dir[i - 1];
		wg_dir_reall[i - 1] = ft_strdup(new_wrg);
		wg_dir_reall[i] = 0;
		free(options->wg_dir);
		options->wg_dir = wg_dir_reall;
	}
	return (options);
}
