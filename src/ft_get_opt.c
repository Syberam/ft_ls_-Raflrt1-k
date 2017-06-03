/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 18:58:01 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/03 06:45:12 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void			ft_init_opt(t_opt *opts, char **argv)
{
	opts->recurs = 0;
	opts->all = 0;
	opts->long_format = 0;
	opts->reverse = 0;
	opts->time_sort = 0;
	opts->err = 0;
	opts->av_dir = argv + 1;
	opts->first_line = 10;
}

static size_t		ft_active_opt_ii(char opt, t_opt *opts)
{
	if (opt == '1')
	{
		opts->col = 1;
		opts->long_format = 0;
	}
	else
	{
		opts->err = opt;
		return (0);
	}
	return (1);
}

static size_t		ft_active_opt_i(char opt, t_opt *opts)
{
	if (opt == 'R')
		opts->recurs = 1;
	else if (opt == 'a')
		opts->all = 1;
	else if (opt == 'l')
		opts->long_format = 1;
	else if (opt == 'r')
		opts->reverse = 1;
	else if (opt == 't')
		opts->time_sort = (!opts->opt_f) ? 1 : 0;
	else if (opt == 'f')
	{
		opts->opt_f = 1;
		opts->all = 1;
		opts->time_sort = 0;
	}
	else if (opt == 'k')
		opts->opt_k = 1;
	else if (opt == 'T')
		opts->big_t = 1;
	else
		return (ft_active_opt_ii(opt, opts));
	return (1);
}

t_opt				*ft_get_opt(char **argv)
{
	size_t			i;
	size_t			j;
	t_opt			*options;

	i = 0;
	if (!(options = (t_opt *)ft_memalloc(sizeof(t_opt))))
		return (NULL);
	ft_init_opt(options, argv);
	while (argv[++i] && argv[i][0] == '-')
	{
		if (argv[i][1] == 0 || (argv[i][1] == '-' && argv[i][2] == 0))
		{
			options->av_dir = (argv[i][1]) ? argv + i + 1 : argv + i;
			return (options);
		}
		j = 0;
		while (argv[i][++j] != 0)
		{
			options->av_dir = argv + i + 1;
			if (!ft_active_opt_i(argv[i][j], options))
				return (options);
		}
	}
	return (options);
}
