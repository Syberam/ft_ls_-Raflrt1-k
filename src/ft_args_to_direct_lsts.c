/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_to_direct_lsts.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 00:17:17 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/03 06:53:56 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void		direct_to_directlst_alsort(t_direct *new, t_direct *lst,
												t_opt *op)
{
	t_direct	*cmp;
	t_direct	*tmp;

	cmp = lst;
	while (cmp && ((!op->reverse) ?
			ft_strcmp((const char *)new->path, (const char *)cmp->path) >= 0 :
			ft_strcmp((const char *)new->path, (const char *)cmp->path) <= 0))
	{
		tmp = cmp;
		cmp = cmp->next;
	}
	if (cmp == lst)
	{
		new->next = lst;
		if (lst == op->first_d)
			op->first_d = new;
		else
			op->arg_file = new;
		return ;
	}
	new->next = tmp->next;
	tmp->next = new;
}

static void		direct_to_directlst_tsort(t_direct *new, t_direct *lst,
												t_opt *op)
{
	t_direct	*cmp;
	t_direct	*tmp;

	cmp = lst;
	while (cmp && ((!op->reverse) ? ft_time_dif(new, cmp) > 0 :
											ft_time_dif(new, cmp) < 0))
	{
		tmp = cmp;
		cmp = cmp->next;
	}
	while (cmp && !ft_time_dif(new, cmp) && ((!op->reverse) ?
ft_strcmp(new->path, cmp->path) <= 0 : ft_strcmp(new->path, cmp->path) >= 0))
	{
		tmp = cmp;
		cmp = cmp->next;
	}
	if (cmp == lst)
	{
		new->next = lst;
		op->first_d = (lst == op->first_d) ? new : op->first_d;
		op->arg_file = (lst == op->arg_file) ? new : op->arg_file;
		return ;
	}
	new->next = tmp->next;
	tmp->next = new;
}

static void		ft_dir_to_direct(char *new, t_stat stats, t_opt *op)
{
	t_direct	*new_dir;
	t_direct	*tmp;

	op->first_line =  op->first_line == 10 ? 0 : 1;
	new_dir = ft_memalloc(sizeof(t_direct));
	new_dir->path = ft_write_path(NULL, new);
	new_dir->file_stat = stats;
	if (!op->first_d)
		op->first_d = new_dir;
	else if (op->opt_f)
	{
		tmp = op->first_d;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_dir;
	}
	else
		(!op->time_sort) ? direct_to_directlst_alsort(new_dir, op->first_d,
				op) : direct_to_directlst_tsort(new_dir, op->first_d, op);
}

static void		ft_file_to_direct(char *new, t_stat stats, t_opt *op)
{
	t_direct	*new_file;
	t_direct	*tmp;

	new_file = ft_memalloc(sizeof(t_direct));
	new_file->path = ft_write_path(NULL, new);
	new_file->file_stat = stats;
	if (!op->arg_file)
		op->arg_file = new_file;
	else if (op->opt_f)
	{
		tmp = op->arg_file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_file;
	}
	else
		(!op->time_sort) ? direct_to_directlst_alsort(new_file, op->arg_file,
				op) : direct_to_directlst_tsort(new_file, op->arg_file, op);
}

t_opt			*ft_args_to_direct_lsts(t_opt *op)
{
	int			i;
	t_stat		file_stats;

	if (!op || !op->av_dir)
		return (op);
	i = 0;
	ft_init_root(op, 0);
	while (op->av_dir[i])
	{
		if (lstat(op->av_dir[i], &file_stats) == -1)
			ft_wrg_dir(op, op->av_dir[i]);
		else if (S_ISDIR(file_stats.st_mode))
			ft_dir_to_direct(op->av_dir[i], file_stats, op);
		else
			ft_file_to_direct(op->av_dir[i], file_stats, op);
		i++;
	}
	return (op);
}
