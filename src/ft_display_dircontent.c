/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_dircontent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 23:14:40 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/01 04:30:42 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void			ft_del_dir_in_directlst(t_direct *dir, t_opt *op)
{	
	op->first_d = dir->next;
	ft_bzero((void *)dir->path, sizeof(dir->path));
	free((void *)dir->path);
	free((void *)dir);
}

t_direct		*ft_put_in_direct_lst(t_direct *prev, t_direct *new, t_opt *op)
{
	if (ft_strcmp(".\0", ft_strrchr(new->path, '/') + 1) == 0 ||
			ft_strcmp("..\0", ft_strrchr(new->path, '/') + 1) == 0)
		return (prev);
	if (op && !op->all && ft_strrchr(new->path, '/')[0] == '.')
		return (prev);
	if (op)
		op->first_line = 1;
	if (prev)
	{
		new->next = prev->next;
		prev->next = new;
	}
	else
		op->first_d = new;
	return (new);
}

static void		ft_display_lst(t_direct *item, t_direct *dad, t_opt *op)
{
	t_direct	*current;
	t_direct	*tmp;
	t_direct	*prev;
	t_direct	*prev_tmp;

	current = dad;
	current = item;
	prev = op->first_d;
	while (current)
	{
		tmp = current->next;
		ft_display_indir_node(current, dad,  op);
		if (op->recurs && S_ISDIR(current->file_stat.st_mode))
		{
			prev_tmp = prev;
			prev = ft_put_in_direct_lst(prev, current, op);
			if (prev_tmp == prev)
			{
				free((void *)current->path);
				free(current);
			}
		}
		else
		{
			free((void *)current->path);
			free(current);
		}
		current = tmp;
	}
}

void			ft_display_dircontent(t_direct *dir, t_opt *op)
{
	t_direct	*curline;

	if (op && op->first_line)
	{
		ft_putchar('\n');
		ft_putstr(dir->path);
		ft_putendl(":");
	}
	op->first_line = 1;
	if (ft_permis_den(dir))  //  PUT BEFORE GET_DIRCONTENT
	{
		ft_del_dir_in_directlst(dir, op);
		return ;
	}
	if (op && op->long_format)
	{
		ft_putstr("total ");
		op->opt_k ? ft_putnbr((dir->ph_lnk) / 2) : ft_putnbr(dir->ph_lnk);
		ft_putchar('\n');
	}
	if (!(dir->content))
	{
		ft_del_dir_in_directlst(dir, op);
		return (ft_putendl("FAIL"));
	}
	curline = dir->content;
	curline->next ? ft_display_lst(curline, dir, op) :
						ft_display_tree(curline, NULL, dir, op);
	ft_del_dir_in_directlst(dir, op);
}
