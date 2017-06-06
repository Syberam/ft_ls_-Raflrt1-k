/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 00:27:42 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/06 12:57:26 by sbonnefo         ###   ########.fr       */
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
	ft_args_to_direct_lsts(options);
	ft_error_name(options);
	ft_display_argfiles(options);
	while (options->first_d)
	{
		ft_get_dircontent(options->first_d, options);
		if (options->first_d)
			ft_display_dircontent(options->first_d, options);
	}
	return (0);
}
