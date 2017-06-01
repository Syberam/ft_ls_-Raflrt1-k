/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool_for_ldisplay.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 23:49:53 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/05/31 08:38:05 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void		ft_fields_size(t_direct *daddir, t_direct *current)
{
	size_t	usr_len;
	size_t	grp_len;
	size_t	size_len;
	size_t	lnk_len;

	usr_len = (!getpwuid(current->file_stat.st_uid)) ?
					ft_ilen(current->file_stat.st_uid) :
					ft_strlen(getpwuid(current->file_stat.st_uid)->pw_name);
	grp_len = (!getgrgid(current->file_stat.st_gid)) ?
					ft_ilen(current->file_stat.st_gid) :
					ft_strlen(getgrgid(current->file_stat.st_gid)->gr_name);
	size_len = (size_t)ft_ilen((int)(current->file_stat.st_size));
	lnk_len = (size_t)ft_ilen((int)(current->file_stat.st_nlink));
	daddir->usr_field = (!daddir->usr_field || daddir->usr_field < usr_len) ?
							usr_len : daddir->usr_field;
	daddir->grp_field = (!daddir->grp_field || daddir->grp_field < grp_len) ?
							grp_len : daddir->grp_field;
	daddir->size_field = (!daddir->size_field || daddir->size_field < size_len) ?
							size_len : daddir->size_field;
	daddir->lnk_field = (!daddir->lnk_field || daddir->lnk_field < lnk_len) ?
							lnk_len : daddir->lnk_field;
}
