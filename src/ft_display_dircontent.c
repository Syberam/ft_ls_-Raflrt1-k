/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_dircontent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 23:14:40 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/07 13:29:28 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void			ft_del_dir_in_directlst(t_direct *dir, t_opt *op, char key)
{
	if (!key)
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

	current = item;
	prev = op->first_d;
	while (current)
	{
		tmp = current->next;
		ft_display_indir_node(current, dad, op);
		if (op->recurs && S_ISDIR(current->file_stat.st_mode))
		{
			prev_tmp = prev;
			prev = ft_put_in_direct_lst(prev, current, op);
			if (prev_tmp == prev)
				free((void *)current->path);
			if (prev_tmp == prev)
				free(current);
		}
		else
			ft_del_dir_in_directlst(current, op, 1);
		current = tmp;
	}
}

void			ft_display_dircontent(t_direct *dir, t_opt *op)
{
	if (!dir)
		return ;
	if (op && op->first_line == 1 && !op->perm)
	{
		ft_putchar('\n');
		ft_putstr(dir->path);
		ft_putendl(":");
	}
	op->first_line = 1;
	if (!(dir->content))
		return (ft_del_dir_in_directlst(dir, op, 0));
	ft_print_total(dir, op);
	(!op->opt_f)
		? ft_display_tree(dir->content, dir, op) :
			ft_display_lst(dir->content, dir, op);
	if (!op->opt_f)
		op->recurs ? ft_confirm_tmp_first_d(op) : ft_free_tmp_first_d(op);
	if (((dir->file_stat.st_mode & S_IXUSR) != S_IXUSR) && op->recurs)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_strrchr(dir->path, '/') ?
ft_putstr_fd(ft_strrchr(dir->path, '/') + 1, 2) : ft_putstr_fd(dir->path, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	ft_del_dir_in_directlst(dir, op, 0);
}
