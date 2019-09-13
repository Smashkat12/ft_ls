/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:32:22 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/13 12:31:55 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void     print_date(t_pathinfo *a, t_flag *flags)
{
        if (flags->u)
                write(1, &ctime(&a->statinfo.st_atime)[4], 12);
        else
                write(1, &ctime(&a->statinfo.st_mtime)[4], 12);
        ft_putchar(' ');
}

static void     print_type(t_pathinfo *direntry_l)
{
        if (S_ISREG(direntry_l->statinfo.st_mode))
                ft_putchar('-');
        else if (S_ISDIR(direntry_l->statinfo.st_mode))
                ft_putchar('d');
        else if (S_ISBLK(direntry_l->statinfo.st_mode))
                ft_putchar('b');
        else if (S_ISCHR(direntry_l->statinfo.st_mode))
                ft_putchar('c');
        else if (S_ISFIFO(direntry_l->statinfo.st_mode))
                ft_putchar('p');
        else if (S_ISLNK(direntry_l->statinfo.st_mode))
                ft_putchar('l');
        else if (S_ISSOCK(direntry_l->statinfo.st_mode))
                ft_putchar('s');
        else
                ft_putchar('?');
}

static void     print_name(t_pathinfo *direntry_l, int flag, t_flag *flags)
{
        if (flag)
		{
			if (flags->one)
			{
				ft_putstr(direntry_l->pathname);
			}
			else
			{
				ft_putstr(direntry_l->pathname);
				ft_putstr(" \t");
			}
		}
        else
                ft_putstr(direntry_l->pathname);
}

static void     print_link(t_pathinfo *a)
{
        char    buf[2048];

        ft_bzero(buf, 2048);
        readlink(a->fullpath, buf, 2047);
		ft_putstr(" -> ");
		ft_putstr(buf);
}

void            print_list(t_pathinfo *direntry_l, t_flag *flags)
{
    if (flags->l)
        {
			print_type(direntry_l);
			print_permissions(direntry_l);
			ft_putstr("  ");
			ft_putnbr(direntry_l->statinfo.st_nlink);
			ft_putchar(' ');
			ft_putstr(getpwuid(direntry_l->statinfo.st_uid)->pw_name);
			ft_putchar('\t');
			ft_putstr(getgrgid(direntry_l->statinfo.st_gid)->gr_name);
			ft_putchar('\t');
			if (S_ISBLK(direntry_l->statinfo.st_mode) || S_ISCHR(direntry_l->statinfo.st_mode))
			{
				ft_putnbr(major(direntry_l->statinfo.st_rdev));
				ft_putstr("  \t");
				ft_putnbr(minor(direntry_l->statinfo.st_rdev));
			}
			else
			{
				ft_putnbr(direntry_l->statinfo.st_size);
			}
			ft_putstr("  ");
			print_date(direntry_l, flags);
			print_name(direntry_l, 0, flags);
			(S_ISLNK    (direntry_l->statinfo.st_mode)) ? print_link(direntry_l) : 0;
		}
	else
		print_name(direntry_l, 1, flags);
}