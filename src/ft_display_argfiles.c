/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_argfiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 19:36:21 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/04 05:34:14 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void		ft_fill_fields(t_opt *op)
{
	t_direct	*tmp;

	tmp = op->arg_file;
	while (tmp)
	{
		ft_fields_size(op->arg_file, tmp);
		tmp = tmp->next;
	}
}

void			ft_display_argfiles(t_opt *op)
{
	t_direct	*tmp;

	if (op->long_format)
		ft_fill_fields(op);
	tmp = op->arg_file;
	if (tmp)
		op->first_line = 1;
	while (tmp)
	{
		(op->long_format) ? ft_display_long(tmp, op->arg_file, op) :
								ft_putstr(tmp->path);
		if (op->col)
			ft_putchar('\n');
		else if (!op->long_format)
			ft_putchar('\t');
		tmp = tmp->next;
	}
	tmp = op->arg_file;
	while (tmp)
	{
		free((void *)tmp->path);
		free(tmp);
		tmp = tmp->next;
	}
}
