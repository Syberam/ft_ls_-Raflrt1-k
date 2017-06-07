/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:21:48 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/07 09:49:20 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

char		*ft_time_for_display(t_stat stat_file, t_opt *options)
{
	time_t	ref;
	char	*line;
	int		i;

	time(&ref);
	line = ctime(&stat_file.st_mtime);
	if (options->big_t)
		return (line);
	if (ref - stat_file.st_mtime > 15552000 || ref - stat_file.st_mtime < 0)
	{
		i = 11;
		line[i] = ' ';
		while (++i < 17)
			line[i] = line[i + 8];
		line[i] = 0;
	}
	else
		line[17] = 0;
	return (line);
}

int			ft_time_dif(t_direct *bef, t_direct *aft)
{
	int		diff;

	if (!aft)
		return (1);
	diff = aft->file_stat.st_mtime - bef->file_stat.st_mtime;
	return (diff);
}
