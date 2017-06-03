/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool_for_ldisplay.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 23:49:53 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/03 21:12:44 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

char		*ft_size_or_minmaj(t_direct *cur)
{
	char	*min;
	char	*maj;
	char	*line_part;
	char	*spaces;
	int		len_sp;

	if (!S_ISBLK(cur->file_stat.st_mode) && !S_ISCHR(cur->file_stat.st_mode))
		return (ft_itoa(cur->file_stat.st_size));
	spaces = "    ";
	maj = ft_itoa(major(cur->file_stat.st_rdev));
	len_sp = ft_strlen(maj);
	line_part = ft_ext_strjoin_free(spaces + len_sp, maj, 2);
	line_part = ft_ext_strjoin_free(line_part, ",", 1);
	min = ft_itoa(minor(cur->file_stat.st_rdev));
	len_sp = ft_strlen(min);
	line_part = ft_ext_strjoin_free(line_part, spaces + len_sp, 1);
	line_part = ft_ext_strjoin_free(line_part, min, 3);
	return (line_part);
}

void		ft_fields_size(t_direct *daddir, t_direct *cur)
{
	size_t	usr_len;
	size_t	grp_len;
	size_t	size_len;
	size_t	lnk_len;

	usr_len = (!getpwuid(cur->file_stat.st_uid)) ?
					ft_ilen(cur->file_stat.st_uid) :
					ft_strlen(getpwuid(cur->file_stat.st_uid)->pw_name);
	grp_len = (!getgrgid(cur->file_stat.st_gid)) ?
					ft_ilen(cur->file_stat.st_gid) :
					ft_strlen(getgrgid(cur->file_stat.st_gid)->gr_name);
	size_len = (S_ISBLK(cur->file_stat.st_mode) ||
							S_ISCHR(cur->file_stat.st_mode)) ?
							8 : (size_t)ft_ilen((int)(cur->file_stat.st_size));
	lnk_len = (size_t)ft_ilen((int)(cur->file_stat.st_nlink));
	daddir->usr_field = (!daddir->usr_field || daddir->usr_field < usr_len) ?
							usr_len : daddir->usr_field;
	daddir->grp_field = (!daddir->grp_field || daddir->grp_field < grp_len) ?
							grp_len : daddir->grp_field;
	daddir->size_field = (!daddir->size_field || daddir->size_field < size_len) ?
							size_len : daddir->size_field;
	daddir->lnk_field = (!daddir->lnk_field || daddir->lnk_field < lnk_len) ?
							lnk_len : daddir->lnk_field;
	daddir->ph_lnk += cur->file_stat.st_blocks;
}
