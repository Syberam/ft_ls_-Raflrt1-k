/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 20:37:15 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/06 05:02:08 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void		ft_to_display_type(char *display_line, t_direct *cur)
{
	if (S_ISDIR(cur->file_stat.st_mode))
		ft_strcpy(display_line, "d");
	if (S_ISLNK(cur->file_stat.st_mode))
		ft_strcpy(display_line, "l");
	if (S_ISBLK(cur->file_stat.st_mode))
		ft_strcpy(display_line, "b");
	if (S_ISCHR(cur->file_stat.st_mode))
		ft_strcpy(display_line, "c");
	if (S_ISSOCK(cur->file_stat.st_mode))
		ft_strcpy(display_line, "s");
	if (S_ISFIFO(cur->file_stat.st_mode))
		ft_strcpy(display_line, "p");
	if (S_ISREG(cur->file_stat.st_mode))
		ft_strcpy(display_line, "-");
}

static void		ft_to_display_chmod(char *display_line, t_direct *cur)
{
	display_line[1] = ((cur->file_stat.st_mode & S_IRUSR) == S_IRUSR) ?
							'r' : '-';
	display_line[2] = ((cur->file_stat.st_mode & S_IWUSR) == S_IWUSR) ?
							'w' : '-';
	display_line[3] = ((cur->file_stat.st_mode & S_IXUSR) == S_IXUSR) ?
							'x' : '-';
	display_line[4] = ((cur->file_stat.st_mode & S_IRGRP) == S_IRGRP) ?
							'r' : '-';
	display_line[5] = ((cur->file_stat.st_mode & S_IWGRP) == S_IWGRP) ?
							'w' : '-';
	display_line[6] = ((cur->file_stat.st_mode & S_IXGRP) == S_IXGRP) ?
							'x' : '-';
	display_line[7] = ((cur->file_stat.st_mode & S_IROTH) == S_IROTH) ?
							'r' : '-';
	display_line[8] = ((cur->file_stat.st_mode & S_IWOTH) == S_IWOTH) ?
							'w' : '-';
	display_line[9] = ((cur->file_stat.st_mode & S_IXOTH) == S_IXOTH) ?
							'x' : '-';
}

static void		ft_to_display_file_infos(char *display_line, t_direct *cur,
										t_direct *dad, t_opt *op)
{
	char		*lin;
	size_t		i;
	size_t		j;

	i = 0;
	lin = ft_size_or_minmaj(cur);
	j = ft_strlen(display_line);
	display_line[j] = ' ';
	j += (dad->size_field - ft_strlen(lin) + 1);
	while (lin[++i - 1] && i < 256)
		display_line[j + i - 1] = lin[i - 1];
	free(lin);
	lin = ft_time_for_display(cur->file_stat, op);
	j += i - 3;
	i = 3;
	while (lin[++i])
		display_line[j + i - 1] = lin[i - 1];
	j += i;
	i = 0;
	lin = (char *)((ft_strrchr(cur->path, '/') != 0 && dad != op->arg_file) ?
							ft_strrchr(cur->path, '/') + 1 : cur->path);
	while (lin[++i - 1])
		display_line[j + i] = lin[i - 1];
	display_line[j + i] = (!S_ISLNK(cur->file_stat.st_mode)) ? '\n' : 0;
	display_line[j + i + 1] = 0;
}

static void		ft_to_display_user_infos(char *display_line, t_direct *cur,
											t_direct *dad, t_opt *op)
{
	char		*lin;
	size_t		i;
	size_t		j;

	j = 0;
	lin = ft_itoa_stack((int)cur->file_stat.st_nlink);
	i = (dad->lnk_field) - (size_t)ft_strlen(lin);
	while (lin[++j - 1])
		display_line[j + i] = lin[j - 1];
	lin = (getpwuid(cur->file_stat.st_uid)) ?
					(getpwuid(cur->file_stat.st_uid))->pw_name :
						ft_itoa(cur->file_stat.st_uid);
	i += j + dad->usr_field - (size_t)ft_strlen(lin);
	j = 0;
	while ((lin)[++j - 1])
		display_line[i + j] = (lin)[j - 1];
	lin = (getgrgid(cur->file_stat.st_gid)) ?
					(getgrgid(cur->file_stat.st_gid))->gr_name :
						ft_itoa(cur->file_stat.st_gid);
	i = (i + j);
	j = 0;
	while ((lin)[++j - 1])
		display_line[i + j] = (lin)[j - 1];
	display_line[i + (dad->grp_field) + 1] = 0;
	ft_to_display_file_infos(display_line, cur, dad, op);
}

void			ft_display_long(t_direct *elem, t_direct *dad, t_opt *opt)
{
	char		*display_line;
	char		buflnk[256];
	size_t		i;

	display_line = (char *)ft_memalloc(sizeof(char) * 800);
	i = 0;
	while (++i - 1 < 800)
		display_line[i - 1] = ' ';
	ft_to_display_type(display_line, elem);
	ft_to_display_chmod(display_line, elem);
	ft_to_display_user_infos(display_line + 11, elem, dad, opt);
	ft_putstr(display_line);
	ft_bzero(buflnk, 256);
	if (S_ISLNK(elem->file_stat.st_mode)
			&& readlink((elem->path), buflnk, 256))
	{
		ft_putstr(" -> ");
		ft_putendl(buflnk);
	}
	free(display_line);
}
