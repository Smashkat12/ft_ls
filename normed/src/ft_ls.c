/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:36:05 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			recur(t_pathinfo *direntry_l, t_flag *flags)
{
	while (direntry_l)
	{
		if (direntry_l->is_dir && ft_strcmp(direntry_l->pathname, ".") \
				&& ft_strcmp(direntry_l->pathname, ".."))
		{
			ft_putchar('\n');
			ft_ls(direntry_l->fullpath, flags);
		}
		direntry_l = direntry_l->next;
	}
}

static void			print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

int					ft_ls(char *fullpath, t_flag *flags)
{
	t_pathinfo		*direntry_l;
	t_pathinfo		*check_direntry_l;
	int				total;
	static int		subdir;

	direntry_l = NULL;
	if ((validate_path(fullpath, flags, &direntry_l)) != 0)
		return (0);
	total = creat_dirent_list(&direntry_l, fullpath, flags);
	sort_list(&direntry_l, flags);
	if (subdir && flags->cap_r)
	{
		ft_putchar('\n');
		(!direntry_l) ? ft_putstr(fullpath) : ft_putendl(fullpath);
	}
	if (direntry_l && flags->l)
		print_total(total);
	check_direntry_l = direntry_l;
	print_direntries(check_direntry_l, flags);
	ft_putchar('\n');
	subdir = 1;
	if (flags->cap_r)
		recur(check_direntry_l, flags);
	free_list(&direntry_l);
	return (0);
}
