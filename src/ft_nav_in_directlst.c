/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nav_in_directlst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 22:36:59 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/05/31 23:17:27 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			ft_nav_in_directlst(t_opt *op)
{
	t_direct	*tmp;
	while (op->first_d)
	{
		tmp = op->first_d;
		ft_get_dircontent(tmp);
		ft_display_dircontent(tmp);
		op->first_d = tmp->next;
		free((void *)tmp->path);
		free(tmp);
	}
}
