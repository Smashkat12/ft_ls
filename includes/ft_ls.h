/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:59:15 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/13 11:31:28 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
#define BIGEST(x, y) x > y ? x : y

#include "../libft/libft.h"


#include <limits.h> //for PATH_MAX
#include <dirent.h> //for opendir()
#include <string.h> //for strerror
#include <sys/stat.h> //for stat() and related struct
#include <errno.h> //for errno
#include <sys/ioctl.h> //for TIOCGWINSZ
#include <stdio.h> //for perror
#include <sys/types.h> //for ino_t
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h> //for getgrgid
#include <time.h> //for ctime()
#include <sys/xattr.h> // for listxattr
#include <sys/acl.h>
#include <stdint.h> //for uint8
#include <unistd.h>



typedef struct	s_flag
{
	u_short		a;
	u_short		A;
	u_short		l;
	u_short		R;
	u_short		r;
	u_short		f;
	u_short		u;
	u_short		c;
	u_short		t;
	u_short		one;
}				t_flag;

typedef struct	s_pathinfo
{
		char				*pathname;
		char				*fullpath;
		int					is_dir;
		int					blk_total;
		struct stat			statinfo;
		struct s_pathinfo	*next;

}			t_pathinfo;
//stores the size/lenth of the different data sections for column printing
typedef struct	s_size
{
	int			nlink; //length of link digits 
	int			pw_name;
	int			gr_name;
	int			st_size;
	int			major; //represent the driver prog (linux has one entry in the major table per device) this number entry point for all dev functions
	int			minor; // used by drive to identify the instance of the prog to work on
	int			device; // indicate special device file for printing out under size
	int			f_name;
	int			w_cols;
}				t_size;

int			index_arg;
char		char_not_flag;
t_flag		get_flags(int ac, char *av[]);
t_flag		init_flags(void);
char		get_opts(int ac, char **av, char *flags_str);
void		print_flag_error(void);
t_flag		set_flags(char c, t_flag flags);
int			ft_ls(char *path, t_flag *flags);
int			validate_path(char *path, t_flag *flags, t_pathinfo **direntry_l);
int			check_dir(char *path);
int			add_tolist(char *f_name, t_pathinfo **direntry_l, struct dirent *entry);
int			creat_dirent_list(t_pathinfo **direntry_l, char *path, t_flag *flags);
char		*correct_path(char *d_or_f_name, char *d_name);
void		sort_list(t_pathinfo **direntry_l, t_flag *flags);
void		merge_sort(t_pathinfo **direntry_l, t_flag *flags);
void		split(t_pathinfo *head, t_pathinfo **a, t_pathinfo **b);
t_pathinfo	*lex_sort(t_pathinfo *a, t_pathinfo *b, t_flag *flags);
int			timecmp(t_pathinfo *a, t_pathinfo *b, t_flag *flags);
t_pathinfo	*lex_sort2(t_pathinfo *a, t_pathinfo *b);
void		rev_list(t_pathinfo **direntry_l);
//t_size		set_size(t_pathinfo *direntry_l);
//t_size		init_size(void);
//int			getwincols(void);
//int			get_digit_len(int64_t nbr);
int			print_direntries(t_pathinfo *list, t_flag *flags);
int			get_line_capacity(int name_len, int win_cols);
void		print_list(t_pathinfo *direntry_l, t_flag *flags);
void    	print_permissions(t_pathinfo *list);
void    	free_list(t_pathinfo **list);
#endif