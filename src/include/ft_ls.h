/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 11:56:34 by sbonnefo          #+#    #+#             */
/*   Updated: 2017/06/04 07:03:31 by sbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>

typedef	struct dirent		t_dirent;
typedef	struct stat			t_stat;
typedef	struct passwd		t_pw;
typedef	struct group		t_grp;

typedef struct				s_indir
{
	char					*path;
	t_stat					file_stat;
}							t_indir;

typedef struct				s_direct
{
	const char				*path;
	char					*display;
	t_stat					file_stat;
	size_t					usr_field;
	size_t					grp_field;
	size_t					size_field;
	size_t					lnk_field;
	int						ph_lnk;
	struct s_direct			*left;
	struct s_direct			*next;
	struct s_direct			*right;
	struct s_direct			*relat;
	struct s_direct			*content;
}							t_direct;

typedef struct				s_opt
{
	char					recurs;
	char					long_format;
	char					all;
	char					reverse;
	char					time_sort;
	char					big_t;
	char					opt_f;
	char					opt_k;
	char					col;
	char					err;
	char					**av_dir;
	char					**wg_dir;
	char					*display;
	char					first_line;
	t_direct				*first_d;
	t_direct				*tmp_first_d;
	t_direct				*arg_file;
}							t_opt;

/*
**				PARSING
*/

t_opt						*ft_get_opt(char **argv);
t_opt						*ft_wrg_dir(t_opt *options, char *new_wrg);

/*
**				DISPLAY
*/

void						ft_display_long(t_direct *elem, t_direct *dad,
												t_opt *options);
void						ft_display_argfiles(t_opt *options);
void						ft_fields_size(t_direct *dir, t_direct *direlem);
char						*ft_time_for_display(t_stat stat_file, t_opt *ops);
char						*ft_size_or_minmaj(t_direct *cur);
void						ft_display_dircontent(t_direct *dir, t_opt *op);
void						ft_display_tree(t_direct *node, t_direct *dad,
																	t_opt *op);
void						ft_display_indir_node(t_direct *node, t_direct *dad,
													t_opt *op);
t_direct					*ft_put_in_direct_lst(t_direct *prev, t_direct *new,
													t_opt *op);

/*
**				DATA SYSTEM
*/

char						*ft_write_path(char *dad, char *child);
int							ft_time_dif(t_direct *bef, t_direct *aft);
t_opt						*ft_args_to_direct_lsts(t_opt *op);
void						ft_init_root(t_opt *options, size_t i);
char						ft_get_dircontent(t_direct *daddir, t_opt *op);
void						ft_del_dir_in_directlst(t_direct *dir, t_opt *op);
void						ft_confirm_tmp_first_d(t_opt *op);

/*
**				FREE
*/

void						ft_free_tab_str(char **strs);
void						ft_free_tmp_first_d(t_opt *op);

/*
**				ERRORS
*/

int							ft_error_ill_option(char first_ill);

char						ft_permis_den(t_direct *dir);
char						ft_error_empty_arg(int argc, char **argv);

void						ft_error_name(t_opt *options);

#endif
