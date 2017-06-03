/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dircontent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 22:52:47 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/03 21:25:11 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static t_direct	*ft_init_new_bud(char *new)
{
	t_direct	*new_bud;

	new_bud = (t_direct *)ft_memalloc(sizeof(t_direct));
	new_bud->path = new;
	new_bud->next = NULL;
	lstat((const char *)new, &new_bud->file_stat);
	return (new_bud);
}

static void		ft_new_listree_elem(t_direct *daddir, char *new, t_opt *op)
{
	t_direct	*new_bud;
	t_direct	*curnode;

	if (!new)
		return ;
	new_bud = ft_init_new_bud(new);
	if (!daddir->content)
		daddir->content = new_bud;
	if (op->long_format)
		ft_fields_size(daddir, new_bud);
	if (new_bud != daddir->content)
	{
		curnode = daddir->content;
		while (curnode->next)
			curnode = curnode->next;
		curnode->next = new_bud;
	}
}

static t_direct	*ft_insertornot(t_direct *curnode, t_direct *new_bud, char l_r)
{
	if (l_r == 'r')
	{
		if (!curnode->right)
		{
			curnode->right = new_bud;
			new_bud->relat = curnode;
			curnode = curnode->right;
		}
		curnode = curnode->right;
	}
	else
	{
		if (!curnode->left)
		{
			curnode->left = new_bud;
			new_bud->relat = curnode;
			curnode = curnode->left;
		}
		curnode = curnode->left;
	}
	return (curnode);
}

static void		ft_new_bud(t_direct *daddir, char *bud, t_opt *op)
{
	t_direct	*new_bud;
	t_direct	*curnode;

	if (!bud)
		return ;
	new_bud = ft_init_new_bud(bud);
	if (op->long_format)
		ft_fields_size(daddir, new_bud);
	if (!daddir->content)
		daddir->content = new_bud;
	else
	{
		curnode = daddir->content;
		while (curnode)
		{
			if (op->time_sort && ft_time_dif(curnode, new_bud) > 0)
				curnode = ft_insertornot(curnode, new_bud, 'l');
			else if (op->time_sort && ft_time_dif(curnode, new_bud) < 0)
				curnode = ft_insertornot(curnode, new_bud, 'r');
			else if (ft_strcmp(curnode->path, new_bud->path) > 0)
				curnode = ft_insertornot(curnode, new_bud, 'l');
			else
				curnode = ft_insertornot(curnode, new_bud, 'r');
		}
	}
}

t_opt			*ft_get_dircontent(t_direct *daddir, t_opt *op)
{
	DIR			*diropen;
	t_dirent	*in;
	char		*path;

	if (!(diropen = opendir(daddir->path)))
		return (op);
	daddir->ph_lnk = 0;
	while ((in = readdir(diropen)))
	{
		path = ft_write_path((char *)daddir->path, in->d_name);
		op->opt_f ? ft_new_listree_elem(daddir, path, op)
						: ft_new_bud(daddir, path, op);
	}
	return (op);
}
