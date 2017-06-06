/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_recurs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 01:46:35 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/06 13:48:54 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void			ft_free_tmp_first_d(t_opt *op)
{
	t_direct	*current;
	t_direct	*tmp;

	current = op->tmp_first_d;
	while (current)
	{
		tmp = current;
		ft_bzero((void *)current->path, ft_strlen(current->path));
		free((void *)current->path);
		ft_bzero((void *)current, sizeof(current));
		free(current);
		current = tmp->next;
	}
	op->tmp_first_d = NULL;
}

void			ft_del_elem_from_lst(t_direct *prev, t_direct *elem, t_opt *op)
{
	if (!prev)
		op->tmp_first_d = elem->next;
	else
		prev->next = elem->next;
	ft_bzero((void *)elem->path, ft_strlen(elem->path));
	free((void **)elem->path);
	ft_bzero((void *)elem, sizeof(elem));
	free((void *)elem);
}

void			ft_confirm_tmp_first_d(t_opt *op)
{
	t_direct	*prev;
	t_direct	*cur;
	t_direct	*tmp;

	cur = op->tmp_first_d;
	prev = NULL;
	while (cur)
	{
		tmp = cur->next;
		if (!S_ISDIR(cur->file_stat.st_mode) ||
!strcmp(strrchr(cur->path, '/') + 1, ".\0") || !strcmp(strrchr(cur->path, '/')
	+ 1, "..\0") || (strrchr(cur->path, '/')[1] == '.' && !op->all))
			ft_del_elem_from_lst(prev, cur, op);
		else
			prev = cur;
		cur = tmp;
	}
	cur = op->tmp_first_d;
	if (!cur)
		return ;
	while (cur->next)
		cur = cur->next;
	cur->next = op->first_d->next;
	op->first_d->next = op->tmp_first_d;
	op->tmp_first_d = NULL;
}
