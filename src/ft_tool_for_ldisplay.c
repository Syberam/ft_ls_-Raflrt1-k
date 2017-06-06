/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool_for_ldisplay.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 23:49:53 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/06 05:54:55 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

char		*ft_size_or_minmaj(t_direct *cur)
{
	char	*min_maj = NULL;
	char	*line;
	char	*spaces;
	int		sp;

	if (!S_ISBLK(cur->file_stat.st_mode) && !S_ISCHR(cur->file_stat.st_mode))
		return (ft_itoa(cur->file_stat.st_size));
	spaces = "    ";
	min_maj = ft_itoa((int)major(cur->file_stat.st_rdev));
	sp = ft_strlen(min_maj);
	line = ft_ext_strjoin_free(spaces + sp, min_maj, 2);
	line = ft_ext_strjoin_free(line, ",", 1);
	min_maj = ft_itoa(minor(cur->file_stat.st_rdev));
	sp = ft_strlen(min_maj);
	line = ft_ext_strjoin_free(line, spaces + sp, 1);
	line = ft_ext_strjoin_free(line, min_maj, 3);
	return (line);
}

void		ft_print_total(t_direct *dir, t_opt *op)
{
	if (op && op->long_format)
	{
		ft_putstr("total ");
		if (op->opt_k)
			ft_putnbr(dir->ph_lnk - (dir->ph_lnk / 2));
		else
			ft_putnbr(dir->ph_lnk);
		ft_putchar('\n');
	}
}

void		ft_fields_size(t_direct *dad, t_direct *cur)
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
	dad->usr_field = (!dad->usr_field || dad->usr_field < usr_len) ?
							usr_len : dad->usr_field;
	dad->grp_field = (!dad->grp_field || dad->grp_field < grp_len) ?
							grp_len : dad->grp_field;
	dad->size_field = (!dad->size_field || dad->size_field < size_len) ?
							size_len : dad->size_field;
	dad->lnk_field = (!dad->lnk_field || dad->lnk_field < lnk_len) ?
							lnk_len : dad->lnk_field;
	dad->ph_lnk += cur->file_stat.st_blocks;
}
