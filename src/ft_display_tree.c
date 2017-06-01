/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:15:06 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/01 01:04:47 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void			ft_display_indir_node(t_direct *node, t_direct *dad, t_opt *op)
{	
	if (op && op->col)
		ft_putendl(ft_strrchr(node->path, '/'));
	else if (op && !op->long_format)
	{
		ft_putstr(ft_strrchr(node->path, '/'));
		ft_putchar('\t');
	}
	else
		ft_display_long(node, dad, op);
}

t_direct		*ft_display_tree_r(t_direct *node, t_direct *prev, t_direct *dad,
									t_opt *op)
{
	t_direct	*tmp;
	t_direct		*left;

	if (node->right)
		prev = ft_put_in_direct_lst(prev, node->right, op);
	ft_display_indir_node(node, dad, op);
	left = node->left;
	prev = (op->recurs) ? ft_put_in_direct_lst(prev, node, op) : prev;
	if (!op->recurs)
	{
		free((void *)node->path);
		free(node);
	}

	if (node->left)
	{
		tmp = ft_put_in_direct_lst(prev, left, op);
		if ((!ft_strcmp(".\0", ft_strrchr(node->path, '/')) &&
				!ft_strcmp(".\0", ft_strrchr(node->path, '/'))) ||
					(op->all && ft_strrchr(node->path, '/')[0] != 0))
			prev = tmp;
	}
	return (prev);
}

t_direct		*ft_display_tree(t_direct *node, t_direct *prev, t_direct *dad,
									t_opt *op)
{
	t_direct	*tmp;
	t_direct	*right;

	if (node->left)
		prev = ft_put_in_direct_lst(prev, node->left, op);
	ft_display_indir_node(node, dad, op);
	right = node->right;
	prev = (op->recurs) ? ft_put_in_direct_lst(prev, node, op) : prev;
	if (!op->recurs)
	{
		free((void *)node->path);
		free(node);
	}
	if (node->right)
	{
		tmp = ft_put_in_direct_lst(prev, right, op);
		if ((!ft_strcmp(".\0", ft_strrchr(node->path, '/')) &&
				!ft_strcmp(".\0", ft_strrchr(node->path, '/'))) ||
					(op->all && ft_strrchr(node->path, '/')[0] != 0))
			prev = tmp;
	}
	return (prev);
}
