/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 20:37:15 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/05/31 20:11:09 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void		ft_to_display_type(char *display_line, t_direct *current)
{
	if (S_ISDIR(current->file_stat.st_mode))
		ft_strcpy(display_line, "d");
	if (S_ISLNK(current->file_stat.st_mode))
		ft_strcpy(display_line, "l");
	if (S_ISBLK(current->file_stat.st_mode))
		ft_strcpy(display_line, "b");
	if (S_ISCHR(current->file_stat.st_mode))
		ft_strcpy(display_line, "c");
	if (S_ISSOCK(current->file_stat.st_mode))
		ft_strcpy(display_line, "s");
	if (S_ISFIFO(current->file_stat.st_mode))
		ft_strcpy(display_line, "p");
	if (S_ISREG(current->file_stat.st_mode))
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

static void		ft_to_display_file_infos(char *display_line, t_direct *current,
										t_direct *dad, t_opt *options)
{
	char		*line_part;
	size_t		i;
	size_t		j;

	i = 0;
	line_part = ft_itoa(current->file_stat.st_size);
	j = ft_strlen(display_line);
	display_line[j] = ' ';
	j += dad->size_field - ft_strlen(line_part) + 1;
	while (line_part[++i - 1] && i < 256)
		display_line[j + i - 1] = line_part[i - 1];
	line_part = ft_time_for_display(current->file_stat, options);
	j += i - 3;
	i = 3;
	while (line_part[++i])
		display_line[j + i - 1] = line_part[i - 1];
	j += i;
	i = 0;
	line_part = (char *)((ft_strrchr(current->path, '/') != 0) ?
			ft_strrchr(current->path, '/') + 1 : current->path);
	while (line_part[++i - 1])
		display_line[j + i] = line_part[i - 1];
	display_line[j + i] =
		(!S_ISLNK(current->file_stat.st_mode)) ? '\n' : 0;
	display_line[j + i + 1] = 0;
}

static void		ft_to_display_user_infos(char *display_line, t_direct *current,
											t_direct *dad, t_opt *options)
{
	char		*line_part;
	size_t		i;
	size_t		j;

	j = 0;
	line_part = ft_itoa((int)current->file_stat.st_nlink);
	i = (dad->lnk_field) - (size_t)ft_strlen(line_part);
	while (line_part[++j - 1])
		display_line[j + i] = line_part[j - 1];
	line_part = (getpwuid(current->file_stat.st_uid)) ?
					(getpwuid(current->file_stat.st_uid))->pw_name :
						ft_itoa(current->file_stat.st_uid);
	i += j + dad->usr_field - (size_t)ft_strlen(line_part);
	j = 0;
	while ((line_part)[++j - 1])
		display_line[i + j] = (line_part)[j - 1];
	line_part = (getgrgid(current->file_stat.st_gid)) ?
					(getgrgid(current->file_stat.st_gid))->gr_name :
						ft_itoa(current->file_stat.st_gid);
	i = (i + j);
	j = 0;
	while ((line_part)[++j - 1])
		display_line[i + j] = (line_part)[j - 1];
	display_line[i + (dad->grp_field) + 1] = 0;
	ft_to_display_file_infos(display_line, current, dad, options);
}

void			ft_display_long(t_direct *elem, t_direct *dad, t_opt *opt)
{
	char		*display_line;
	char		buflnk[255];
	size_t		i;

	display_line = (char *)ft_memalloc(sizeof(char) * 800);
	i = 0;
	while (++i - 1 < 800)
		display_line[i - 1] = ' ';
	ft_to_display_type(display_line, elem);
	ft_to_display_chmod(display_line, elem);
	ft_to_display_user_infos(display_line + 11, elem, dad, opt);
	ft_putstr(display_line);
	ft_bzero(buflnk, 255);
	if (S_ISLNK(elem->file_stat.st_mode)
			&& readlink((elem->path), buflnk, 255))
	{
		ft_putstr(" -> ");
		ft_putstr(buflnk);
	}
	free(display_line);
}
