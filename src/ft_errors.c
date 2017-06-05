/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 18:18:48 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/04 07:03:13 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

int			ft_error_ill_option(char first_ill)
{
	char	*supp_opt;

	if (!first_ill)
		return (1);
	supp_opt = "[-RafklrtT1]\0";
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(first_ill, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ls ", 2);
	ft_putstr_fd(supp_opt, 2);
	ft_putendl_fd(" [file ...]", 2);
	return (0);
}

char		ft_permis_den(t_direct *dir)
{
	DIR		*current_dir;

	if ((current_dir = opendir(dir->path)))
	{
		closedir(current_dir);
		return (0);
	}
	ft_putchar('\n');
	ft_putstr(dir->path);
	ft_putendl(":");
	ft_putstr_fd("ft_ls: ", 2);
	ft_strrchr(dir->path, '/') ?
			ft_putstr_fd(ft_strrchr(dir->path, '/') + 1, 2) :
			ft_putstr_fd(dir->path, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (1);
}

static void	ft_sort_err(t_opt *options)
{
	size_t	i;
	char	*swp;

	i = 0;
	while ((options->wg_dir)[i])
	{
		if ((options->wg_dir)[i + 1]
				&& ft_strcmp(options->wg_dir[i], options->wg_dir[i + 1]) > 0)
		{
			swp = options->wg_dir[i];
			options->wg_dir[i] = options->wg_dir[i + 1];
			options->wg_dir[i + 1] = swp;
			i = 0;
		}
		i++;
	}
}

void		ft_error_name(t_opt *options)
{
	size_t	i;

	if (!options->wg_dir)
		return ;
	options->first_line = 1;
	i = 0;
	ft_sort_err(options);
	while ((options->wg_dir)[i])
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd((options->wg_dir)[i], 2);
		ft_putendl_fd(": No such file or directory", 2);
		i++;
	}
}

char		ft_error_empty_arg(int argc, char **argv)
{
	size_t	i;

	i = 0;
	while (++i < (size_t)argc)
	{
		if (!argv[i][0])
		{
			ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
			return (0);
		}
	}
	return (1);
}
