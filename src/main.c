/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 00:27:42 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/02 01:44:45 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

int				main(int argc, char **argv)
{
	t_opt		*options;

	if (!ft_error_empty_arg(argc, argv))
		return (0);
	options = ft_get_opt(argv);
	if (!ft_error_ill_option(options->err))
	{
		free(options);
		return (0);
	}
	ft_putendl("_____________________________");
	ft_args_to_direct_lsts(options);
	ft_error_name(options);
	ft_display_argfiles(options);
	// si options->long format -->set les fields
	ft_putchar('\n');
	ft_putendl("_____________________________");
	while (options->first_d)
	{
		ft_get_dircontent(options->first_d, options);
		ft_display_dircontent(options->first_d, options);
//		options->first_d = options->first_d->next;
	}
/*	tmp = options->first_d;
	while (tmp)
	{
		ft_putendl(tmp->path);
		tmp = tmp->next;
	}
*/	//DISPLAY + Recurs
	//free wrg_dir, options
	return (0);
}
