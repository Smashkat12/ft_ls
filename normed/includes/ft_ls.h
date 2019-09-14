/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:59:15 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:40:11 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define BIGEST(x, y) x > y ? x : y

# include "../libft/libft.h"

# include <limits.h>
# include <dirent.h>
# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdint.h>
# include <unistd.h>

int		g_indx_arg;
char	g_char_not_flag;

typedef struct			s_flag
{
	u_short				a;
	u_short				cap_a;
	u_short				l;
	u_short				cap_r;
	u_short				r;
	u_short				f;
	u_short				u;
	u_short				c;
	u_short				t;
	u_short				one;
}						t_flag;

typedef struct			s_pathinfo
{
	char				*pathname;
	char				*fullpath;
	int					is_dir;
	int					blk_total;
	struct stat			statinfo;
	struct s_pathinfo	*next;

}						t_pathinfo;

t_flag					get_flags(int ac, char *av[]);
t_flag					init_flags(void);
char					get_opts(int ac, char **av, char *flags_str);
void					print_flag_error(void);
t_flag					set_flags(char c, t_flag flags);
int						ft_ls(char *path, t_flag *flags);
int						validate_path(char *path, t_flag *flags, \
						t_pathinfo **direntry_l);
int						check_dir(char *path);
int						add_tolist(char *f_name, t_pathinfo **direntry_l, \
						struct dirent *entry);
int						creat_dirent_list(t_pathinfo **direntry_l, \
						char *path, t_flag *flags);
char					*correct_path(char *d_or_f_name, char *d_name);
void					sort_list(t_pathinfo **direntry_l, t_flag *flags);
void					merge_sort(t_pathinfo **direntry_l, t_flag *flags);
void					split(t_pathinfo *head, t_pathinfo **a, t_pathinfo **b);
t_pathinfo				*lex_sort(t_pathinfo *a, t_pathinfo *b, t_flag *flags);
int						timecmp(t_pathinfo *a, t_pathinfo *b, t_flag *flags);
t_pathinfo				*lex_sort2(t_pathinfo *a, t_pathinfo *b);
void					rev_list(t_pathinfo **direntry_l);
int						print_direntries(t_pathinfo *list, t_flag *flags);
int						get_line_capacity(int name_len, int win_cols);
void					print_list(t_pathinfo *direntry_l, t_flag *flags);
void					print_permissions(t_pathinfo *list);
void					print_link_count(t_pathinfo *direntry_l);
void					print_link(t_pathinfo *a);
void					print_type(t_pathinfo *direntry_l);
void					print_name(t_pathinfo *direntry_l, \
						int flag, t_flag *flags);
void					print_date(t_pathinfo *a, t_flag *flags);
void					free_list(t_pathinfo **list);
#endif
