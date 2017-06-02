/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:08 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/01 20:33:08 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

char		*ft_write_path(char *dad, char *child)
{
	char	*path;

	if (!dad)
	{
		path = ft_ext_strjoin_free(child, NULL, 0);
		return (path);
	}
	if (dad && dad[ft_strlen(dad) - 1] != '/')
	{
		path = ft_ext_strjoin_free(dad, "/\0", 0);
		path = ft_ext_strjoin_free(path, child, 0);
	}
	else
		path = ft_ext_strjoin_free(dad, child, 0);
	return (path);
}

void		ft_init_root(t_opt *options, size_t i)
{
	if (!options->av_dir[i])
	{
		options->av_dir[i] = "./\0";
		options->av_dir[1] = 0;
	}
}
