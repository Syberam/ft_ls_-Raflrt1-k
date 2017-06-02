/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dircontent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 22:52:47 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/02 06:29:06 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void		ft_new_listree_elem(t_direct *daddir, char *new, t_opt *op)
{
	t_direct	*new_bud;
	t_direct	*curnode;

	if (!new)
		return ;
	new_bud = (t_direct *)ft_memalloc(sizeof(t_direct));
	new_bud->path = new;
	new_bud->next = NULL;
	lstat((const char *)new, &new_bud->file_stat);
	if (!daddir->content)
		daddir->content = new_bud;
	if (op->long_format)
		ft_fields_size(daddir, new_bud);
	if (op->long_format)
		daddir->ph_lnk += new_bud->file_stat.st_blocks;
	if (new_bud != daddir->content)
	{
		curnode = daddir->content;
	while (curnode->next)
	{
		curnode = curnode->next;
	}
	curnode->next = new_bud;
	}
}

static void		ft_new_bud(t_direct *daddir, char *bud, t_opt *op)
{
	t_direct	*new_bud;
	t_direct	*curnode;

	if (!bud)
		return ;
	new_bud = (t_direct *)ft_memalloc(sizeof(t_direct));
	new_bud->path = bud;
	lstat((const char *)bud, &new_bud->file_stat);
	if (op->long_format)
		ft_fields_size(daddir, new_bud);
	if (!daddir->content)
		daddir->content = new_bud;
	else
	{
		ft_putendl(new_bud->path);
		curnode = daddir->content;
		while (curnode)
		{
			if (op->time_sort && ft_time_dif(new_bud, curnode) < 0)
			{
				if (!curnode->left)
				{
					ft_putstr(new_bud->path);
					ft_putstr(" put in left of : ");
					ft_putendl(curnode->path);
					curnode->left = new_bud;
					new_bud->relat = curnode;
					curnode = curnode->left;
				}
				curnode = curnode->left;
			}
			else if (op->time_sort && ft_time_dif(new_bud, curnode) > 0)
			{
				if (!curnode->right)
				{	
					ft_putstr(new_bud->path);
					ft_putstr(" put in right of : ");
					ft_putendl(curnode->path);
					curnode->right = new_bud;
					new_bud->relat = curnode;
					curnode = curnode->right;
				}
				curnode = curnode->right;
			}
			else if (ft_strcmp(new_bud->path, curnode->path) <= 0) // || <0 ??
			{
				if (!curnode->left)
				{	
					ft_putstr(new_bud->path);
					ft_putstr(" put in left of : ");
					ft_putendl(curnode->path);
					curnode->left = new_bud;
					new_bud->relat = curnode;
					curnode = curnode->left;
				}
				curnode = curnode->left;
			}
			else
			{
				if (!curnode->right)
				{
					ft_putstr(new_bud->path);
					ft_putstr(" put in right of : ");
					ft_putendl(curnode->path);
					curnode->right = new_bud;
					new_bud->relat = curnode;
					curnode = curnode->right;
				}
				curnode = curnode->right;
			}
		}
	}
	if (op->long_format)
		daddir->ph_lnk += new_bud->file_stat.st_blocks;
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
