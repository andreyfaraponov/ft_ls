/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 21:33:01 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 13:11:25 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include "../libft/libft.h"
# define COLOR_RED			"\x1b[31m"
# define COLOR_GREEN		"\x1b[32m"
# define COLOR_BOLD_GREEN	"\x1b[32;1m"
# define COLOR_YELLOW		"\x1b[33m"
# define COLOR_BLUE			"\x1b[34m"
# define COLOR_MAGENTA		"\x1b[35m"
# define COLOR_BOLD_CYAN	"\x1b[96;1m"
# define COLOR_RESET		"\x1b[0m"
# define MY_ABS(x) x < 0 ? -x : x
# define STAT struct stat
# define NAME_SIZE 256

typedef struct		s_info
{
	STAT			f_stat;
	short			is_error;
	char			*name;
	char			*full_path;
}					t_info;

typedef struct		s_flags
{
	short			f_list;
	short			f_recur;
	short			f_rever;
	short			f_all;
	short			f_by_time;
	short			f_colors;
	short			f_just_dir;
	short			f_list_not_owner;
	short			f_dis_lsg;
	short			f_sort_by_mod_time;
	short			no_name;
}					t_flags;

typedef struct		s_localinfo
{
	t_flags			flags;
	char			*errors;
	char			*loc_path;
	char			*upper_path;
	unsigned int	offsets[4];
	t_info			*files;
	unsigned int	files_size;
	size_t			total_bytes;
}					t_localinfo;

void			ft_get_lsflags(t_flags *fl, int c, char **v);
void			ft_get_first_paths(t_flags *fl, int c, char **v);
void			ft_free_strsplit(char **split);
void			printf_file_name(t_flags *fl, struct stat s, char *fname);
void			print_l_info(t_localinfo *l, struct stat s, char *fname, char *path);
void			make_error(char *e_name, t_localinfo *l);
int				make_permission_error(char *e_name);
void			print_errors(char *errors);
void			run_ls_att(t_localinfo *local);
size_t			get_digit_len(size_t val);
void			open_and_print_dir(t_info file, t_flags *fl, int is_one);
void			sort_args(t_localinfo *local);
void			get_width_for_l(t_localinfo *l);
void			clear_t_localinfo(t_localinfo *info);
int				make_link_error(char *name);
int				make_flag_error(char sign);


#endif
