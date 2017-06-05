/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:15:06 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/04 04:31:22 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void			ft_display_indir_node(t_direct *no, t_direct *dad, t_opt *op)
{
	t_direct	*tmp;

	if (!op->opt_f && !op->tmp_first_d)
		op->tmp_first_d = no;
	else if (!op->opt_f)
	{
		tmp = op->tmp_first_d;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = no;
	}
	if ((strrchr(no->path, '/'))[1] == '.' && !op->all)
		return ;
	if (op && op->col)
		ft_putendl(ft_strrchr(no->path, '/') + 1);
	else if (op && !op->long_format)
	{
		ft_putstr(ft_strrchr(no->path, '/') + 1);
		no->right || no->left || no->next ? ft_putchar('\t') : ft_putchar('\n');
	}
	else
		ft_display_long(no, dad, op);
}

static void		ft_display_tree_rev(t_direct *no, t_direct *dad, t_opt *op)
{
	if (!no)
		return ;
	if (no->right)
		ft_display_tree(no->right, dad, op);
	ft_display_indir_node(no, dad, op);
	if (no->left)
		ft_display_tree(no->left, dad, op);
}

static void		ft_display_tree_(t_direct *no, t_direct *dad, t_opt *op)
{
	if (!no)
		return ;
	if (no->left)
		ft_display_tree(no->left, dad, op);
	ft_display_indir_node(no, dad, op);
	if (no->right)
		ft_display_tree(no->right, dad, op);
}

void			ft_display_tree(t_direct *no, t_direct *dad, t_opt *op)
{
	op->reverse ? ft_display_tree_rev(no, dad, op) :
					ft_display_tree_(no, dad, op);
}
