/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:59:15 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/07 11:31:21 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/libft.h"


#include <limits.h> //for PATH_MAX
#include <dirent.h> //for opendir()
#include <string.h> //for strerror
#include <sys/stat.h> //for stat() and related struct
#include <errno.h> //for errno
#include <sys/ioctl.h> //for TIOCGWINSZ
#include <stdio.h> //for perror
#include <sys/types.h> //for getpwuid
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h> //for getgrgid
#include <time.h> //for ctime()
#include <sys/xattr.h> // for listxattr
#include <sys/acl.h>
#include <stdint.h> //for uint8
#include <unistd.h>

typedef struct	flag_s
{
	u_short		a;
	u_short		l;
	u_short		R;
	u_short		r;
	u_short		t;
}				flag_t;

typedef struct	pathinfo_s
{
		char				*pathname;
		char				*fullpath;
		int					IS_DIR;
		int					blk_total;
		struct stat			*statinfo;
		struct pathinfo_s	*next;

}				pathinfo_t;

int			index_arg;
char		char_not_flag;
flag_t		get_flags(int ac, char *av[]);
flag_t		init_flags(void);
char		get_opts(int ac, char **av, char *flags_str);
void		print_flag_error(void);
flag_t		set_flags(char c, flag_t flags);
int			ft_ls(char *path, flag_t *flags);
int			validate_path(pathinfo_t **pathinfo_l, char *path, flag_t *flags);
#endif